#! /bin/bash
CC=gcc

server:server.o
	${CC} -o server server.o

client:client.o
	${CC} -o client client.o

server.o:server.c headers.h declarations.h
	${CC} -c server.c

client.o:client.c headers.h declarations.h
	${CC} -c client.c

clean:
	rm *.o
	rm server
	rm client
