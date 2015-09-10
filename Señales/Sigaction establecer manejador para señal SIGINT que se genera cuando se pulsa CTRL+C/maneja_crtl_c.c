/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

// tarea10.c 

#include <stdio.h>
#include <signal.h>

static int s_recibida = 0;

static void handler (int signum){
	printf("\n Nueva acción del manejador \n");
	s_recibida++;
}

int main(){
	// Crea una variable sa de tipo sigaction
	struct sigaction sa;

	// Recibe la señal en la función establecida
	sa.sa_handler = handler;

	// Inicializa a vacío el conjunto de señales
	sigemptyset(&sa.sa_mask); 

	//Reiniciar las funciones que hayan sido interrumpidas por un manejador 
	sa.sa_flags = SA_RESTART; 

	// signum => SIGINT -> Interrupción procedente del teclado (<Ctrl+C>) (Página 2 - Sesión 5)
	// act* => &sa -> nueva acción para la señal signum se instala como act
	// oldact => NULL -> no se guarda la acción anterior
	if (sigaction(SIGINT, &sa, NULL) == -1){ // -1 -> error | 0 -> éxito
		printf("error en el manejador");
	}

	while(s_recibida < 3);
}

