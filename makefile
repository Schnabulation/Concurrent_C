################################################################################
# makefile
# --------
# Created by Steve Heller
################################################################################

all: server client

debug: server-debug client

server:
	gcc editor.c -o run -lpthread

server-debug:
	gcc editor.c -o run -lpthread -g

client:
	gcc client.c -o test -lpthread

clean:
	rm -rf run test
