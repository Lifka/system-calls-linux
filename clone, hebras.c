/*

********************************************

	Javier Izquierdo Vera
	javierizquierdovera@gmail.com
	UGR

********************************************

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <linux/sched.h>
#include <malloc.h>
#define _GNU_SOURCE

/* See feature_test_macros(7) */
int variable=3;

// Hebra
int thread(void *p) {
	printf("\nsoy el hijo\n");
	sleep(5); // espera 5

	variable++;

	int tid = syscall(SYS_gettid); // id hebra

	printf("\nPID y TID del hijo:%d %d\n",getpid(),tid);
	printf("\nEn el hijo la variable vale:%d\n",variable);
}

int main() {
	void **stack; // Pila del hijo
	int i, tid;

	stack = (void **)malloc(15000); // reservamos espacio

	if (!stack) // Si error
		return -1;

	// LANZAMOS LA HEBRA
	// int clone(int (*func) (void *), void *child_stack, int flags, void *func_arg,...

				//func  //Pila               flags                                                     argumentos funćón
	i = clone(thread, (char*) stack + 15000, CLONE_VM|CLONE_FILES|CLONE_FS|CLONE_THREAD|CLONE_SIGHAND, NULL);
	/* el hijo comparte con su padre la memoria virtual, los archivos abiertos, el directorio raíz
		el directorio de trabajo y la máscara de creación de archivos, pone al hijo en el mismo grupo
		del padre (PID es igual), y comparten los manejadores de señales. FLAS EN P9 APUNTES SESION 3
	*/

	sleep(5); // Espera 5
	if (i == -1) // Si error al crear la hebra
		perror("clone");

	tid = syscall(SYS_gettid); //id hebra padre
	printf("\nPID y TID del padre:%d %d\n ",getpid(),tid);
	printf("\nEn el padre la variable vale:%d\n",variable); //será la misma como consecuencia de CLONE_VM
	return 0;
}
