/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(){

	int nprocs = 3; // Lanzamos 20 procesos
	int childpid;
	int i;

	/* En la siguiente jerarquía, el proceso padre termina, pero el hijo sigue, y como tiene la misma
	estructura de datos, cada hijo produce otro y se cierra. Así hasta terminar el bucle.
	*/

	/*
	Jerarquía de procesos tipo 1
	*/
	pid_t id_proceso = getpid();
	printf("PID padre %d\n\n", id_proceso);
	for (i=1; i < nprocs; i++) {
		if (childpid == 0){
				printf("\n[*1*] Comienzo del bucle soy HIJO-> %d\n", i); 
		} else {
				printf("\n[*1*] Comienzo del bucle soy PADRE-> %d\n", i); 
		}

		if ((childpid= fork()) == -1) {
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(-1);
		} 

		if(childpid == 0){ // Si es el hijo...
			pid_t id_proceso;
			pid_t id_padre;

			id_proceso = getpid();
			id_padre = getppid();
			
			printf("[1] Identificador de proceso: %d\n", id_proceso);
			printf("[1] Identificador del proceso padre: %d\n", id_padre);
		}

		pid_t id_proceso;
		id_proceso = getpid();
		if (childpid){
			if (childpid == 0){
				printf("[*1*] Proceso HIJO va a cerrar!-> %d\n", i); 
				printf("[*1*] HIJO con PID -> %d\n", id_proceso);
			} else {
				printf("[*1*] Proceso PADRE va a cerrar!-> %d\n", i); 
				printf("[*1*] PADRE con PID -> %d\n", id_proceso);
			}
			
			break;
		}
		
	}

	/* El programa acaba cuando llega un hijo ya que hace break si el childpid es 

	*/

	/*
	Jerarquía de procesos tipo 2
	*/
	/*pid_t id_proceso = getpid();
	printf("PID padre %d\n\n", id_proceso);
	for (i=1; i < nprocs; i++) {
		if (childpid == 0){
				printf("\n[*2*] Comienzo del bucle soy HIJO-> %d\n", i); 
		} else {
				printf("\n[*2*] Comienzo del bucle soy PADRE-> %d\n", i); 
		}

		if ((childpid= fork()) == -1) {
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(-1);
		}

		if(childpid == 0){ // Si es el hijo...
			pid_t id_proceso;
			pid_t id_padre;

			id_proceso = getpid();
			id_padre = getppid();
			
			printf("[2] Identificador de proceso: %d\n", id_proceso);
			printf("[2] Identificador del proceso padre: %d\n", id_padre);
		}

		pid_t id_proceso;
		id_proceso = getpid();
		if (!childpid)
			if (childpid == 0){
				printf("[*2*] Proceso HIJO va a cerrar!-> %d\n", i); 
				printf("[*2*] HIJO con PID -> %d\n", id_proceso);
			} else {
				printf("[*2*] Proceso PADRE va a cerrar!-> %d\n", i); 
				printf("[*2*] PADRE con PID -> %d\n", id_proceso);
			}
			break;
	}*/

}