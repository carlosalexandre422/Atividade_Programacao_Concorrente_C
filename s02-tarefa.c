// Crie um programa com 5 threads usando laço e
// passe para cada uma o nome da respectiva thread.
// Cada thread dorme por 10 segundos de 1 em 1 segundo.
// Cada thread retorna ao término um código de ERRO caso o
// seu nome não inicie com letra maiúscula, e SUCESSO caso inicie.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define	N_THREADS	5

pthread_t minhas_threads[N_THREADS];		// Identificadores para 5 threads
int ERRO_TH = 111;		// Codigo que indica erro na thread
int SUCESSO_TH = 222; 	// Codigo que indica sucesso na thread

typedef struct param_t {
    int nst;		// Numero de segundos no total
    char *nome;		// Nome da thread
} Param_t;


/** Espera passar *nst segundos, de segundo em segundo */
void codigo_tarefa(Param_t *pparam){
	for( int ns=0; ns < pparam->nst; ++ns) {
		sleep(1);
		printf("Tarefa: passaram %d segundos do total de %d.\n", ns+1, pparam->nst);
    }
    if(pparam->nome[0] == 'T'){
        pthread_exit(&SUCESSO_TH);
    } else {
        pthread_exit(&ERRO_TH);
    }
}


/** Função principal, cria as threads */
int main(void){
	Param_t param_dados[N_THREADS];
    int *retornos[N_THREADS];

    for(int i=0; i<N_THREADS; ++i){
        retornos[i] = malloc(sizeof(int));
    }

	printf("Inicio\n");

	// Prepara os parametros de todas as threads
	for( int i=0; i<N_THREADS; ++i){
        param_dados[i].nome = malloc(10*sizeof(char));
        char x[10];
        itoa(i+1, x, 10);
        param_dados[i].nst = 10;
        if(i == 4){
        param_dados[i].nome = "tarefa 5";
        break;       
        }   
        sprintf(param_dados[i].nome, "Tarefa %s", x);
    }
		
	// Cria todas as threads
	for( int i=0; i<N_THREADS; ++i) 
		pthread_create(&minhas_threads[i], NULL, (void *) codigo_tarefa, (void *)&param_dados[i]);

	// Espera por todas as threads
	for( int i=0; i<N_THREADS; ++i)
		pthread_join(minhas_threads[i], (void *)&retornos[i]);

	printf("Fim\n");

    for( int i=0; i<N_THREADS; ++i)
		printf("Tarefa %d retornou %d\n", i+1, *retornos[i]);
	return(0);
}

