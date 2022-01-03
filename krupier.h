#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "vypisy.h"

#ifndef POSSEMESTRALKA_KRUPIER_H
#define POSSEMESTRALKA_KRUPIER_H

#include "hrac.h"

typedef struct DataKrupier {
    int *balicek;
    int *aktualnaKarta;
} DATA_K;

void premiesajBalicek(int *balicek);
void rozdajKarty(const int *balicek, int *kartyA, int *kartyB);
void dajKartu(const int *balicek, int *karty, int *aktualnaKarta, int *pocetKariet);
void porovnaj(DATA_H dataH1, DATA_H dataH2);
void hra(DATA_K dataK, DATA_H dataH1, DATA_H dataH2);

#endif //POSSEMESTRALKA_KRUPIER_H
