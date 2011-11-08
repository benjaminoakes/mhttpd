/**
 * @author Benjamin Oakes <hello@benjaminoakes.com>
 */
#include <stdio.h>
#include "mhttpd.h"

#define DEFAULT_PORT 3000

/** Name this program was called with */
const char* progname;

/** Print usage information */
static void show_usage() {
    printf("Serve a directory over HTTP\n");
    printf("\n");
    printf("Usage: %s [port]\n", progname);

    exit(-2);
}

/** Start server */
static void start(int port) {
    printf("[%s] Starting...\n", progname);

    printf("[%s] Listening on port %d\n", progname, port);
    mhttp.listen(port);

    printf("[%s] Finished\n", progname);
}

/** Entry point; process arguments and start. */
int main(int argc, char* argv[]) {
    int port = DEFAULT_PORT;
    progname = argv[0];

    if (argc == 2) {
        port = atoi(argv[1]);
    } else if (argc > 2) {
        show_usage();
    }

    start(port);

    return 0;
}
