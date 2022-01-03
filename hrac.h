#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef POSSEMESTRALKA_HRAC_H
#define POSSEMESTRALKA_HRAC_H

//#include "krupier.h"

typedef struct DataHrac {
    int *karty;
    int *pocetKariet;
    int *skore;
} DATA_H;

int ukazKarty();
void pridajKartu(int paKarta);
int rozhodniHodnotuEsa(DATA_H *data);
void vypocitajSkore(DATA_H *data);

#endif //POSSEMESTRALKA_HRAC_H
