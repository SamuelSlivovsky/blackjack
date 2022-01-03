#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "vypisy.h"

#ifndef POSSEMESTRALKA_HRAC_H
#define POSSEMESTRALKA_HRAC_H

//#include "krupier.h"

typedef struct DataHrac {
    int *karty;
    int *pocetKariet;
    int *skore;
} DATA_H;

void ukazKarty(DATA_H *data);
void pridajKartu(int paKarta);
int rozhodniHodnotuEsa(DATA_H *data);
void vypocitajSkore(DATA_H *data);

#endif //POSSEMESTRALKA_HRAC_H
