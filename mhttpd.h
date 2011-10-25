#include <stdio.h> /* for fopen, etc */
#include <sys/socket.h> /* for socket */
#include <netinet/in.h> /* for serv_addr, cli_addr, AF_INET, INADDR_ANY, etc */

#ifndef MTTPD_H
#define MTTPD_H
typedef struct {
    void (* const listen)(int);
} ns;
extern ns const mhttp;
#endif
