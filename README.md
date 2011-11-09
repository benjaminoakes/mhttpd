mhttpd
======

A minimal, C-based HTTP server.

My goal is to keep it simple and only handle GET requests.  I'm building it to practice C and teach myself more about low level networking.

Usage
-----

    Usage: mhttpd [port]

Example:

	mhttpd 3000

Right now, it just serves up "public/index.html" in response to any request.

Building
--------

After you have the source (e.g., from [downloading a tarball via GitHub](https://github.com/benjaminoakes/mhttpd/tarball/master)), just do the standard steps:

	./configure
	make

Currently, there is no "make install" task, but you can mv the resulting "mhttpd" executable anywhere you'd like.
