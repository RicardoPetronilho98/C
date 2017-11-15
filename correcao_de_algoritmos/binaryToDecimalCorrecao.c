#include <assert.h>
#include <stdio.h>
#include <math.h>

int binaryToDecimal(int a[], int N);
int sumArray(int a, int b, int v[]);


int main(){

	int N = 4;
	int a[] = {1, 0, 0, 1};

	int n = binaryToDecimal(a, N);

	printf("\n%d\n\n", n);
}



int sumArray(int a, int b, int v[]){

	int i, sum = 0;

	for (i = a; i <= b; i++) sum += v[i] * pow(2, i);;

	return sum;
}



int binaryToDecimal(int a[], int N){

	assert(N >= 0); // pré-condição do programa
	
	int n = 0; 
	int i = 0;

	assert(N >= 0 && n == 0 && i == 0); // pré-condição do ciclo While

	while (i < N){
		
		assert(n == sumArray(0, i - 1, a) && i <= N); // Invariante
		
		n = n * 2 + a[i];
		i = i + 1;
	}

	assert(n == sumArray(0, N - 1, a)); // pós-condição do programa

	return n;
}
