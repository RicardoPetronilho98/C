/* this file shows how to send input by terminal execution */

#include <stdio.h> //standard input output library

int main(int argc, char const *argv[]){

	printf("argc = %d\n", argc);
	printf("argv[0] = %s\n", argv[0]);
	printf("argv[1] = %s\n", argv[1]);
	
	return 0; // Zero indicates success
}

/* 
	compile: gcc -Wall input_by_exec.c -o input_by_exec
	run: ./input_by_exec hello
	
	returned output: argc = 2
					 argv[0] = ./input_by_exec
					 argv[1] = credu

	explanation:
	argc ---> contains the number of arguments provided by the input
	argv[] ---> contains pointers to the arguments (an array of pointers)
*/