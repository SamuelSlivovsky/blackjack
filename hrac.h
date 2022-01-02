#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef POSSEMESTRALKA_HRAC_H
#define POSSEMESTRALKA_HRAC_H

#include "krupier.h"

typedef struct DataHrac {
    int (*karty)[5];
    int *pocetKariet;
} DATA_H;

int ukazKarty();
void pridajKartu(int paKarta);
void rozhodniHodnotuEsa();
void vypocitajSkore();

#endif //POSSEMESTRALKA_HRAC_H
