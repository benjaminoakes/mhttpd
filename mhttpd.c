#include "mhttpd.h"

#define MAX_Q_LEN 5

static void ns_error(const char *msg) {
    perror("Error opening socket");
    exit(1);
}

/*
 * Begin listening on port
 * @see http://www.linuxhowtos.org/data/6/server.c, http://www.linuxhowtos.org/C_C++/socket.htm
 */
static void ns_listen(int port) {
    int servsockfd, clisockfd;
    socklen_t clilen;
    char buffer[BUFSIZ];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    servsockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (servsockfd < 0) {
       ns_error("ERROR opening socket");
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(servsockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        ns_error("Error binding");
    }

    listen(servsockfd, MAX_Q_LEN);
    clilen = sizeof(cli_addr);
    clisockfd = accept(servsockfd, (struct sockaddr *) &cli_addr, &clilen);

    if (clisockfd < 0) {
        ns_error("Error accepting");
    }

    bzero(buffer, BUFSIZ);
    n = read(clisockfd, buffer, BUFSIZ - 1);

    if (n < 0) {
        ns_error("Error reading from socket");
    }

    printf("%s\n", buffer);
    n = write(clisockfd, "I got your message\n", 19);

    if (n < 0) {
        ns_error("Error writing to socket");
    }

    close(clisockfd);
    close(servsockfd);
}

ns const mhttp = {
    ns_listen
};
