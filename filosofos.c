#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define NUM_FILOSOFOS 5

int LOOPS = 100;
int TEMPO_COMENDO = 2;
int TEMPO_PENSANDO = 1;
int TEMPO_MULT = 1;

volatile int counter = 0;

char estado_filosofo[NUM_FILOSOFOS][4];
pthread_mutex_t mutex_garfo[NUM_FILOSOFOS];

void print_table(int id) {

    printf("╔════════════════════════════╗\n"
           "║ Estado Atual do Thread %d:  ║\n"
           "╚════════════════════════════╝\n"
           "\n"
           "        ┌───┐         ┌───┐         ┌───┐         ┌───┐         ┌───┐        \n"
           "        │%s│         │%s│         │%s│         │%s│         │%s│         \n"
           "        └───┘         └───┘         └───┘         └───┘         └───┘        \n",
           id, estado_filosofo[0], estado_filosofo[1], estado_filosofo[2], estado_filosofo[3], estado_filosofo[4]);
}

void *filosofo(void *arg) {
    int id = *(int *)arg;
    int garfo_esquerda = id;
    int garfo_direita = (id + 1) % NUM_FILOSOFOS;

    while (1) {
        counter++;
        if (counter > LOOPS) break;         // Terminou as refeicoes
        strcpy(estado_filosofo[id], "?O?"); // Pensando
        print_table(id);
        usleep(TEMPO_PENSANDO * TEMPO_MULT);// Tempo para pensar

        strcpy(estado_filosofo[id], " O "); // Sem garfo
        print_table(id);

        if (id % 2 == 0) {
            pthread_mutex_lock(&mutex_garfo[garfo_esquerda]);
            strcpy(estado_filosofo[id], "|O "); // Pegou garfo esquerdo
            print_table(id);
            pthread_mutex_lock(&mutex_garfo[garfo_direita]);
            strcpy(estado_filosofo[id], "|O|"); // Pegou garfo direito
            print_table(id);
        } else {
            pthread_mutex_lock(&mutex_garfo[garfo_direita]);
            strcpy(estado_filosofo[id], " O|"); // Pegou garfo direito
            print_table(id);
            pthread_mutex_lock(&mutex_garfo[garfo_esquerda]);
            strcpy(estado_filosofo[id], "|O|"); // Pegou garfo esquerdo
            print_table(id);
        }
        usleep(TEMPO_COMENDO * TEMPO_MULT); // Tempo para comer

        pthread_mutex_unlock(&mutex_garfo[garfo_direita]);
        strcpy(estado_filosofo[id], "|O "); // Soltou garfo esquerdo
        print_table(id);
        pthread_mutex_unlock(&mutex_garfo[garfo_esquerda]);
        strcpy(estado_filosofo[id], " O "); // Soltou garfo direito
        print_table(id);
    }

    pthread_exit(NULL);
}

int main() {
    printf("╔════════════════════════════════════╗\n"
           "║       O Jantar dos Filósofos       ║\n"
           "╚════════════════════════════════════╝\n");
    
    pthread_t threads[NUM_FILOSOFOS];
    int tid[NUM_FILOSOFOS];

    printf("Insira os valores das seguintes variáveis:\n");
    printf("Número de Refeições:\n");
    scanf("%d", &LOOPS);
    printf("Tempo Comendo (em usec):\n");
    scanf("%d", &TEMPO_COMENDO);
    printf("Tempo Pensando (em usec):\n");
    scanf("%d", &TEMPO_PENSANDO);

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        /* Cada garfo sera um mutex. O numero de garfos equivale 
         * ao de filosofos */ 
        pthread_mutex_init(&mutex_garfo[i], NULL);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        strcpy(estado_filosofo[i], "?O?"); // Inicialmente pensando
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        // Iniciando as threads referentes a cada filosofo
        tid[i] = i;
        pthread_create(&threads[i], NULL, filosofo, &tid[i]);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
