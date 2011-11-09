/**
 * @author Benjamin Oakes <hello@benjaminoakes.com>
 */
#include <signal.h>
#include <stdbool.h>
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

/**
 * Handle quit signal
 * @see http://www.go4expert.com/forums/showthread.php?t=839
 */
static void signal_quit() {
    debug("%s", __FUNCTION__);
    // TODO clean up?
    exit(0);
}

/** Handle interrupt signal */
static void signal_interrupt() {
    debug("%s", __FUNCTION__);
    signal_quit();
}

/** Start server */
static void start(int port) {
    log_info("Starting...");

    log_info("Listening on port %d", port);
    mhttp.listen(port);

    log_info("Finished");
}

/** Initialize, process arguments, and start. */
int main(int argc, char* argv[]) {
    int port = DEFAULT_PORT;
    progname = argv[0];

    signal(SIGINT, signal_interrupt);
    signal(SIGQUIT, signal_quit);

    if (argc == 2) {
        port = atoi(argv[1]);
    } else if (argc > 2) {
        show_usage();
    }

    start(port);

    return 0;
}
