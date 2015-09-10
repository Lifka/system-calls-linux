/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

/*suspenda la ejecución del proceso actual hasta que se reciba
la señal SIGUSR1*/

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
	// Añadimos todas las señales salvo SIGUSR1
	sigaddset(&new_mask, SIGHUP);
	sigaddset(&new_mask, SIGINT);
	sigaddset(&new_mask, SIGQUIT);
	sigaddset(&new_mask, SIGILL);
	sigaddset(&new_mask, SIGABRT);
	sigaddset(&new_mask, SIGFPE);
	sigaddset(&new_mask, SIGSEGV);
	sigaddset(&new_mask, SIGPIPE);
	sigaddset(&new_mask, SIGALRM);
	sigaddset(&new_mask, SIGTERM);
	sigaddset(&new_mask, SIGUSR2);
	sigaddset(&new_mask, SIGCHLD);
	sigaddset(&new_mask, SIGCONT);
	sigaddset(&new_mask, SIGTSTP);
	sigaddset(&new_mask, SIGTTIN);
	sigaddset(&new_mask, SIGTTOU);

	// sigsuspend reemplaza temporalmente la máscara de señal para el proceso con la dada por el argumento mask y luego suspende el proceso hasta que se recibe una señal.
	/*esperar a cualquier señal excepto SIGUSR1 */
	sigsuspend(&new_mask);
}
