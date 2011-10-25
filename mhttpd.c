#include "mhttpd.h"

static void listen(int port) {
    puts("got in");
}

ns const mhttp = {
    listen
};
