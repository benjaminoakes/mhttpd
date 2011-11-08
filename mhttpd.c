#include "mhttpd.h"

#define MAX_Q_LEN 5

/**
 * Print out a file, like Unix `cat`.
 */
void ns_cat(char* path) {
    FILE *file;
    char c;

    file = fopen(path, "r");

    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }

    fclose(file);
}

/**
 * Begin listening on port.
 *
 * @see http://www.linuxhowtos.org/C_C++/socket.htm
 * @see http://www.linuxhowtos.org/data/6/server.c
 */
static void ns_listen(int port) {
    int req_sock_fd,
        res_sock_fd,
        bind_result,
        n;
    socklen_t res_len;
    char req_buffer[BUFSIZ];
    struct sockaddr_in req_addr, res_addr;
    char* header = "HTTP/1.0 200 OK\nContent-Type: text/html\n\n"; // TODO Content-Length: 1234
    char* body = "<!DOCTYPE html>\n<html><head><title>Hello</title></head><body><h1>Hello from mhttpd</h1><p>This is just a test</p></body></html>\n";

    req_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    check(req_sock_fd >= 0, "Error opening socket");

    bzero((char*) &req_addr, sizeof(req_addr));
    req_addr.sin_family = AF_INET;
    req_addr.sin_addr.s_addr = INADDR_ANY;
    req_addr.sin_port = htons(port);

    bind_result = bind(req_sock_fd, (struct sockaddr*) &req_addr, sizeof(req_addr));
    check(bind_result >= 0, "Error binding");

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
    printf("%s", body);
    n = write(res_sock_fd, body, strlen(body));

    check(n >= 0, "Error writing to socket");

error:
    close(res_sock_fd);
    close(req_sock_fd);
}

mhttp_ns const mhttp = {
    ns_listen
};
