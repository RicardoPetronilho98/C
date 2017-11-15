#include <assert.h>
#include <stdio.h>

int minArray(int v[], int N);
int oneMinArray(int a, int b, int v[], int r);



int main(){

	int N = 6;
	int a[] = {7, 3, 5, -2, 1, 0};

	printf( "\nmin = %d\n\n", a[ minArray(a, N) ] );
	
	return 0;
}




int oneMinArray(int a, int b, int v[], int r){

	int i, res = 1;

	for (i = a; i < b; i++){
		
		if (v[i] >= v[r]) continue;
		
		else{
			res = 0;
			break;
		}
	}

	return res;
}




int minArray(int v[], int N){

	assert(N > 0); // pré-condição do programa
	
	int r = 0; 
	int i = 1;

	assert(N > 0 && r == 0 && i == 1); // pré-condição do ciclo While
	
	while (i < N) {

		// forall (0<=k<i) v[k] >= v[r] && i <= N
		assert(oneMinArray(0, i, v, r) == 1 && i <= N); // Invariante

		if (v[i] < v[r]) r = i;
		
		i = i + 1;
	}
	
	// forall (0<=k<N) v[k] >= v[r] 
	assert(oneMinArray(0, N, v, r) == 1); // pós-condição do programa

	return r;
}
