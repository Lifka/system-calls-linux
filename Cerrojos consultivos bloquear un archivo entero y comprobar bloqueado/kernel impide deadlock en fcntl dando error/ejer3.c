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
	
	struct flock cerrojo1;
	struct flock cerrojo2;
	pid_t  pid;

	// Lanzamos hijo
    pid = fork();

	int fd1 = open ("locks",  O_CREAT|O_WRONLY);
    cerrojo1.l_type = F_WRLCK; // Cerrojo de escritura
	cerrojo1.l_whence = SEEK_SET; // El inicio es el inicio
	cerrojo1.l_start = 0; // Empezamos desde la pos cero a contar desde el incio
	cerrojo1.l_len = 0; // Bloqueamos hasta EOF

	int fd2 = open ("locks2",  O_CREAT|O_WRONLY);
    cerrojo2.l_type = F_WRLCK; // Cerrojo de escritura
	cerrojo2.l_whence = SEEK_SET; // El inicio es el inicio
	cerrojo2.l_start = 0; // Empezamos desde la pos cero a contar desde el incio
	cerrojo2.l_len = 0; // Bloqueamos hasta EOF

	if (pid == 0){
		if (fcntl (fd2, F_SETLKW, &cerrojo2) == -1)
			printf("Error al crear cerrojo2 en hijo\n");

		if (fcntl (fd1, F_SETLKW, &cerrojo1) == -1)
			printf("Error al crear cerrojo1 en hijo\n");
	} else {
		if (fcntl (fd1, F_SETLKW, &cerrojo1) == -1)
			printf("Error al crear cerrojo1 en padre\n");


		if (fcntl (fd2, F_SETLKW, &cerrojo2) == -1)
			printf("Error al crear cerrojo2 en padre\n");
	}


/*
	if (fcntl (fd, F_SETLKW, &cerrojo) == -1)
		if (pid == 0)
			printf("Error al crear cerrojo en hijo",pid);
		else
			printf("Error al crear cerrojo en padre -> %d\n",pid);
*/
	//sleep(1);
}
