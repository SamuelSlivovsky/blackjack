#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "hrac.h"
#include "krupier.h"
#include "vypisy.h"

//    TODO
//      - komunikacia medzi hracom a krupierom
//      - DONE - krupier - porovnanie kariet
//      - krupier - vypisanie vysledkov (historia hier) - vyriesit problem so zapisom
//      - hrac - rozhodnutie o hodnote esa
//      - hrac - rozhodnutie o tahani karty
//      - hrac - vylozenie kariet
//      - DONE - vypisanie vysledkov
//      - DONE - ci chcu hrat znova

typedef struct historia {
    char *historia;
    int pocetHier;
} HISTORY;

int game(HISTORY history) {
    int volba = 1;
    char chr = 'n';
    history.pocetHier = 0;
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
            char harabin = ' ';
            //hrac A
            int kartyA[5] = {0};
            int pocetKarietA = 2;
            int skoreA = 0;

            //hrac B
            int kartyB[5] = {0};
            int pocetKarietB = 2;
            int skoreB = 0;

            //naplnenie struktur
            DATA_K dataK = {balicek, &aktualnaKarta, &harabin};
            DATA_H dataH1 = {kartyA, &pocetKarietA, &skoreA};
            DATA_H dataH2 = {kartyB, &pocetKarietB, &skoreB};

            //spustenie hry
            hra(dataK, dataH1, dataH2);

            //naplnenie historie
            history.pocetHier++;
            char novePole[history.pocetHier];
            for (int i = 0; i < history.pocetHier; ++i) {
                novePole[i] = history.historia[i];

            }
            //novePole[history.pocetHier] = '\0';
            history.historia = novePole;
            history.historia[history.pocetHier] = *(dataK.harabin);

            printf("\n");
            printf("Chcete hrat znova?\n");
            printf(" (y - ano, n - nie)\n");
            printf("vasa volba: ");
            scanf(" %c", &chr);
            printf("\n");

        } else if (volba == 2) {
            // printf("...coskoro...\n");

            printf("%c\n", *history.historia);


        } else if (volba == 3) {
            return 0;
        } else {
            printf("Zadajte iba moznosti z MENU.\n");
        }
    }
}

int main() {
    srand(time(NULL));
    int pocetHier = 1;
    char historia[pocetHier];
    historia[0] = ' ';

    HISTORY history = {historia, pocetHier};
    game(history);
//    //krupier
//    int volba = 1;
//    char chr = 'n';
//    int balicek[52] = {0};
//    int aktualnaKarta = 4;
//    char harabin = ' ';
//    //hrac A
//    int kartyA[5] = {0};
//    int pocetKarietA = 2;
//    int skoreA = 0;
//
//    //hrac B
//    int kartyB[5] = {0};
//    int pocetKarietB = 2;
//    int skoreB = 0;
//
//    //naplnenie struktur
//    DATA_K dataK = {balicek, &aktualnaKarta, &harabin};
//    DATA_H dataH1 = {kartyA, &pocetKarietA, &skoreA};
//    DATA_H dataH2 = {kartyB, &pocetKarietB, &skoreB};
//
//    //spustenie hry
//    hra(dataK, dataH1, dataH2);
//
//    //naplnenie historie
//    history.pocetHier++;
//    char novePole[history.pocetHier];
//    for (int i = 0; i < history.pocetHier; ++i) {
//        novePole[i] = history.historia[i];
//    }
//    novePole[history.pocetHier] = '\0';
//    history.historia = novePole;
//    //history.historia[history.pocetHier-1] = *(dataK.harabin);
//    sprintf(history.historia,"%s",(dataK.harabin));
//
//    printf("%s\n", history.historia);
//    printf("\n");
//    printf("Chcete hrat znova?\n");
//    printf(" (y - ano, n - nie)\n");
//    printf("vasa volba: ");
//    scanf(" %c", &chr);
//    printf("\n");
}