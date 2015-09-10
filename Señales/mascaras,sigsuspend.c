/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

// tarea11.c

#include <stdio.h>
#include <signal.h>

/*
Se suspende la ejecución del proceso actual hasta que
reciba una señal distinta de SIGUSR1
*/

int main(){
	// Creamos una nueva máscara de señales
	sigset_t new_mask;

	/* inicializar la nueva mascara de señales */
	sigemptyset(&new_mask);

	// sigaddset=> Añade una señal a un conjunto de señales set previamente inicializado
	// Añadimos SIGUSR1 al conjunto de la máscara
	sigaddset(&new_mask, SIGUSR1);

	// sigsuspend reemplaza temporalmente la máscara de señal para el proceso con la dada por el argumento mask y luego suspende el proceso hasta que se recibe una señal.
	/*esperar a cualquier señal excepto SIGUSR1 */
	sigsuspend(&new_mask);
}
