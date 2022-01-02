#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef POSSEMESTRALKA_KRUPIER_H
#define POSSEMESTRALKA_KRUPIER_H

#include "hrac.h"

typedef struct DataKrupier {
    int (*balicek)[52];
    int *aktualnaKarta;
} DATA_K;

void premiesajBalicek(int (*balicek)[52]);
//void rozdajKarty(int (*balicek)[52], int (*kartyA)[5], int (*kartyB)[5]);
void rozdajKarty(int (*balicek)[52]);
void dajKartu(int (*balicek)[52], int (*karty)[5], int aktualnaKarta, int pocetKariet);
void vykresliKartu(int cKarty);
void porovnaj(int *skoreA, int *skoreB);
void hra(DATA_K dataK);


#endif //POSSEMESTRALKA_KRUPIER_H
