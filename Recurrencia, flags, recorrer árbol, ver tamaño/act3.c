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

void Procesar(char * raiz, unsigned int* total,unsigned int* size){
	struct dirent *ent; // Los punteros de readdir se guardan en un tipo struct dirent
   	DIR *dir = opendir(raiz);


   	// Directorio ****
	if (dir == NULL){ // Miramos que no haya error
    	perror("Pathname error");
		exit(EXIT_FAILURE);
    }

    while ((ent = readdir (dir)) != NULL){ // Si == NULL => Error o final
   	//Ver de qué tipo es

    	if ((strcmp(ent->d_name,"..") != 0) && (strcmp(ent->d_name,".") != 0)){ // Ignoramos .. y .
			
			struct stat atributos;

	    	if(stat(ObtenerRuta(raiz,ent->d_name),&atributos) < 0) {
				printf("\nError al intentar acceder a los atributos de ");
				printf(ent->d_name);
				perror("\nError en lstat");
				exit(-1);
			}

			// Si es un archivo regular lo contamos
			if(S_ISREG(atributos.st_mode)){

				// detectamos si están activados los flags de permiso de ejecución para el grupo y para otros
				if((atributos.st_mode & S_IXGRP) && (atributos.st_mode & S_IXOTH)){
					*total = *total + 1;
					*size = *size + atributos.st_size;
					printf(ObtenerRuta(raiz,ent->d_name));
					printf(" ");
					printf("%d",ent->d_ino);
					printf("\n");
				}

			} else if(S_ISDIR(atributos.st_mode)){ // Si es un directorio -> entra
				
				Procesar(ObtenerRuta(raiz,ent->d_name),total,size); // Recurrencia para que haga lo mismo con todas las ramas
			
			}
		}

	}

	// Cerramos el directorio
  	if (closedir (dir) != 0){
  		perror("Pathname error");
		exit(EXIT_FAILURE);
  	}

}

int main(int argc, char *argv[]) {
	char * directorio = 0;

	if (argc == 2){
		 directorio = argv[1]; // Con un puntero a DIR abriremos el directorio
	} else
		directorio = ".";

	// Vamos a usar el paso por referencia...
	unsigned int total = 0; 
	unsigned int size = 0;

	printf("Los i-nodos son:\n");
   	Procesar(directorio, &total, &size);

   	printf("\nExisten ");
	printf("%d",total);
	printf(" archivos regulares con permiso x para grupo y otros.\n");

	printf("El tamaño total ocupado por dichos archivos es ");
	printf("%d",size);
	printf(" bytes\n");
}
