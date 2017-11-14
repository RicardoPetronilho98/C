#include <stdio.h>

void printArray(int a[], int N){

	int i;

	for (i = 0; i < N; i++) printf("%d ", a[i]);
	putchar('\n');
}



void swap(int a[], int x, int y){

	int temp = a[x];
	a[x] = a[y];
	a[y] = temp;
}



int partition(int v[], int l, int h){
	
	int i = l; //posicao do primeiro elemento maior que pivot
	int j = l; //posicao do primeiro elemento nao tratado
	
	// pivot: v[h] (ultimo elemento)
	while (j < h - 1){
		if (v[j] < v[h]) swap(v, i++, j++);
		else j++;
	}

	swap(v, i, h); //coloca pivot entre as duas partes
	
	return i;
}


void qsortAux(int v[], int a, int b){

	int p;

	if (a < b){
		p = partition (v, a, b);
		qsortAux (v , a , p - 1);
		qsortAux (v, p + 1, b);
	}	
}


void qSort(int v[], int N){
	
	qsortAux (v , 0, N - 1);
}


int main(){

	int N = 9;
	int a[] = { 7, 12, 1, -2, 15, 0, 4, 11, 9};

	printf("\nUnsorted array is:  "); printArray(a, N);

	qSort( a, N);

	printf("\nSorted array is:  "); printArray(a, N); putchar('\n');
	
	return 0;
}