/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

/*
El programa Tarea 13.3 toma uno o varios pathnames como argumento y, para cada uno de
los archivos especificados, se intenta un cerrojo consultivo del archivo completo. Si el bloqueo
falla, el programa escanea el archivo para mostrar la información sobre los cerrojos
existentes: el nombre del archivo, el PID del proceso que tiene bloqueada la región, el inicio y
longitud de la región bloqueada, y si es exclusivo (“w”) o compartido (“r”). El programa itera
hasta obtener el cerrojo, momento en el cual, se procesaría el archivo (esto se ha omitido) y,
finalmente, se libera el cerrojo.

*/

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc, char * argv[]) {

	// Creamos el cerrojo
	struct flock cerrojo;
	int fd;
	while (--argc > 0 ) {
		if ((fd=open(*++argv, O_RDWR)) == -1 ){
			perror("open fallo");
			continue;
		}

		cerrojo.l_type=F_WRLCK; // Cerrojo de escritura
		cerrojo.l_whence=SEEK_SET; // El inicio es el inicio
		cerrojo.l_start=0; // Empezamos desde la pos cero a contar desde el incio
		cerrojo.l_len=0; // Bloqueamos hasta EOF
		
		/* intentamos un bloqueo de escritura del archivo completo */

		while (fcntl (fd, F_SETLK, &cerrojo) == -1) { // -1 => fallo
			/* si el cerrojo falla, vemos quien lo bloquea */
			while (fcntl (fd, F_SETLK, &cerrojo) == -1 && cerrojo.l_type != F_UNLCK) {
				printf ("%s bloqueado por %d desde %d hasta %d para %c", *argv, cerrojo.l_pid, cerrojo.l_start, cerrojo.l_len, cerrojo.l_type==F_WRLCK ? 'w':'r');

			// Obtenemos una región fuera del cerrojo, al final:
			if (!cerrojo.l_len) 
				break;

			cerrojo.l_start += cerrojo.l_len;
			cerrojo.l_len = 0;
			} /*mientras existan cerrojos de otros procesos */
		} /*mientras el bloqueo no tenga exito */

		/* ahora el bloqueo tiene exito y podemos procesar el archivo*/
		printf ("procesando el archivo\n");
		/* una vez finalizado el trabajo, desbloqueamos el archivo entero*/
		cerrojo.l_type=F_UNLCK;
		cerrojo.l_whence=SEEK_SET;
		cerrojo.l_start=0;
		cerrojo.l_len=0;
		
		if (fcntl (fd, F_SETLKW, &cerrojo) == -1) 
			perror ("Desbloqueo");
		}

	return 0;
}
