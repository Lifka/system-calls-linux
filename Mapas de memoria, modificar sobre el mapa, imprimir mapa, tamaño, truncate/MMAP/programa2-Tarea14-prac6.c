/*

********************************************

  Javier Izquierdo Vera
  javierizquierdovera@gmail.com
  UGR

********************************************

*/

/*
crea un archivo denominado Archivo y los rellena con nulos. Tras lo cual, crea una proyección
compartida del archivo para que los cambios se mantengan. Una vez establecida la
proyección, copia en la memoria asignada a la misma el mensaje “Hola Mundo\n”. Tras
finalizar el programa, podemos visualizar el archivo para ver cual es el contenido: la cadena
“Hola Mundo\n”
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

const int MMAPSIZE=1024;

int main(){
 
  int fd, num, i;
  char ch='\0'; // NOP -> Valor nulo
  char *memoria;
  umask(0);

  fd = open("Archivo", O_RDWR|O_CREAT|O_EXCL, S_IRWXU);

  if (fd == -1) {
    perror("El archivo existe");
    exit(1);
  }

  // Rellenamos el atchivo con valores nulos antes de empezar
 for (i=0; i < MMAPSIZE; i++){
      num=write(fd, &ch, sizeof(char));

      if (num!=1) 
        printf("Error escritura\n");
  }

  // Proyectamos sobre la memoria 
  // Tamaño 1024 MMAPSIZE
  // PROT_READ|PROT_WRITE --> Se puede leer y escribir
  // MAP_SHARED -> La modificación es visible para todos
  memoria = (char *)mmap(0, MMAPSIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

  if (memoria == MAP_FAILED) {
      perror("Fallo la proyeccion");
      exit(2);
  }
 
  close(fd);  /* ya no es necesario el descriptor*/
  strcpy(memoria, "hola mundo\n");  /* copia la cadena en la proyeccion */
  exit(0);
}
