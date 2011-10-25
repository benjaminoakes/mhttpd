/**
 * @author Benjamin Oakes <hello@benjaminoakes.com>
 */
#include <stdio.h>

#include "mhttpd.h"

const char *progname;

void cat(char *path) {
    FILE *file;
    char c;

    file = fopen(path, "r");

    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }

    fclose(file);
}

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

    // cat(index);

    printf("[%s] Listening on port %d\n", progname, port);
    mhttp.listen(port);

    printf("[%s] Finished\n", progname);

    return 0;
}
