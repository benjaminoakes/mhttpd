/**
 * @author Benjamin Oakes <hello@benjaminoakes.com>
 */
#include <stdio.h>

#include "mhttpd.h"

const char *progname;

int main(int argc, char *argv[]) {
    char *index;
    int port = 3000;

    progname = argv[0];

    printf("[%s] Starting...\n", progname);

    if (argc == 2) {
        index = argv[1];
    } else {
        index = "public/index.html";
    }

    printf("[%s] Listening on port %d\n", progname, port);
    mhttp.listen(port);

    printf("[%s] Finished\n", progname);

    return 0;
}
