/**
 * @author Benjamin Oakes <hello@benjaminoakes.com>
 */
#include <stdio.h>

#include "mhttpd.h"

char *progname;

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

    if (argc == 2) {
        index = argv[1];
    } else {
        index = "public/index.html";
    }

    printf("[%s] starting...\n", progname);
    printf("[%s] started\n", progname);

    cat(index);

    mhttp.listen(port);

    printf("[%s] finished\n", progname);

    return 0;
}
