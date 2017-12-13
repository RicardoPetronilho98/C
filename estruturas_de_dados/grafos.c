#include <stdio.h>
#include <stdlib.h>



#define NV					8
#define INFINITY	  	99999



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



GrafoM D = {

	{0, 0, 0, 6, 0, 0, 0, 0},
	{5, 0, 18, 0, 0, 21, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0},
	{10, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 11, 0, 3, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};




//print functions ------------------------------------------------------------------------------------

void printArray(int a[], int N){

	int i;

	for(i = 0; i < N; i++) 
		printf("%d ", a[i]);

	puts("\n");
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

//Conversões Matriz-Grafos --------------------------------------------------------------------------




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

//Capacidade de vértices -------------------------------------------------------------------------------





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

	for (l = 0; l < NV; cap[l++] = 0); // inicializa o array cap[] a zeros

	for (l = 0; l < NV; l++) // percorre todos os vértices
		cap[l] = capacidade(g, l); // 'men' isto aqui vai fazer muitas iterações, o mesmo se obtém fazendo poucas...

	for (r = 0, l = 1; l < NV; l++)
		if (cap[l] > cap[r]) r = l;

	return r;
}

//Travessias de grafos -------------------------------------------------------------------------------------




int breadthFirst(Grafo g, int v, int ant[]){

	int q[NV], i, f, visitados[NV];
	struct aresta *x;

	for (i = 0; i < NV; i++){

		visitados[i] = 0;
		ant[i] = -1;
	}

	i = f = 0; 
	q[f++] = v; // a fila/ orla começa com o vértice inicial
	visitados[v] = 1; // para respeitar o Invariante o vértice inicial é visitado aqui

	while(i != f){

		v = q[i++]; // vai á fila e 'busca' o elemento do inicio (i)
		
		for (x = g[v]; x; x = x->prox) // percorre os sucessores de v
			if (!visitados[x->destino]){ // se o destino de v ainda NÃO foi visitado
				
				q[f++] = x->destino; // acrescenta esse vértice á fila
				ant[x->destino] = v; // o vértice v é o anterior ao x->destino (logicamente)
				visitados[x->destino] = 1; // x->destino foi visitado aqui
			}
	}

	return i;
}




int succN(Grafo g, int v, int N){

	int q[NV], i, f, visitados[NV], dist[NV];
	struct aresta *x;

	for(i = 0; i < NV; i++)	visitados[i] = 0;

	i = f = 0; 
	q[f++] = v;
	visitados[v] = 1;
	dist[v] = 0;

	while(i != f){

		v = q[i];

		if (dist[v] > N) break;
		
		i++;

		for (x = g[v]; x; x = x->prox)
			if (!visitados[x->destino]){
				
				q[f++] = x->destino;
				visitados[x->destino] = 1;
				dist[x->destino] = dist[v] + 1;
			}
	}

	return i;
}



int depthFirstRec(Grafo g, int v, int ant[], int visitados[]){

	int count = 1;
	struct aresta *x;

	visitados[v] = 1;

	for (x = g[v]; x; x = x->prox)
		if (!visitados[x->destino]){
			
			ant[x->destino] = v;
			count += depthFirstRec(g, x->destino, ant, visitados);
		}

	return count;
}


int depthFirst(Grafo g, int v, int ant[]){

	int visitados[NV], i;

	for (i = 0; i < NV; i++){

		ant[i] = -1;
		visitados[i] = 0;
	}

	return depthFirstRec(g, v, ant, visitados);
}




int procuraRec(Grafo g, int o, int d, int visitados[]){

	int found = 0;
	struct aresta *x;

	visitados[o] = 1;
	
	if (o == d) found = 1; //encontrou um caminho, acaba a função
	else
		for (x = g[o]; x && !found; x = x->prox)
			if (!visitados[x->destino])
				found = procuraRec(g , x->destino, d, visitados);
	
	return found;
}



int procura(Grafo g, int o, int d){

	int visitados[NV], i;

	for (i = 0; i < NV; i++) visitados[i] = 0;

	return procuraRec(g, o, d, visitados);
}



// outras funções utéis ----------------------------------------------------------------------------------------

int naoAlcancavel(Grafo g, int o){

	//usando a travessia recursiva depthFirst

	int v, ant[NV];

	depthFirst(g, o, ant);

	ant[o] = o; 

	for (v = 0; v < NV; v++) if (ant[v] == -1) break;
	
	return v;
}



int naoAlcancavel2(Grafo g, int o){

	//usando a travessia imperativa breadthFirst

	int v, ant[NV];

	breadthFirst(g, o, ant);

	ant[o] = o; 

	for (v = 0; v < NV && ant[v] != -1; v++);
	
	return v;
}



int naoAlcancavel3(Grafo g, int o){

	//usando a função recursiva procura (variação da travessia depthFirst)

	int v;

	for (v = 0; v < NV; v++) 
		if (!procura(g, o, v)) break;

	return v;
}



// Caminho mais curto --------------------------------------------------------------------------------




void floydWarshall(Grafo g, int m[NV][NV], int c[NV][NV]){

	int i, o, d;
	struct aresta *x;

	// inicializar as matrizes m e c
	for (i = 0; i < NV; i++)
		for (o = 0; o < NV; o++){
			c[i][o] = -1;
			m[i][o] = INFINITY;
		}

	//colocar os pesos nas caixas certas
	for (i = 0; i < NV; i++)
		for (x = g[i]; x; x = x->prox)
			m[i][x->destino] = x->peso;

	for (i = 0; i < NV; i++)
		for (o = 0; o < NV; o++)
			if (m[o][i] != INFINITY)
				for (d = 0; d < NV; d++)
					if (m[i][d] != INFINITY)
						if (m[o][d] > m[o][i] + m[i][d]) m[o][d] = m[o][i] + m[i][d];
}




void imprimeCaminho(int m[NV][NV], int c[NV][NV], int o, int d){

	if (c[o][d] == -1) printf("%d - %d - %d\n", o, m[o][d], d);
	
	else{
		
		imprimeCaminho(m, c, o, c[o][d]);
		imprimeCaminho(m, c, c[o][d], d);
	}
}

//------------------------------------------------------------------------------------------------


int main(){

	//printMatrix(A);

	Grafo B;
	matToLista(A, B);
	printGrafo(B);

	/*
	GrafoM C;
	listaToMat(B, C); // aqui a mat C == mat A
	printMatrix(C); 

	int v = 3;
	printf("capacidade de entrada no vertice %d --> %d\n\n", v, capacidadeIn(B, v) );
	printf("capacidade de saida no vertice %d --> %d\n\n", v, capacidadeOut(B, v) );
	printf("capacidade total (In - Out) do vertice %d --> %d\n\n", v, capacidade(B, v) );
	
	printf("vertice com maior capacidade total do grafo B --> %d \n\n", vMaxCap(B) );
	printf("vertice com maior capacidade total do grafo B --> %d (versao INEFICIENTE)\n\n", vMaxCap_Ineficiente(B) );

	int ant[NV];
	int v2 = 0;
	printf("maximo alcance/ nº de vertices atingidos pelo vertice %d --> %d\n\n", v2, breadthFirst(B, v2, ant));
	printArray(ant, NV);

	*/
	int v = 3;
	int dist = 1;
	printf("succN de %d com dist = %d --> %d\n\n", v, dist, succN(B, v, dist));

	printf("%d nao e alcancavel por %d\n\n",  naoAlcancavel(B, 0), v);

	printf("%d nao e alcancavel2 por %d\n\n",  naoAlcancavel2(B, 0), v);

	printf("%d nao e alcancavel3 por %d\n\n",  naoAlcancavel3(B, 0), v);



	/*
	int m[NV][NV], c[NV][NV];

	Grafo E;
	matToLista(D, E);

	floydWarshall(E, m, c);

	int origem = 1;
	int destino = 7;
	imprimeCaminho(m, c, origem, destino);
	putchar('\n');

	int some = procura(B, origem, destino);
	printf("%d\n\n", some);
	*/
	return 0;
}