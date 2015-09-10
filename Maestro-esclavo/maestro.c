/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

/*
Ejercicio5: Programa que calcula los primos
*/

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){

	if (argc != 3){
		perror("ERROR: se necesita un intervalo\n");
		exit (-1);
	}

	char * minimo = argv[1];
	char * maximo = argv[2];

	int max1 = atoi(argv[2])/2;
	int min2 = atoi(argv[2])/2 + 1;

	// Transformamos la variable anterior a char *
	char max1_str[10];
	char min2_str[10];
	sprintf( max1_str, "%d", max1 );
	sprintf( min2_str, "%d", min2 );

	int fd0[2];
	int fd1[2];

	pid_t PID;

	pipe(fd0); // Llamada al sistema para crear un pipe para esclavo 1
	pipe(fd1); // Llamada al sistema para crear un pipe para esclavo 2

	
 	int i;
	for(i=1;i<=2;i++){
  		PID=fork(); 

  		if (!PID){
   			//Cerrar el descriptor de lectura de cauce en el proceso hijo
   			int error;
   			if (i==1){ // if hijo 1
				close(fd0[0]);
				dup2(fd0[1],1); // --> pone fd0[1] en el lugar de la salida_estandar cerrandolo previamente.
				error = execlp("./esclavo","esclavo",minimo,max1_str,NULL);
				
			}else{  // if hijo 2
				close(fd1[0]);
				dup2(fd1[1],1); // --> pone fd0[1] en el lugar de la salida_estandar cerrandolo previamente.
				error = execlp("./esclavo","esclavo",min2_str,maximo,NULL);
			}
			if (error == -1)
				perror ("Error!!!!");
			exit(0);
 		}
  
 	}


	
	 // sort. Proceso padre porque PID != 0.
	//Cerrar el descriptor de escritura en cauce situado en el proceso padre
	close(fd0[1]);
	close(fd1[1]);

	int j = 0;

	printf("---Primos del proceso 0--- \n");
	while(read(fd0[0],&j,sizeof(int)) > 0)
		printf("Primo recibido: %i\n",j);

	printf("---Primos del proceso 1--- \n");
	while(read(fd1[0],&j,sizeof(int)) > 0)
		printf("Primo recibido: %i\n",j);
		

	return(0);
}



