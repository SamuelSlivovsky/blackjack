#include "krupier.h"

void hra(DATA_K dataK) {
//    premiesajBalicek(dataK.balicek);
//    rozdajKarty(dataK.balicek, dataH1.karty, dataH2.karty);
    rozdajKarty(dataK.balicek);
//    dajKartu(dataK.balicek, null, dataK.aktualnaKarta, null)
}

void premiesajBalicek(int (*balicek)[52]) {
    int premiesane[52] = {0};
    int nahodnaKarta = 0;
    bool rovnaka = true;

    for (int i = 0; i < 52; ++i) {

            nahodnaKarta = rand() % 13 + 1;
            int opakovanie = 0;
            for (int k = 0; k < 52; ++k) {
                if (premiesane[k] != nahodnaKarta){
                    rovnaka = false;
                }
               if(premiesane[k]== nahodnaKarta && opakovanie < 4){
                   opakovanie++;
                   rovnaka = false;
               }
               if(opakovanie > 3){
                   i--;
                   rovnaka = true;
                   break;
               }
            }
            if (!rovnaka) {
                premiesane[i] = nahodnaKarta;
            }
    }
    for (int i = 0; i < 52; ++i) {
        printf("%d ", premiesane[i]);
    }
}

void rozdajKarty(int (*balicek)[52]) {
    int premiesane[52] = {0};
    int nahodnaKarta = 0;
    bool rovnaka = true;

    for (int i = 0; i < 52; ++i) {

        nahodnaKarta = rand() % 13 + 1;
        int opakovanie = 0;
        for (int k = 0; k < 52; ++k) {
            if (premiesane[k] != nahodnaKarta){
                rovnaka = false;
            }
            if(premiesane[k]== nahodnaKarta && opakovanie < 4){
                opakovanie++;
                rovnaka = false;
            }
            if(opakovanie > 3){
                i--;
                rovnaka = true;
                break;
            }
        }
        if (!rovnaka) {
            premiesane[i] = nahodnaKarta;
        }
    }
    for (int i = 0; i < 52; ++i) {
        printf("%d ", premiesane[i]);
    }
    printf("\n");

    int kartyA[5] = {0};
    int kartyB[5] = {0};

    kartyA[0] = premiesane[0];
    kartyB[0] = premiesane[1];
    kartyA[1] = premiesane[2];
    kartyB[1] = premiesane[3];

    printf("kartyA: %d %d %d %d %d\n", kartyA[0], kartyA[1], kartyA[2], kartyA[3], kartyA[4]);
    printf("kartyB: %d %d %d %d %d\n", kartyB[0], kartyB[1], kartyB[2], kartyB[3], kartyB[4]);
}

void dajKartu(int (*balicek)[52], int (*karty)[5], int aktualnaKarta, int pocetKariet) {
    *(karty[pocetKariet]) = *(balicek[aktualnaKarta]);
    aktualnaKarta++;
    pocetKariet++;
}

void porovnaj(int *skoreA, int *skoreB) {
    if (*skoreA > *skoreB) {
        printf("Vyhral hrac A, skore bolo %d : %d\n", *skoreA, *skoreB);
    } else {
        printf("Vyhral hrac B, skore bolo %d : %d\n", *skoreB, *skoreA);
    }
}

void vykresliKartu(int cisloKarty) {

    switch (cisloKarty) {
        case 1: {
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*   A *\n");
            printf("*     *\n");
            printf("*******\n");
            break;
        }
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10: {
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*  %2d *\n", cisloKarty);
            printf("*     *\n");
            printf("*******\n");
            break;
        }
        case 11: {
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*   J *\n");
            printf("*     *\n");
            printf("*******\n");
            break;
        }
        case 12: {
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*   Q *\n");
            printf("*     *\n");
            printf("*******\n");
            break;
        }
        case 13: {
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*   K *\n");
            printf("*     *\n");
            printf("*******\n");
            break;
        }
    }
}