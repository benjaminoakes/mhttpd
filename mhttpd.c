#include "mhttpd.h"

#define MAX_Q_LEN 20

/**
 * Get a file, like Unix `cat`.
 */
void ns_cat(char* path, int res_sock_fd) {
    char c;
    int n;
    FILE *file;

    file = fopen(path, "r");

    // TODO buffer read and write into a char[BUFSIZ]
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
        n = write(res_sock_fd, &c, 1);
        check(n >= 0, "Error writing to socket");
    }

error:
    fclose(file);
    close(res_sock_fd);
}

/**
 * Begin listening on port.
 *
 * @see http://www.linuxhowtos.org/C_C++/socket.htm
 * @see http://www.linuxhowtos.org/data/6/server.c
 */
static void ns_listen(int port) {
    int req_sock_fd;
    int res_sock_fd;
    int bind_result;
    int n;
    socklen_t res_len;
    char req_buffer[BUFSIZ];
    struct sockaddr_in req_addr, res_addr;
    char* header = "HTTP/1.0 200 OK\nContent-Type: text/html\n\n"; // TODO Content-Length: 1234

    req_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    check(req_sock_fd != -1, "Error opening socket");

    bzero((char*) &req_addr, sizeof(req_addr));
    req_addr.sin_family = AF_INET;
    req_addr.sin_addr.s_addr = INADDR_ANY;
    req_addr.sin_port = htons(port);

    bind_result = bind(req_sock_fd, (struct sockaddr*) &req_addr, sizeof(req_addr));
    check(bind_result == 0, "Error binding");

    for (;;) {
        listen(req_sock_fd, MAX_Q_LEN);
        res_len = sizeof(res_addr);
        res_sock_fd = accept(req_sock_fd, (struct sockaddr *) &res_addr, &res_len);
        check(res_sock_fd >= 0, "Error accepting");

        bzero(req_buffer, BUFSIZ);
        n = read(res_sock_fd, req_buffer, BUFSIZ - 1);
        check(n >= 0, "Error reading from socket");

        printf("%s", req_buffer);
        printf("%s", header);
        n = write(res_sock_fd, header, strlen(header));
        check(n >= 0, "Error writing to socket");

        ns_cat("public/index.html", res_sock_fd);
    }

error:
    close(res_sock_fd);
    close(req_sock_fd);
}

mhttp_ns const mhttp = {
    ns_listen
};
