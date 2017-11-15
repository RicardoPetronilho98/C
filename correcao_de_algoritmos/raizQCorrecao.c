#include <assert.h>
#include <stdio.h>

int raizQ(int n);


int main(){

	int n = 144;

	printf("\nraizQ de %d = %d\n\n", n, raizQ(n));
	
	return 0;
}



int raizQ(int n){

	int n0 = n; // variável lógica apenas para guardar o valor inicial de n

	assert(n == n0 && n > 0); // pré-condição do programa
	
	int r = 1;

	assert(n == n0 && n >= 0 && r == 1); // pré-condição do ciclo While

	while (r * r < n){

		assert(n == n0 && n >= 0 && (r - 1) * (r - 1) <= n); // Invariante
		
		r = r + 1;
	}

	assert(n == n0 && n >= 0 && (r - 1) * (r - 1) <= n && r * r >= n); // pós-condição do ciclo While
	
	if (r * r > n) r = r - 1;
	
	assert(r * r <= n0 && (r + 1) * (r + 1) > n0); // pós-condição do programa

	return r;
}
