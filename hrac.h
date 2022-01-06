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

//#include "krupier.h"

typedef struct DataHrac {

    char *karty;
    int *pocetKariet;
    int *skore;
    char *buffer;
    int sockfd;
    pthread_mutex_t *mutex;
    pthread_cond_t *canRead;
} DATA_H;

void ukazKarty(DATA_H *data);
int rozhodniHodnotuEsa(DATA_H *data);
void vypocitajSkore(DATA_H *data);
int hra(DATA_H *data);
int start(DATA_H *data);
int tah(DATA_H *data);
void vypisKarty(DATA_H *data);
void ukazKartyProtivnika(char *karty);
#endif //POSSEMESTRALKA_HRAC_H
