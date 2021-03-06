#ifndef __mhttpd_h__
#define __mhttpd_h__

#include <netinet/in.h> /* for serv_addr, cli_addr, AF_INET, INADDR_ANY, etc */
#include <stdio.h> /* for fopen, sscanf, etc */
#include <stdlib.h> /* for exit */
#include <strings.h> /* for bzero */
#include <sys/socket.h> /* for socket */

#include "dbg.h"

typedef struct {
    void (* const listen)(int);
} mhttp_ns;
extern mhttp_ns const mhttp;
#endif
