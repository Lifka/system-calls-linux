/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

/*
tarea5.c
Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX
2.10
*/
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	pid_t pid;
	int estado;

	// Creamos un hijo
	if( (pid=fork())<0) {
		perror("\nError en el fork");
		exit(-1);

	} else if(pid==0) { //proceso hijo ejecutando el programa

/*
       ldd  prints  the  shared  libraries  required by each program or shared
       library specified on the command line.
*/
		// Ese hijo lo convertimos en ldd (da la información sobre las bibliotecas que requiere o comparte)
       // Como primer argumento especificamos la ruta donde se encuentra, y a continuación los argumentos, de forma que se ejecute sobre ./tarea5
		if( (execl("/usr/bin/ldd","ldd","./ejer3",NULL)<0)) {
			perror("\nError en el execl");
			exit(-1);
		}

	}

	wait(&estado);
	/*
	<estado> mantiene información codificada a nivel de bit sobre el motivo de
	finalización del proceso hijo que puede ser el número de señal o 0 si alcanzó
	su finalización normalmente.
	Mediante la variable estado de wait(), el proceso padre recupera el valor
	especificado por el proceso hijo como argumento de la llamada exit(), pero
	desplazado 1 byte porque el sistema incluye en el byte menos significativo el
	código de la señal que puede estar asociada a la terminación del hijo. Por eso
	se utiliza estado>>8 de forma que obtenemos el valor del argumento del exit()
	del hijo.
	*/
	printf("\nMi hijo %d ha finalizado con el estado %d\n",pid,estado>>8);
	exit(0);
}
