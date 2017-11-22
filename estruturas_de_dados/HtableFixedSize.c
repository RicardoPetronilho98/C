#include <stdio.h>

#define Hsize 		 11
#define Free 	 	  0
#define Used 	 	  1
#define Deleted	 	  2



typedef struct cell{

	int status;
	int value;

} HTable [Hsize];





int hash(int k, int size){

	return (k % size);
}






void init(HTable h){

	int i;

	for (i = 0; i < Hsize; i++) h[i].status = Free;
}






int procura(HTable h, int k){

	int p = hash(k, Hsize);
	int n = Hsize;

	while(h[p].value != k && h[p].status != Free && n >= 0){

		p = (p + 1) % Hsize;
		n--;
	}

	return ((h[p].value == k) && (h[p].status == Used));
}




void printHashTable(HTable h){

	int i;

	for (i = 0; i < Hsize; i++){

		printf("%d (%d) --> ", h[i].value, h[i].status);
	}

	printf("NULL\n");
}





int acrescenta(HTable h, int k){

	//0 - sucesso, 1 - já existia, 2 - tabela cheia

	int p, n;

	if (procura(h, k)) return 1;

	p = hash(k, Hsize);
	n = Hsize;

	while(n > 0 && h[p].status == Used){

		n--;
		p = (p + 1) % Hsize;
	}

	if (n == 0) return 2;

	h[p].value = k;
	h[p].status = Used;

	return 0;
}






int main(){

	putchar('\n');

	HTable h = { {Free, 12}, 
	     		 {Used, 78}, 
	     		 {Free, 34}, 
	     		 {Free, 45}, 
	     		 {Used, 15}, 
	     		 {Deleted, 37}, 
	     		 {Used, 28}, 
	     		 {Used, 73}, 
	     		 {Used, 95}, 
	     		 {Used, 49}, 
	     		 {Free, 98} };

	printf("HTable inicial => ");
	printHashTable(h);

	printf("\nacrescenta 99 - %d sucesso\n\n", acrescenta(h, 99));

	printHashTable(h);

	printf("\nacrescenta 49 - %d ja existia\n\n", procura(h, 49));

	init(h);

	puts("Iniciar uma HTable - tudo Free\n");

	printHashTable(h);

	printf("\nacrescenta 2 - %d sucesso\n\n", acrescenta(h, 2));

	printHashTable(h);

	putchar('\n');

	return 0;
}









