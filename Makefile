OUTFILE="mhttpd"

all: configure
	./configure
	gcc main.c -o ${OUTFILE}

test: all
	./${OUTFILE}

clean:
	rm -rf *.o
	rm -f ${OUTFILE}
