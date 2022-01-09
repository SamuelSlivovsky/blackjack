#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#include "vypisy.h"

#ifndef POSSEMESTRALKA_HRAC_H
#define POSSEMESTRALKA_HRAC_H

typedef struct DataHrac {
    char *karty;
    int *pocetKariet;
    int *skore, *readFlag;
    char *buffer;
    int sockfd;
    pthread_mutex_t *mutex;
    pthread_cond_t *canRead;
} DATA_H;

void ukazKarty(char *karty);
int rozhodniHodnotuEsa(DATA_H *data);
void vypocitajSkore(DATA_H *data);
int hra(DATA_H *data);
int start(DATA_H *data);
void vypisKarty(DATA_H *data);

int writeMsg(DATA_H dataH, char *msg);
void readMsg(DATA_H dataH);
void* reading(void* args);

#endif //POSSEMESTRALKA_HRAC_H
