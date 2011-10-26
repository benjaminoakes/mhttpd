OUTFILE="mhttpd"

all: mhttpd.o
	gcc main.c mhttpd.o -o ${OUTFILE}

mhttpd.o: mhttpd.c mhttpd.h
	gcc -c mhttpd.c

test: all
	./${OUTFILE}

clean:
	rm -rf *.o
	rm -f ${OUTFILE}
