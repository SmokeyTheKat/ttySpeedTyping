all:
	gcc ./tty-typing.c -o tty-typing -Wall -lX11

install:
	cp ./tty-typing /usr/bin/tty-typing
