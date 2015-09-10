/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

/*
Pprograma en C que tenga como argumento un número entero.
Este programa debe crear un proceso hijo que se encargará de comprobar si dicho número es
un número par o impar e informará al usuario con un mensaje que se enviará por la salida
estándar. A su vez, el proceso padre comprobará si dicho número es divisible por 4, e
informará si lo es o no usando igualmente la salida estándar.

*/
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	if (argc!=2){
		perror("Syntax error: ./ejer1 <int>");
		exit(EXIT_FAILURE);
	}

	int value = strtol(argv[1], NULL, 10);

	int hijo1 = fork();

	if(hijo1 == 0){ //Si hijo es = a 0, es que estamos en el hijo, si > 0, en el padre (contiene el PID)
		int par = (value % 2) == 0;
		
		if (par)
			printf("Es par\n");
		else
			printf("Es impar\n");
	} else if (hijo1 > 0){
		int por_4 = (value % 4) == 0;

		if (por_4)
			printf("Es divisible por 4\n");
		else
			printf("No es divisible por 4\n");
	}
}	


