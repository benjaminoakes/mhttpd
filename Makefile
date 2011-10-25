OUTFILE="mhttpd"

all: mhttpd.o
	./configure
	gcc main.c mhttpd.o -o ${OUTFILE}

mhttpd.o: mhttpd.c
	gcc -c mhttpd.c

test: all
	./${OUTFILE}

clean:
	rm -rf *.o
	rm -f ${OUTFILE}
