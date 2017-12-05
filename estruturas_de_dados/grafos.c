#include <stdio.h>
#include <stdlib.h>

#define NV 		8

typedef int GrafoM[NV][NV];

typedef struct aresta{

	int destino;
	int peso;
	struct aresta *prox;
	
} *Grafo[NV];


GrafoM A = {
	
	{0, 0, 0, 1, 0, 0, 0, 0},
	{2, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 4, 2, 0, 0, 0, 2, 0},
	{0, 0, 0, 0, 0, 0, 0, 3},
	{0, 0, 0, 0, 1, 0, 0, 2},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};



void matToLista(GrafoM in, Grafo out){

	int l, c;
	struct aresta *new;

	for (l = 0; l < NV; l++){ // percorre todas as linhas da matriz
		
		out[l] = NULL; // pode haver vértices que não têm nenhum destino
		
		for (c = 0; c < NV; c++){ // percorre todas as colunas da matriz
			
			if (in[l][c] != 0){
	 		
		 		new = malloc (sizeof(struct aresta));
		 		new->destino = c;
		 		new->peso = in[l][c];
		 		
		 		// acrescenta á cabeça da lista
		 		new->prox = out[l];
		 		out[l] = new;
	 		}
		}
	}
}



void printMatrix(GrafoM a){

	int l, c;

	for(l = 0; l < NV; l++){
		for (c = 0; c < NV; c++) printf("%d ", a[l][c]);
		putchar('\n');
	}

	putchar('\n');
}



void printGrafo(Grafo a){

	int l;
	struct aresta *x;

	//percorre todos os vértices
	for(l = 0; l < NV; l++){
		
		printf("%d -> ", l);
		
		//percorre os sucessores do vértice (l)
		for(x = a[l]; x; x = x->prox) printf("(%d | peso: %d) -> ", x->destino, x->peso); 

		putchar('\n');
	}

	putchar('\n');

}


void listaToMat(Grafo in, GrafoM out){

	int l, c;
	struct aresta *x;

	//inicializar a matriz out a zeros
	for (l = 0; l < NV; l++)
		for (c = 0; c < NV; c++)
			out[l][c] = 0;

	for (l = 0; l < NV; l++) //percorre todos os vértices
		for (x = in[l]; x; x = x->prox) //percorre todos os sucessores do vértice (l)
			out[l][x->destino] = x->peso;
}



int main(){

	printMatrix(A);

	Grafo B;
	matToLista(A, B);
	printGrafo(B);

	GrafoM C;
	listaToMat(B, C); // aqui a mat C == mat A
	printMatrix(C); 

	return 0;
}









