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
#include <errno.h>
#include <stdlib.h>

static void handler (int estado){
	pid_t pid = wait(&estado); 

	/*char fifo_pid[longpalabra];
	sprintf(fifo_pid, "fifo.%d",pid);
	unlink(fifo_pid);*/

}

int crea_n_hijos(int cantidad){
	pid_t pid;	
	int i = 0;
	while (i < cantidad && (pid = fork())){
		printf("Creado nuevo hijo -> %d por %d\n",i,getpid());
		i++;
	}
	return pid;
}

int main(int argc, char** argv){
	if(argc != 2){
		perror("Syntax error: program n_process");
		exit(1);
	}

	pid_t pid = crea_n_hijos(strtol(argv[1], NULL, 10));

	if (pid > 0){
		printf("Soy el padre! %d\n", getpid());
	} else {
		printf("Soy hijo! %d\n", getpid());

	}


	// Evitar que queden procesos zombis
	struct sigaction sa;

	// Recibe la señal en la función establecida
	// Establecemos nuestro propio controlador de señal
	sa.sa_handler = handler;

	// Inicializa a vacío el conjunto de señales
	sigemptyset(&sa.sa_mask); 

	//Reiniciar las funciones que hayan sido interrumpidas por un manejador 
	sa.sa_flags = SA_RESTART; 

	/*
	No deben quedar procesos zombis en el sistema. Podemos evitarlo manejando en el servidor
	las señales SIGCHLD que envían los procesos proxy (ya que son hijos del servidor) cuando
 	terminan. Por omisión, la acción asignada a esta señal es ignorarla, pero mediante la
   	llamada al sistema signal podemos especificar un manejador que ejecute la llamada wait
 	impidiendo que los procesos proxy queden en estado zombi indefinidamente
	*/
	// signum => SIGCHLD -> Manejar la finalización de los hijos
	// act* => &sa -> nueva acción para la señal signum se instala como act
	// oldact => NULL -> no se guarda la acción anterior
	if (sigaction(SIGCHLD, &sa, NULL) == -1){ // -1 -> error | 0 -> éxito
		printf("error en el manejador");
	}

}