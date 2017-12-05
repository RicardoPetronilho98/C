#include <stdio.h>
#include <stdlib.h>

#define NV			8

typedef int GrafoM[NV][NV];

typedef struct aresta {

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

	for(l = 0; l < NV; l++){// percorre todos os vértices
		
		printf("%d -> ", l);
		
		for(x = a[l]; x; x = x->prox) // percorre os sucessores do vértice (l)
			printf("(%d | peso: %d) -> ", x->destino, x->peso); 

		putchar('\n');
	}

	putchar('\n');
}




void listaToMat(Grafo in, GrafoM out){

	int l, c;
	struct aresta *x;

	for (l = 0; l < NV; l++) // inicializar a matriz out a zeros
		for (c = 0; c < NV; c++)
			out[l][c] = 0;

	for (l = 0; l < NV; l++) //percorre todos os vértices
		for (x = in[l]; x; x = x->prox) //percorre todos os sucessores do vértice (l)
			out[l][x->destino] = x->peso;
}




int capacidadeIn(Grafo g, int v){

	// peso total das 'setas' que estão a 'entrar' no vértive v

	int l, count = 0;
	struct aresta *x;

	for (l = 0; l < NV; l++) // percorre todos os vértices
		for (x = g[l]; x; x = x->prox) // percorre todos os sucessores do vértice (l)
			if (x->destino == v){
				count += x->peso;
				break; // este 'men' já não apareçe á frente, logo não é preciso continuar a procurar
			}

	return count;
}




int capacidadeOut(Grafo g, int v){

	// peso total das 'setas' que estão a 'sair' no vértive v

	int count = 0;
	struct aresta *x;

	for (x = g[v]; x; x = x->prox) // percorre todos os sucessores do vértice (l)
		count += x->peso;

	return count;
}




int capacidade(Grafo g, int v){

	return capacidadeIn(g, v) - capacidadeOut(g, v);
}



int vMaxCap(Grafo g){

	int cap[NV], l, r;
	struct aresta *x;

	for (l = 0; l < NV; cap[l++] = 0); //inicializa o array cap[] a zeros

	for (l = 0; l < NV; l++) // percorre todos os vértices
		for (x = g[l]; x; x = x->prox){ // percorre todos os sucessores do vértice (l)
			
			// o resultado final desta parte é o calculo eficiente da capacidade de todos os vértices
			cap[l] -= x->peso;
			cap[x->destino] += x->peso;
		}

	for (r = 0, l = 1; l < NV; l++) // este ciclo determina o MAX do array cap[]
		if (cap[l] > cap[r]) r = l;

	return r;
}




int vMaxCap_Ineficiente(Grafo g){

	int cap[NV], l, r;
	struct aresta *x;

	for (l = 0; l < NV; cap[l++] = 0); // inicializa o array cap[] a zeros

	for (l = 0; l < NV; l++) // percorre todos os vértices
		cap[l] = capacidade(g, l); // 'men' isto aqui vai fazer muitas iterações, o mesmo se obtém fazendo poucas...

	for (r = 0, l = 1; l < NV; l++)
		if (cap[l] > cap[r]) r = l;

	return r;
}





int main(){

	printMatrix(A);

	Grafo B;
	matToLista(A, B);
	printGrafo(B);

	GrafoM C;
	listaToMat(B, C); // aqui a mat C == mat A
	printMatrix(C); 

	int v = 7;
	printf("capacidade de entrada no vértice %d --> %d\n\n", v, capacidadeIn(B, v) );
	printf("capacidade de saida no vértice %d --> %d\n\n", v, capacidadeOut(B, v) );
	printf("capacidade total do vértice %d --> %d\n\n", v, capacidade(B, v) );
	
	printf("vértice com maior capacidade total do grafo B --> %d \n\n", v, vMaxCap(B) );
	printf("vértice com maior capacidade total do grafo B --> %d (versao INEFICIENTE)\n\n", v, vMaxCap_Ineficiente(B) );

	return 0;
}