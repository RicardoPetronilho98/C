#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void programa(int n);
int fib (int n);



int main(){
	
	programa(10);

	puts("\nSe está a ler isto é porque o programa está correto, otherwise o programa breakava a meio e não aparecia this message!\n");
	
	return 0;
}



int fib (int n){
	
	if (n == 0 || n == 1) return n;
	else return fib(n - 1) + fib(n - 2);
}



void programa(int n){

	int n0 = n; //variável lógica apenas para guardar o valor inicial de n 

	assert(n == n0 && n > 0); //pré-condição do programa
	
	int x = 1; 
	int y = 0;
	
	assert(n == n0 && n > 0 && x == 1 && y == 0); //pré-condição do ciclo While
	
	while (n > 1) {

		assert(x == fib (n0 - n + 1) && y == fib (n0 - n) && n >= 1); //Invariante
		
		x = x + y; 
		y = x - y; 
		n = n - 1;
	}
	
	assert(x == fib (n0)); //pós-condição do programa
}
