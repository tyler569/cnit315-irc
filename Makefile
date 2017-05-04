
all:
	gcc -Wall -pedantic -ansi notesModule.c profanity.c main.c logging.c reverse.c -O0 -g -o ircbot

run: all
	./ircbot

