all:
	gcc ./tty-typing.c -o tty-typing -Wall

install:
	cp ./tty-typing /usr/bin/tty-typing
