#include <stdio.h>
#include <math.h>

long long intBinaryToDecimal(long long n); //function prototype
long long stringBinaryToDecimal(char n[]); //function prototype

int main(){
    
    long long n1;
   	char n2[128];
    
    printf("\nUsing - INT - input:");
    printf("\nEnter a binary number: ");
    scanf("%lld", &n1);
    printf("%lld in binary = %lld in decimal\n\n", n1, intBinaryToDecimal(n1));

    printf("Using - STRING - input:");
    printf("\nEnter a binary number: ");
    scanf("%s", n2);
    printf("%s in binary = %lld in decimal\n\n", n2, stringBinaryToDecimal(n2));
    
    return 0;
}



long long intBinaryToDecimal(long long n){

	int decimalNumber = 0, i = 0, r;
    
    while (n != 0){
        
        r = n % 10; //remainder
        n /= 10;
        decimalNumber += r * pow(2, i);
        ++i;
    }

    return decimalNumber;
}



long long stringBinaryToDecimal(char n[]){

	int decimalNumber = 0, i, N;

	for (N = 0; n[N]; N++); // N ---> length da string 
	N--;

	for (i = 0; n[i]; i++){

		decimalNumber += (int) (n[i] - '0') * pow(2, N);
		N--;
	}

	return decimalNumber;
}

