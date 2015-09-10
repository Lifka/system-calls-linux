/*

********************************************

  Javier Izquierdo Vera
  javierizquierdovera@gmail.com
  UGR

********************************************

*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>

#include<stdlib.h>

// Directorios
#include<sys/types.h>
#include<dirent.h>

// Obtener ruta
#include<memory.h>

char * ObtenerRuta(char * ruta, char * archivo){
    	// Obtenemos la ruta completa...
      	char * temp = (char *) malloc(2 + strlen(ruta)+ strlen(archivo) ); // Tamaño + 1

      	//Copiamos ruta
      	strcpy(temp, ruta);
      	//Metemos la barra
      	strcat(temp, "/");
      	//Metemos el archivo
      	strcat(temp, archivo);

      	return temp;
}

char * SystemMostrarPermisos(char * archivo){
		// Comando :
		char * command = (char *) malloc(strlen(archivo)+50);
		strcpy(command, "ls -l ");
		strcat(command, archivo);
		strcat(command, " | cut -d \" \" -f 1");

   		FILE *in=NULL;

   		char * resultado = (char *) malloc(11);
   
   		in=popen(command, "r");
   		fgets(resultado, 11, in);
   		return resultado;
}

void ProcesarArchivo(char * archivo, long int octal){
		// Salida 
		printf(archivo);
		printf(" : ");

      	// Procesamos el archivo ****

		char * permidos_antes = SystemMostrarPermisos(archivo);

		// Cambiar permisos y salida
      	if(chmod(archivo,octal) < 0){
      		printf("<errno>");
      		printf(" ");
      		printf(permidos_antes);
      	} else {
      		printf(permidos_antes);
      		printf(" ");
      		printf(SystemMostrarPermisos(archivo));
      	}
      	printf("\n");


}

int main(int argc, char *argv[]) {

	if (argc != 3){
		perror("Syntax error: ./act2 <pathname> <4_digits_octal>");
		exit(EXIT_FAILURE);
	}

	// Número ****
	long int octal = strtol(argv[2], NULL, 8); // Convierte string a int en base 8 (si no es long no funciona)

	printf("-> Octal recibido: ");
	printf("%d\n",octal); 

	// Directorio ****
	DIR *dir = opendir(argv[1]); // Con un puntero a DIR abriremos el directorio
 	if (dir == NULL){ // Miramos que no haya error
    	perror("Pathname error");
		exit(EXIT_FAILURE);
    }

    // Leer archivos ****
    struct dirent *ent; // Los punteros de readdir se guardan en un tipo struct dirent
    while ((ent = readdir (dir)) != NULL){ // Si == NULL => Error o final

    	if ((strcmp(ent->d_name,"..") != 0) && (strcmp(ent->d_name,".") != 0)){ // Ignoramos .. y .
    		char * temp = ObtenerRuta(argv[1], ent->d_name);
    		ProcesarArchivo(temp, octal);
    	}

    }

    // Cerramos el directorio
  	if (closedir (dir) != 0){
  		perror("Pathname error");
		exit(EXIT_FAILURE);
  	}

	return 0;
}