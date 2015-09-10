/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

char buf[80];

int main(int argc, char *argv[])
{
int fd, fd2;

if (argc != 2)
		perror("\nSyntax error: ./2 <file>");

if( (fd=open(argv[1],O_RDONLY,S_IRUSR|S_IWUSR))<0) {
	perror("\nError en open");
	exit(EXIT_FAILURE);
}

if( (fd2=open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
	perror("\nError en open");
	exit(EXIT_FAILURE);
}

int contador = 0;
int tam = 0;
int tam_total = 0;

// Espacio para el número de bloques
if(lseek(fd2,28,SEEK_SET) < 28) {
	perror("\nError en lseek");
	exit(EXIT_FAILURE);
}


while(tam = read(fd,buf,80)){
	contador++;
	tam_total += tam;

	char e = contador + '0';
	char msg[10] = "\nBloque ";
	msg[8] = e;
	msg[9] = '\0';


	if(write(fd2,"\nBloque ",8) != 8) {
		perror("\nError en write 1");
		exit(EXIT_FAILURE);
	}

	//Cifras
	int cifras0 = 1;
	int aux0 = contador;
	while((aux0 = aux0 / 10) && (aux0 > 0))
		cifras0++;

	//char to int
	char msg0[cifras0];
	sprintf(msg0, "%d", contador);

	if(write(fd2,msg0,sizeof(msg0)) != sizeof(msg0)) {
		perror("\nError en write 1");
		exit(EXIT_FAILURE);
	}

	if(write(fd2,"\n",1) != 1) {
		perror("\nError en write 3");
		exit(EXIT_FAILURE);
	}

	if(write(fd2,buf,tam) != tam) {
		perror("\nError en write 2");
		exit(EXIT_FAILURE);
	}

}

//Número de bloques:
//Nos vamos al principio
if(lseek(fd2,0,SEEK_SET) < 0) {
	perror("\nError en lseek");
	exit(EXIT_FAILURE);
}


//Cifras
int cifras = 1;
int aux = tam_total;
while((aux = aux / 10) && (aux > 0))
	cifras++;

//char to int
char msg2[cifras];
sprintf(msg2, "%d", tam_total);


// Lo escribimos
if(write(fd2,"El número de bloques es ",25) != 25) {
	perror("\nError en write último");
	exit(EXIT_FAILURE);
}

// Lo escribimos
if(write(fd2,msg2,sizeof(msg2)) != sizeof(msg2)) {
	perror("\nError en write último");
	exit(EXIT_FAILURE);
}

return EXIT_SUCCESS;
}
