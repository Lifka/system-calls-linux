/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

/*Programa que lanza cinco procesos hijo. Cada uno de ellos se
identificará en la salida estándar, mostrando un mensaje del tipo Soy el hijo PID. El
proceso padre simplemente tendrá que esperar la finalización de todos sus hijos y cada vez
que detecte la finalización de uno de sus hijos escribirá en la salida estándar un mensaje del
tipo:
Acaba de finalizar mi hijo con <PID>
Sólo me quedan <NUM_HIJOS> hijos vivos

*/

/*
pid_t waitpid(pid_t pid, int *status, int options);

STATUS

Si status no es NULL, waitpid almacena la información de estado en la memoria apuntada por
status.

    WIFEXITED(status): Es distinto de cero si el hijo terminó normalmente.
    WEXITSTATUS(status): Permite obtener el valor devuelto por el proceso hijo en la llamada exit o el valor devuelto en la función main, utilizando la sentencia return. Esta macro solamente puede ser tenida en cuenta si WIFEXITED devuelve un valor distinto de cero.
    WIFSIGNALED(status): Devuelve true si el proceso hijo terminó a causa de una señal no capturada.
    WTERMSIG(status): Devuelve el número de la señal que provocó la muerte del proceso hijo. Esta macro sólo puede ser evaluada si WIFSIGNALED devolvió un valor distinto de cero.
    WIFSTOPPED(status): Devuelve true si el proceso hijo que provocó el retorno está actualmente parado; esto solamente es posible si la llamada se hizo usando WUNTRACED o cuando el hijo está siendo rastreado.
    WSTOPSIG(status): Devuelve el número de la señal que provocó la parada del hijo. Esta macro solamente puede ser evaluada si WIFSTOPPED devolvió un valor distinto de cero.


Opciones:

    WNOHANG: Vuelve inmediatamente si ningún hijo ha terminado.

    WUNTRACED: El padre obtiene información adicional si el hijo recibe alguna de las señales

SIGINT, SIGTTOU, SIGSSTP, SIGTSTOP.

*/

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(){

	const int NPROCS = 5; // Lanzamos 5 procesos
	int childpid;
	int i;
	int vector_espera[NPROCS];
	int status[NPROCS];


	pid_t id_proceso = getpid();
	printf("Hola, soy el padre y tengo PID %d\nComencemos:\n\n", id_proceso);


	// Creamos los hijos
	for (i=0; i < NPROCS; i++) {
		if ((childpid= fork()) == -1) {
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(-1);
		}

		vector_espera[i] = childpid;// Lo añadimos al vector de espera

		if (childpid == 0){
			pid_t id_proceso = getpid();
			printf("Soy el hijo %d\n", id_proceso);
			i = NPROCS; //Evitamos que los hijos creen más hijos...
		}
	}


	// Esperar finalización
	if (childpid > 0){ // Soy el padre
		for(i = 0; i < NPROCS; i++){
		 	waitpid(vector_espera[i], &status[i], 0);
		 	//Detectar errores
		 	if (WIFEXITED(status[i]) == 0){
				printf("ERROR: El proceso %d no terminó correctamente", vector_espera[i]);
			} else {
			 	printf("\nAcaba de finalizar mi hijo con <%d>\n", vector_espera[i]);
				printf("Sólo me quedan <%d> hijos vivos\n", NPROCS-i-1);
			}
		}

	}

}