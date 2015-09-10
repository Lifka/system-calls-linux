/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

// Como cp

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main (int argc, char *argv[]){

	int fd, fd2;
	if (argc != 3){
		perror("Syntax error: ./ejer5 archivo1 archivo2");
		exit(1);
	}

    umask(0); // Para que no diga permiso denegado

	// Abrimos el primer fichero
	fd = open(argv[1], O_RDONLY, S_IRWXU);
	if (fd == -1) {
            printf("Error al abrir archivo %s\n", argv[1]);
            exit(1);
    }

  	// Cogemos su tamaño con stat
  	struct stat buf;
  	if ( stat(argv[1], &buf) == -1){
		perror(argv[1]);
		exit(1);
	}

	// Abrimos el segundo fichero o lo creamos
	fd2 = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
    if (fd2 == -1) {
            printf("Error al abrir archivo de destino %s\n", argv[2]);
    	exit(1);
    }

    // Hacemos espacio
    ftruncate(fd2, buf.st_size);

	// Creamos el mapa para el descriptor de origen
	char *mOrigen = (char *) mmap (0, buf.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (mOrigen == MAP_FAILED) {
		perror("Fallo la proyeccion1");
		exit(-1);
	}

	// Abrimos otro mapa para el descriptor de origen
	char *mDestino = (char *) mmap (0, buf.st_size, PROT_WRITE, MAP_SHARED, fd2, 0);
	if (mDestino == MAP_FAILED) {
		perror("Fallo la proyeccion2");
		exit(-1);
	}
	// DEBUG:
	//printf("%s",mOrigen);
	//printf("%d",buf.st_size);

	// Copiamos...
	memcpy(mDestino,mOrigen, buf.st_size);	

	 if (munmap (mOrigen, buf.st_size) == -1) {//cerrar la proyeccion.
		printf("Error al cerrar la proyeccion \n");
		exit(-1);
	}
	if (munmap (mDestino, buf.st_size) == -1) {//cerrar la proyeccion.
		printf("Error al cerrar la proyeccion \n");
		exit(-1);
	}

}