#include "mhttpd.h"

#define MAX_Q_LEN 5

static void ns_error(const char *msg) {
    perror(msg);
    exit(1);
}

/*
 * Begin listening on port
 * @see http://www.linuxhowtos.org/data/6/server.c, http://www.linuxhowtos.org/C_C++/socket.htm
 */
static void ns_listen(int port) {
    int req_sock_fd, res_sock_fd;
    socklen_t res_len;
    char req_buffer[BUFSIZ];
    struct sockaddr_in req_addr, res_addr;
    int n;

    req_sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (req_sock_fd < 0) {
       ns_error("Error opening socket");
    }

    bzero((char*) &req_addr, sizeof(req_addr));
    req_addr.sin_family = AF_INET;
    req_addr.sin_addr.s_addr = INADDR_ANY;
    req_addr.sin_port = htons(port);

    if (bind(req_sock_fd, (struct sockaddr *) &req_addr, sizeof(req_addr)) < 0) {
        ns_error("Error binding");
    }

    listen(req_sock_fd, MAX_Q_LEN);
    res_len = sizeof(res_addr);
    res_sock_fd = accept(req_sock_fd, (struct sockaddr *) &res_addr, &res_len);

    if (res_sock_fd < 0) {
        ns_error("Error accepting");
    }

    bzero(req_buffer, BUFSIZ);
    n = read(res_sock_fd, req_buffer, BUFSIZ - 1);

    if (n < 0) {
        ns_error("Error reading from socket");
    }

    printf("%s", req_buffer);
    n = write(res_sock_fd, "I got your message\n", 19);

    if (n < 0) {
        ns_error("Error writing to socket");
    }

    close(res_sock_fd);
    close(req_sock_fd);
}

ns const mhttp = {
    ns_listen
};
