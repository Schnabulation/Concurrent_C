################################################################################
# makefile
# --------
# Created by Steve Heller
################################################################################

all: server client

server:
	gcc editor.c -o run -lpthread

client:
	gcc client.c -o test -lpthread

clean:
	rm -rf run test
