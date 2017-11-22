#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ocupado 	0
#define livre		1
#define apagado 	2


typedef int chave;


typedef struct entry{
	
	chave c;
	char info[128];
	int status;	

} * Entry;


int hash(chave c, int N){

	return c % N;
}


Entry procura(chave cp, int N, Entry v[]){

	int h = hash(cp, N);
	int i = h;

	while (v[i]->status != livre || i < N){

		if (v[i]->c == h) return v[i];

		i++;
	}

	return NULL;
}



/*void listArray(int v[], int N){

	int i;

	for (i = 0; i < N; i++) printf("\nchave: %d --> info: %s\n", v[i]->c, v[i]->info);

	putchar('\n');
}*/



int main(){
 	
 	Entry a = (Entry) malloc (sizeof(struct entry));
 	a->c = 524;
 	strcpy(a->info, "Joao");
 	a->status = ocupado;

 	Entry b =  (Entry) malloc (sizeof(struct entry));
 	b->c = 789;
 	strcpy(b->info, "Ricardo");
 	b->status = ocupado;

 	Entry c = (Entry) malloc (sizeof(struct entry));
 	Entry d = (Entry) malloc (sizeof(struct entry));
 	Entry e = (Entry) malloc (sizeof(struct entry));
 	Entry f = (Entry) malloc (sizeof(struct entry));
 	Entry g = (Entry) malloc (sizeof(struct entry));
 	Entry h = (Entry) malloc (sizeof(struct entry));
 	Entry i = (Entry) malloc (sizeof(struct entry));
 	Entry j = (Entry) malloc (sizeof(struct entry));

 	c->status = d->status = e->status = f->status = g->status = h->status = i->status = j->status = livre;

 	int N = 10;
 	Entry v[] = {c, a, b, d, e, f, g, h, i, j};

	Entry t = procura(222, N, v);

	printf("%d --> %s\n", t->c, t->info);

	return 0;
}





