#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "vypisy.h"

#ifndef POSSEMESTRALKA_KRUPIER_H
#define POSSEMESTRALKA_KRUPIER_H

typedef struct DataKrupier {
    int *balicek;
    int *aktualnaKarta;
    char *harabin;
    char *buffer;
    int sockfd, cl_1_sockfd, cl_2_sockfd;
} DATA_K;

typedef struct historia {
    char *historia;
    int pocetHier;
} HISTORY;

typedef struct DataHrac {
    int *karty;
    int *pocetKariet;
    int *skore;
} DATA_H;

void premiesajBalicek(int *balicek);
void rozdajKarty(const int *balicek, int *kartyA, int *kartyB);
void dajKartu(const int *balicek, int *karty, int *aktualnaKarta, int *pocetKariet);
void porovnaj(DATA_H dataH1, DATA_H dataH2, DATA_K dataK);
void hra(DATA_K dataK, DATA_H dataH1, DATA_H dataH2);
int game(DATA_K dataK);
#endif //POSSEMESTRALKA_KRUPIER_H
