#include <stdio.h>
#define pai(x)		(int) ((x-1) / 2)
#define esq(x)		(int) (2 * x + 1)
#define dir(x) 		(int) (2 * x + 2)


void swap(int a[], int x, int y){

	int temp = a[x];
	a[x] = a[y];
	a[y] = temp;
}


void bubbleUp(int heap[], int i){

	int p = pai(i);

	while (i > 0 && heap[p] > heap[i]){
		swap(heap, i, p);
		i = p; p = pai(i);
	}
}


void bubbleDown(int heap[], int N, int i){

	int f = esq(i);

	while(f < N){

		if(f + 1 < N && heap[f + 1] < heap[f]) f = f + 1;

		if (heap[i] <= heap[f]) break;

		swap(heap, i, f);
		i = f;
		f = esq(i); 
	}
}


void bubbleSort(int a[], int N){ //custo: N * log2 (N)

	int i;

	for (i = 1; i < N; i++) bubbleUp(a, i); 

 	//função nao acabada
}



void printArray(int a[], int N){

	int i;

	for (i = 0; i < N; i++) printf("%d ", a[i]);
	putchar('\n');
}



int main(){
	
	putchar('\n');

	//exemplo do - bubbleDown - em execução ---> puxa o (10) para baixo:
	int N = 11;
	int heap1[] = {10, 2, 7, 5, 3, 11, 43, 8, 9, 4, 21};
	puts("efeito do bubbleDown: puxa o (10) para baixo");
	printf("antes  ---> "); printArray(heap1, N);
	bubbleDown(heap1, N, 0);
	printf("depois ---> "); printArray(heap1, N);
	//-----------------------------------------------------------------

	//exemplo do - bubbleUp - em execução ---> puxa o (-5) para cima:
	N = 12;
	int heap2[] = {1, 2, 7, 5, 3, 10, 43, 8, 9, 4, 21, -5};
	puts("\nefeito do bubbleUp: puxa o (-5) para cima");
	printf("antes  ---> "); printArray(heap2, N);
	bubbleUp(heap2, 11);
	printf("depois ---> "); printArray(heap2, N);
	//---------------------------------------------------------------

	//exemplo do - bubbleSorte - em execução ---> ordena o array:
	N = 11;
	int heap3[] = {1, 2, 7, 5, 3, 10, 43, 8, 9, 4, 21};
	puts("\nefeito do bubbleSort: ordena o array");
	printf("antes  ---> "); printArray(heap3, N);
	bubbleSort(heap3, N);
	printf("depois ---> "); printArray(heap3, N);
	//---------------------------------------------------------------
	putchar('\n');

	return 0;
}