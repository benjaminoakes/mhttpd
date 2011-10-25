#include "mhttpd.h"

static void ns_listen(int port) {
    puts("got in");
}

ns const mhttp = {
    ns_listen
};
