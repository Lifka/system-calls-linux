/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

// tarea12.c

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int signal_recibida = 0;

// Manejador de señales
// Reestablece la señal recibida a 1
static void manejador (int sig){
          signal_recibida = 1;
}

int main (int argc, char *argv[]){
	// Creamos el conjunto de máscaras
	sigset_t conjunto_mascaras;

	// Aquí guardaremos la antigua máscara de señales
	sigset_t conj_mascaras_original;

	// Creamos un sigaction
	struct sigaction act;

	//Iniciamos a 0 todos los elementos de la estructura act 
	memset (&act, 0, sizeof(act));

	// Establecemos el manejador de señales
	act.sa_handler = manejador;

	// Captamos SIGTERM
	if (sigaction(SIGTERM, &act, 0)) {
		perror ("sigaction");
		return 1;
	}
    
	//Iniciamos un nuevo conjunto de mascaras
	sigemptyset (&conjunto_mascaras);

	//Añadimos SIGTERM al conjunto de mascaras
	sigaddset (&conjunto_mascaras, SIGTERM);
    
	//Bloqueamos SIGTERM
	// SIG_BLOCK => Bloquea las señales
	// Se aplica sobre conjunto_mascaras
	// Se guarda la original en conj_mascaras_original
	if (sigprocmask(SIG_BLOCK, &conjunto_mascaras, &conj_mascaras_original) < 0) {
  		error ("primer sigprocmask");
		return 1;
	}

	// Esperamos...
	sleep (10);

	//Restauramos la señales desbloqueamos SIGTERM
	// Establecemos las bloqueadas en función del segundo parámetro
	// conj_mascaras_original => Las que teníamos antes
	// NULL => No hacemos copia de las que acabábamos d eponer
	if (sigprocmask(SIG_SETMASK, &conj_mascaras_original, NULL) < 0) {
		perror ("segundo sigprocmask");
		return 1;
	}

	sleep (1);

	if (signal_recibida)
		printf ("\nSenal recibida\n");
		return 0;
}
