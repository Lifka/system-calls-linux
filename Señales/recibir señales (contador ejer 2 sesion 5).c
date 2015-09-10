/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

int vect[14];

static void manejador_func(int sigNum){
	vect[sigNum]++;
	printf("La señal %d se ha recibido %d veces\n",sigNum,vect[sigNum]);
}

int main(int argc, char *argv[]){
	int i;
	for(i = 0; i < 14; i++)
		vect[0] = 0;

	// Crea un sigaction 
	// sigaction => Establece la acción que realizará un proceso como respuesta a la recepción de una señal
	struct sigaction manejador;

	// Crea un buffer sobre la salida estándar de tipo _IONBF y tamaño 0
	// int setvbuf ( FILE * stream, char * buffer, int mode, size_t size );
	if(setvbuf(stdout,NULL,_IONBF,0)){
		perror("\nError en setvbuf");
	}

	//Inicializar la estructura manejador para especificar la nueva acción para la señal.
	// sa_handler => especifica la acción que se va a asociar con la señal signum
	manejador.sa_handler = manejador_func; // Nuestra función

	//'sigemptyset' inicia el conjunto de señales dado al conjunto vacío. 
	sigemptyset (&manejador.sa_mask);
	manejador.sa_flags = 0;
	
	// sigaction se emplea para cambiar la acción tomada por un proceso cuando recibe una determinada señal
	// *********** Establecer mi manejador particular de señal
	if( sigaction(SIGHUP,&manejador,NULL) <0)
		printf("\nNo puedo manejar la señal %d",SIGHUP);

	if( sigaction(SIGINT,&manejador,NULL) <0)
		printf("\nNo puedo manejar la señal %d",SIGINT);

	if( sigaction(SIGABRT,&manejador,NULL) <0)
		printf("\nNo puedo manejar la señal %d",SIGABRT);

	if( sigaction(SIGFPE,&manejador,NULL) <0)
		printf("\nNo puedo manejar la señal %d",SIGFPE);

	if( sigaction(SIGSEGV,&manejador,NULL) <0)
		printf("\nNo puedo manejar la señal %d",SIGSEGV);

	if( sigaction(SIGPIPE,&manejador,NULL) <0)
		printf("\nNo puedo manejar la señal %d",SIGPIPE);

	if( sigaction(SIGALRM,&manejador,NULL) <0)
		printf("\nNo puedo manejar la señal %d",SIGALRM);

	if( sigaction(SIGTERM,&manejador,NULL) <0)
		printf("\nNo puedo manejar la señal %d",SIGTERM);

	if( sigaction(SIGUSR1,&manejador,NULL) <0)
		printf("\nNo puedo manejar la señal %d",SIGUSR1);

	if( sigaction(SIGUSR2,&manejador,NULL) <0)
		printf("\nNo puedo manejar la señal %d",SIGUSR2);

	if( sigaction(SIGCHLD,&manejador,NULL) <0)
		printf("\nNo puedo manejar la señal %d",SIGCHLD);

	if( sigaction(SIGCONT,&manejador,NULL) <0)
		printf("\nNo puedo manejar la señal %d",SIGCONT);

	if( sigaction(SIGTTIN,&manejador,NULL) <0)
		printf("\nNo puedo manejar la señal %d",SIGTTIN);

	if( sigaction(SIGTTOU,&manejador,NULL) <0)
		printf("\nNo puedo manejar la señal %d",SIGTTOU);

	if (SIGKILL)
		printf("\nNo puedo manejar la señal %d",SIGKILL);

	if (SIGSTOP)
		printf("\nNo puedo manejar la señal %d",SIGSTOP);
	
	for(;;){
	}

}

