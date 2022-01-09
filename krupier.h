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
    char *balicek;
    int *aktualnaKarta, *readFlag;
    char *harabin;
    char *buffer;
    int sockfd, cl_1_sockfd, cl_2_sockfd;
    int *readSockfd;
    pthread_mutex_t *mutex;
    pthread_cond_t *canRead;
} DATA_K;

typedef struct historia {
    char *historia;
    int *pocetHier;
} HISTORY;

typedef struct DataHrac {
    char *karty;
    int *pocetKariet;
    int *skore;
    int *lock;
    int clsockfd;
} DATA_H;

void inicializacia(DATA_K dataK, DATA_H dataH1, DATA_H dataH2);
int hra(DATA_K dataK, DATA_H dataH1, DATA_H dataH2, HISTORY history);
void premiesajBalicek(char *balicek);
void rozdajKarty(DATA_K dataK, DATA_H dataH1, DATA_H dataH2);
void dajKartu(DATA_K datak, DATA_H dataH);
void tah(DATA_H dataH, DATA_K dataK);
int porovnaj(DATA_H dataH1, DATA_H dataH2, DATA_K dataK);
void vypocitajSkore(DATA_H *data);
void ukazKarty(DATA_H data);
void vylozitKarty(DATA_H dataH);

int writeMsg(DATA_K dataK, char *msg);
void readMsg(DATA_K dataK);
void *reading(void *args);

#endif //POSSEMESTRALKA_KRUPIER_H