/*

********************************************

  Javier Izquierdo Vera
  javierizquierdovera@gmail.com
  UGR

********************************************

*/

#include <sys/types.h>
#include <unistd.h>		
#include <sys/stat.h>
#include <fcntl.h>		
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <memory.h>

/*


    struct stat
    {
        dev_t         st_dev;      /* dispositivo 
        ino_t         st_ino;      /* inodo 
        mode_t        st_mode;     /* proteccion 
        nlink_t       st_nlink;    /* numero de enlaces fisicos 
        uid_t         st_uid;      /* ID del usuario propietario 
        gid_t         st_gid;      /* ID del grupo propietario 
        dev_t         st_rdev;     /* tipo dispositivo (si es
                                      dispositivo inodo) 
        off_t         st_size;     /* tamaño total, en bytes 
        unsigned long st_blksize;  /* tamaño de bloque para el
                                      sistema de ficheros de E/S 
        unsigned long st_blocks;   /* numero de bloques asignados 
        time_t        st_atime;    /* hora ultimo acceso 
        time_t        st_mtime;    /* hora ultima modificacion 
        time_t        st_ctime;    /* hora ultimo cambio 
    };



*/

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

int sizeFileByte(char * file){

	int size = 0; // Si es un directorio devolveremos 0, ya que solo contamos si es archivo regular
	struct stat atributos;

  	if(stat(file,&atributos) < 0) {
		printf("\nError al intentar acceder a los atributos de %s", file);
		exit(-1);
	}

	// Si es un archivo regular lo contamos
	if(S_ISREG(atributos.st_mode)){

		size = atributos.st_size;
		
	}

	return size;
}



void RecorrerDirectorio(char * raiz){
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
			
    		int a = sizeFileByte(ObtenerRuta(raiz,ent->d_name));
    		printf("tam %s = %d\n",ent->d_name,a);
		}

	}

	// Cerramos el directorio
  	if (closedir (dir) != 0){
  		perror("Pathname error");
		exit(EXIT_FAILURE);
  	}

}

struct pair{
	char* file;
	int size;
};


// Devuelve un vector de pares con el nombre y el tamaño de los archivos
void getFilesOf(char * raiz, struct pair* archivos, int* total){
	*total = 0;
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
			
    			struct pair archivo;
				archivo.file = ent->d_name;
				archivo.size = sizeFileByte(ObtenerRuta(raiz,ent->d_name));

				archivos[*total] = archivo;
				(*total)++;
		}

	}

	// Cerramos el directorio
  	if (closedir (dir) != 0){
  		perror("Pathname error");
		exit(EXIT_FAILURE);
  	}

}



int main(int argc, char ** argv){

	struct pair archivos[50];
	int total;
	getFilesOf(".", archivos,&total);

	int i;
	for(i = 0; i < total; i++)
		printf("%d: %s - %d\n", i, archivos[i].file, archivos[i].size);


}