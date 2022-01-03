#include "krupier.h"

void hra(DATA_K dataK, DATA_H dataH1, DATA_H dataH2) {
    premiesajBalicek(dataK.balicek);
    rozdajKarty(dataK.balicek, dataH1.karty, dataH2.karty);

    printf("\npo rozdani kariet:\n");
    printf("kartyA: %d %d %d %d %d\n", dataH1.karty[0], dataH1.karty[1], dataH1.karty[2], dataH1.karty[3], dataH1.karty[4]);
    printf("kartyB: %d %d %d %d %d\n", dataH2.karty[0], dataH2.karty[1], dataH2.karty[2], dataH2.karty[3], dataH2.karty[4]);

    for (int i = 0; i < 3; ++i) {
        dajKartu(dataK.balicek, dataH1.karty, dataK.aktualnaKarta, dataH1.pocetKariet);
        dajKartu(dataK.balicek, dataH2.karty, dataK.aktualnaKarta, dataH2.pocetKariet);
    }

    printf("\npo tahani kariet:\n");
    printf("kartyA: %d %d %d %d %d\n", dataH1.karty[0], dataH1.karty[1], dataH1.karty[2], dataH1.karty[3], dataH1.karty[4]);
    printf("kartyB: %d %d %d %d %d\n", dataH2.karty[0], dataH2.karty[1], dataH2.karty[2], dataH2.karty[3], dataH2.karty[4]);

    printf("\nvysledok:\n");
    porovnaj(dataH1, dataH2);
}

void premiesajBalicek(int *balicek) {
    int nahodnaKarta;
    bool rovnaka = true;

    for (int i = 0; i < 52; ++i) {

            nahodnaKarta = rand() % 13 + 1;
            int opakovanie = 0;
            for (int k = 0; k < 52; ++k) {
                if (balicek[k] != nahodnaKarta){
                    rovnaka = false;
                }
               if(balicek[k]== nahodnaKarta && opakovanie < 4){
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
                balicek[i] = nahodnaKarta;
            }
    }
    for (int i = 0; i < 52; ++i) {
        printf("%d ", balicek[i]);
    }
    printf("\n");
}

void rozdajKarty(const int *balicek, int *kartyA, int kartyB[5]) {
    kartyA[0] = balicek[0];
    kartyB[0] = balicek[1];
    kartyA[1] = balicek[2];
    kartyB[1] = balicek[3];

    printf("kartyA:\n");
    for (int i = 0; i < 2; ++i) {
        vykresliKartu(kartyA[i]);
    }
    printf("kartyB:\n");
    for (int i = 0; i < 2; ++i) {
        vykresliKartu(kartyB[i]);
    }
}

void dajKartu(const int *balicek, int *karty, int *aktualnaKarta, int *pocetKariet) {
    karty[*pocetKariet] = balicek[*aktualnaKarta];
    (*aktualnaKarta)++;
    (*pocetKariet)++;
}

void porovnaj(DATA_H dataH1, DATA_H dataH2) {
    vypocitajSkore(&dataH1);
    vypocitajSkore(&dataH2);

    int skoreA = *(dataH1.skore);
    int skoreB = *(dataH2.skore);

    if (skoreA > skoreB) {
        printf("Vyhral hrac A, skore bolo %d : %d\n", skoreA, skoreB);
    } else if (skoreA < skoreB) {
        printf("Vyhral hrac B, skore bolo %d : %d\n", skoreB, skoreA);
    } else {
        printf("Remiza, nikto nevyhral, skore bolo (A:B) %d : %d\n", skoreA, skoreB);
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
        default:
            break;
    }
}