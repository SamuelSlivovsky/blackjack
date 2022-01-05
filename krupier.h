#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "vypisy.h"

#ifndef POSSEMESTRALKA_KRUPIER_H
#define POSSEMESTRALKA_KRUPIER_H

typedef struct DataKrupier {
    int *balicek;
    int *aktualnaKarta;
    char *harabin;
    char *buffer;
    int sockfd, cl_1_sockfd, cl_2_sockfd;
    pthread_mutex_t *mutex;
    pthread_cond_t *canRead;
} DATA_K;

typedef struct historia {
    char *historia;
    int pocetHier;
} HISTORY;

typedef struct DataHrac {
    int *karty;
    int *pocetKariet;
    int *skore;
    int *lock;
    int clsockfd;
} DATA_H;

void premiesajBalicek(int *balicek);
void rozdajKarty(DATA_K dataK, DATA_H dataH1, DATA_H dataH2);
void dajKartu(DATA_K datak, DATA_H dataH);
void vylozitKarty(DATA_H dataH);
void tah(DATA_H dataH, DATA_K dataK);
void porovnaj(DATA_H dataH1, DATA_H dataH2, DATA_K dataK);
void hra(DATA_K dataK, DATA_H dataH1, DATA_H dataH2);
int writeCharMsg(DATA_K dataK, char *msg, int client);
int writeIntMsg(DATA_K dataK, int msg, int client);
int readMsg(DATA_K dataK, int client);

#endif //POSSEMESTRALKA_KRUPIER_H
