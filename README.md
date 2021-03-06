mhttpd
======

A minimal, C-based HTTP server.

My goal is to keep it simple and only handle GET requests.  I'm building it to practice C and teach myself more about low level networking.

Usage
-----

<!-- BEGIN USAGE -->
	Usage: ./mhttpd [--help] [port]
	
	Serve a directory over HTTP
	
	   --help      Show this help text.
	   port        Port number.  Default: 80 (requires privileges)
	
	Example:
	
	   ./mhttpd 3000
<!-- END USAGE -->

Right now, it just serves up "public/index.html" in response to any request.

Building
--------

After you have the source (e.g., from [downloading a tarball via GitHub](https://github.com/benjaminoakes/mhttpd/tarball/master)), just do the standard steps:

	./configure
	make

Currently, there is no "make install" task, but you can mv the resulting "mhttpd" executable anywhere you'd like.
