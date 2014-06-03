################################################################################
# makefile
# --------
# Created by Steve Heller
################################################################################

all: clean run test

debug: run-debug test

run:
	gcc run.c -o run -lpthread

run-debug:
	gcc run.c -o run -lpthread -g

test:
	gcc test.c -o test -lpthread

clean:
	rm -rf run test
