#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "hrac.h"
#include "krupier.h"

int main() {

    srand(time(NULL));

    int balicek[52] = {0};
    int kartyA[5] = {0};
    int kartyB[5] = {0};
    int aktualnaKarta = 4;
    int pocetKarietA = 2;
    int pocetKarietB = 2;
    int skoreA = 0;
    int skoreB = 0;

    DATA_K dataK = {balicek, &aktualnaKarta};
    DATA_H dataH1 = {kartyA, &pocetKarietA, &skoreA};
    DATA_H dataH2 = {kartyB, &pocetKarietB, &skoreB};

    hra(dataK, dataH1, dataH2);

//    TODO
//      - komunikacia medzi hracom a krupierom
//      - krupier - porovnanie kariet
//      - krupier - vypisanie vysledkov (historia hier)
//      - hrac - rozhodnutie o hodnote esa
//      - hrac - rozhodnutie o tahani karty
//      - hrac - vylozenie kariet
//      - vypisanie vysledkov
//      - ci chcu hrat znova

    return 0;
}
