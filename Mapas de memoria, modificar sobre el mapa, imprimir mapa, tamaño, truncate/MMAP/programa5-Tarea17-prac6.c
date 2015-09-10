/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

/*
MEMORIA ANONIMO - SIN ARCHIVO
La memoria se
inicializa a cero. Esta forma está en desuso (en Linux se implementa a través de
/dev/zero)

*/
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main (int argc, char *argv[]){
        
  char *p;
  
  // Pomnemos a -1 el fd y ponemos la bandera MAP_ANON
  p = (char *) mmap (0, sizeof(char), PROT_READ, MAP_SHARED | MAP_ANON, -1, 0);
  if (p == MAP_FAILED) {
       printf("Fallo el mapeo\n");
       return 1;
  }
  return 0;
}
					  
