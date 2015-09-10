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

int exclusionMutua(int a){
	struct flock cerrojo;
	int fd;
	char * file = "locks";

	if ((fd = open (file, O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR)) < 0){
		perror("Error en el archivo de exclusión mutua");
		exit(1);
	}
	
	if(a == 1){ // Bloquea
		cerrojo.l_type = F_WRLCK; // Cerrojo de escritura
		cerrojo.l_whence = SEEK_SET; // El inicio es el inicio
		cerrojo.l_start = 0; // Empezamos desde la pos cero a contar desde el incio
		cerrojo.l_len = 0; // Bloqueamos hasta EOF

		if (fcntl(fd, F_SETLKW, &cerrojo) == -1){
			perror("Bloqueo");
			exit(1);
		}

	} else {
		cerrojo.l_type =F_UNLCK;
		cerrojo.l_whence =SEEK_SET;
		cerrojo.l_start =0;
		cerrojo.l_len =0;

		if (fcntl(fd, F_SETLKW, &cerrojo) == -1){
			perror("Desbloqueo");
			exit(1);
		}
		unlink(file);
	}

	return fd;
}

int main(int argc, char ** argv){
	exclusionMutua(0);



}
