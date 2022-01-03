#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "hrac.h"
#include "krupier.h"
#include "vypisy.h"

//    TODO
//      - komunikacia medzi hracom a krupierom
//      - DONE - krupier - porovnanie kariet
//      - krupier - vypisanie vysledkov (historia hier)
//      - hrac - rozhodnutie o hodnote esa
//      - hrac - rozhodnutie o tahani karty
//      - hrac - vylozenie kariet
//      - DONE - vypisanie vysledkov
//      - DONE - ci chcu hrat znova

int main() {

    srand(time(NULL));
    int volba = 1;
    char chr = 'n';
    intro();
    while (true) {
        menu();
        if (chr != 'y') {
            printf("vasa volba: ");
            scanf("%d", &volba);
        }

        if (volba == 1) {
            //krupier
            int balicek[52] = {0};
            int aktualnaKarta = 4;

            //hrac A
            int kartyA[5] = {0};
            int pocetKarietA = 2;
            int skoreA = 0;

            //hrac B
            int kartyB[5] = {0};
            int pocetKarietB = 2;
            int skoreB = 0;

            //naplnenie struktur
            DATA_K dataK = {balicek, &aktualnaKarta};
            DATA_H dataH1 = {kartyA, &pocetKarietA, &skoreA};
            DATA_H dataH2 = {kartyB, &pocetKarietB, &skoreB};

            //spustenie hry
            hra(dataK, dataH1, dataH2);

            printf("\n");
            printf("Chcete hrat znova?\n");
            printf(" (y - ano, n - nie)\n");
            printf("vasa volba: ");
            scanf(" %c", &chr);
            printf("\n");

        } else if (volba == 2) {
            printf("...coskoro...\n");
        } else if (volba == 3){
            return 0;
        } else {
            printf("Zadajte iba moznosti z MENU.\n");
        }
    }
}