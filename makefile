################################################################################
# makefile
# --------
# Created by Steve Heller
################################################################################

all: server client

debug: server-debug client

server:
	gcc server.c -o run -lpthread

server-debug:
	gcc server.c -o run -lpthread -g

client:
	gcc client.c -o test -lpthread

clean:
	rm -rf run test
