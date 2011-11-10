/**
 * @author Benjamin Oakes <hello@benjaminoakes.com>
 */
#include <signal.h>
#include <stdio.h>
#include "mhttpd.h"

#define DEFAULT_PORT 80

/** Name this program was called with */
const char* progname;

/** Print usage information */
static void show_usage() {
    printf(
        "Usage: %s [--help] [port]\n"
        "\n"
        "Serve a directory over HTTP\n"
        "\n"
        "   --help      Show this help text.\n"
        "   port        Port number.  Default: %d (requires privileges)\n"
        "\n"
        "Example:\n"
        "\n"
        "   %s 3000\n"

        , progname
        , DEFAULT_PORT
        , progname
    );

    exit(-1);
}

/**
 * Process command line arguments
 *
 * @return port number
 */
static int process_args(int argc, char* argv[]) {
    int i;
    int port = DEFAULT_PORT;

    for (i = 0; i < argc; i++) {
        if (0 == strcmp(argv[i], "--help")) {
            show_usage();
        }
    }

    if (argc == 2) {
        port = atoi(argv[1]);
    } else if (argc > 2) {
        show_usage();
    }

    return port;
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
    int port;
    progname = argv[0];

    signal(SIGINT, signal_interrupt);
    signal(SIGQUIT, signal_quit);

    port = process_args(argc, argv);
    start(port);

    return 0;
}
