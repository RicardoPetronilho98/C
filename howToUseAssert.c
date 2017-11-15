#include <assert.h>
#include <stdio.h>

int mod(int x, int y);
int hasSomeAssert(int y, int r, int x);
/*
	esta função - hasSomeAssert - serve para verificar a validade de 
	uma expressão com um quantificador existencial:

	(exists q >= 0 : q * y + r = x)
*/


int main(){

	int x = 27, y = 5;
	printf("\nMod %d %d = %d\n\n", x, y, mod(x, y));
	return 0;
}


int hasSomeAssert(int y, int r, int x){

	int q = 0;
	int res = 0;

	while (q <= x){

		if (q * y + r == x){ 
			
			res = 1; 
			break;
		}

		q++;
	}

	return res;
}



int mod(int x, int y){
	
	assert(x >= 0 && y > 0); //pré-condição do programa

	int r = x;
	
	assert(x >= 0 && y > 0 && r == x); //pré-condição do ciclo While
	
	while (r >= y) {
		
		assert(r >= 0 && hasSomeAssert(y, r, x) == 1); // isto é o Invariante
		r = r - y;

	}
	
	assert(0 <= r && r < y && hasSomeAssert(y, r, x) == 1); //prós-condição do programa
	
	return r;
}

