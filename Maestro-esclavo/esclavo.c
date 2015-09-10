/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

/*
esclavo
compilar con: gcc -o esclavo esclavo.cpp -lm
*/

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <string.h>


int main(int argc, char * argv[]){

	int minimo = atoi(argv[1]);
	int maximo = atoi(argv[2]);

	int i,k;
	int primo;

	int tope;

	
	for (i=minimo;i<=maximo;i++){
		primo = 1;
		tope = sqrt(i);
		for (k=2; k <= tope && primo; k++){ //comprobamos que sea primo
			primo = (i % k) != 0;
		}

		if (primo){
			write(1, &i,sizeof(int));
		}
		
	}
	

	return 0;
}