/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv){
	
	if (argc != 4){
		perror("Syntax error: orden \"<\"\">\" archivo"); 
		exit(1);
	}

	char * orden = argv[1];
	char * redireccion = argv[2];
	char * archivo = argv[3];

	int fd, error;

	/*
	"<"" --> cambia la entrada estándar por el fichero, todo lo que hay en el fichero sale a la consola
	(Hace un execlp(sort,"", NULL)) -> Coge los datos de la entrada (el fichero) y lo muestra por la salida extandar (la consola)
	*/
	if (strcmp(redireccion,"<") == 0){
		//Redireccionamos la entrada
		int fd = open (archivo, O_RDONLY); // Abrimos el descriptor de fichero en solo lectura
		close(STDIN_FILENO); // Cerramos la entrada estándar para asegurarnos de que esté libre
		error = fcntl(fd, F_DUPFD, STDIN_FILENO); // Ajustamos la entrada estándar con el fichero
		// Ahora la entrada estándar es el fichero
		execlp(orden,"", NULL); //Ejecutamos la orden



	} else if (strcmp(redireccion,">") == 0){
		//Redireccionamos la entrada
		int fd = open (archivo, O_WRONLY); // Abrimos el descriptor de fichero en solo escritura
		close(1); // Cerramos la salida estándar para asegurarnos de que esté libre
		error = fcntl(fd, F_DUPFD, 1); // Ajustamos la salida estándar con el fichero
		char bufer[256];
		execlp(orden,"", NULL); //Ejecutamos la orden
	}

	if (error == -1)
		perror("Ocurrió un error");
	

}
