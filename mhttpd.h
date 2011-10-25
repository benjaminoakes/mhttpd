#include <stdio.h>
#include <sys/socket.h> /* for socket() */

#ifndef MTTPD_H
#define MTTPD_H
typedef struct {
    void (* const listen)(int);
} ns;
extern ns const mhttp;
#endif
