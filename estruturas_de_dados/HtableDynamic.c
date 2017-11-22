#include <stdio.h>
#include <stdlib.h>

#define Free 	 	  0
#define Used 	 	  1
#define Deleted	 	  2



typedef struct cell{

	int status;
	int value;

} CELL;


typedef struct thash{

	int hsize;
	int used;

	CELL *t;
	
} *THASH;





void init(THASH h, int size){

	int i;

	h->t = malloc(size * sizeof(CELL));
	h->hsize = size;
	h->used = 0;

	for (i = 0; i < size; i++) h->t[i].status = Free;
}




void printHashTable(THASH h){

	int i;

	for (i = 0; i < h->hsize; i++){

		printf("%d (%d) --> ", h->t[i].value, h->t[i].status);
	}

	printf("NULL\n");
}






int main(){

	putchar('\n');

	THASH h; 
	int size = 10;

	init(h, size);

	printf("HTable inicial => "); printHashTable(h);

	
	return 0;
}




//ficheiro não acabado

















