/*

********************************************

  Javier Izquierdo Vera
  javierizquierdovera@gmail.com
  UGR

********************************************

*/

/*
MEMORIA ANONIMO - SIN ARCHIVO
La mayoría de sistemas suministran el seudo-dispositivo /dev/zero que tras
abrirlo y leerlo suministra tantos ceros como le indiquemos, y cualquier cosa que
escribamos en él es descartada. Su uso se ilustra en el programa Tarea18.c

*/

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main (int argc, char *argv[]){
        
  int fd;
  char *p;
  
  // Abrimos el seudo-dispositivo /dev/zero
  fd = open("/dev/zero", O_RDONLY);
  
  p = (char *) mmap (0, sizeof(int), PROT_READ , MAP_SHARED, fd, 0);
  if (p == MAP_FAILED) {
       printf("Fallo el mapeo\n");
       return 1;
  }
  close(fd);
  return 0;
}
					  
