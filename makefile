CC=gcc
script: script.c
	gcc -o script script.c -lhidapi-hidraw
