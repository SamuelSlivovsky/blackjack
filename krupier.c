#include "krupier.h"

void hra(DATA_K dataK, DATA_H dataH1, DATA_H dataH2) {
    premiesajBalicek(dataK.balicek);
    rozdajKarty(dataK.balicek, dataH1.karty, dataH2.karty);

    printf("\npo rozdani kariet:\n");
    printf("kartyA: %d %d %d %d %d\n", dataH1.karty[0], dataH1.karty[1], dataH1.karty[2], dataH1.karty[3], dataH1.karty[4]);
    printf("kartyB: %d %d %d %d %d\n", dataH2.karty[0], dataH2.karty[1], dataH2.karty[2], dataH2.karty[3], dataH2.karty[4]);

    for (int i = 0; i < 3; ++i) {
        int tahaA = rand() % 2;
        if (tahaA == 0)
            dajKartu(dataK.balicek, dataH1.karty, dataK.aktualnaKarta, dataH1.pocetKariet);
        int tahaB = rand() % 2;
        if (tahaB == 0)
            dajKartu(dataK.balicek, dataH2.karty, dataK.aktualnaKarta, dataH2.pocetKariet);
    }

    printf("\npo tahani kariet:\n");
    printf("kartyA: %d %d %d %d %d\n", dataH1.karty[0], dataH1.karty[1], dataH1.karty[2], dataH1.karty[3], dataH1.karty[4]);
    printf("kartyB: %d %d %d %d %d\n", dataH2.karty[0], dataH2.karty[1], dataH2.karty[2], dataH2.karty[3], dataH2.karty[4]);

    printf("\nKARTY HRAC A:\n");
    ukazKarty(&dataH1);

    printf("\nKARTY HRAC B:\n");
    ukazKarty(&dataH2);

    printf("\nvysledok:\n");
    porovnaj(dataH1, dataH2, dataK);
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
}

void dajKartu(const int *balicek, int *karty, int *aktualnaKarta, int *pocetKariet) {
    karty[*pocetKariet] = balicek[*aktualnaKarta];
    (*aktualnaKarta)++;
    (*pocetKariet)++;
}

void porovnaj(DATA_H dataH1, DATA_H dataH2, DATA_K dataK) {
    vypocitajSkore(&dataH1);
    vypocitajSkore(&dataH2);

    int skoreA = *(dataH1.skore);
    int skoreB = *(dataH2.skore);
    int rozdielA = 21 - skoreA;
    int rozdielB = 21 - skoreB;

    if (rozdielA >= 0 && rozdielA < rozdielB || rozdielB < 0 && rozdielA >= 0) {
        printf("Vyhral hrac A, skore bolo - %d : %d (A:B)\n", skoreA, skoreB);
        *(dataK.harabin) = 'A';
    } else if (rozdielB >= 0 && rozdielB < rozdielA || rozdielA < 0 && rozdielB >= 0) {
        printf("Vyhral hrac B, skore bolo - %d : %d (B:A)\n", skoreB, skoreA);
        *(dataK.harabin) = 'B';
    } else if (rozdielA == rozdielB && rozdielA >= 0) {
        printf("Remiza, skore bolo - %d : %d (A:B)\n", skoreA, skoreB);
        *(dataK.harabin) = 'R';
    } else {
        printf("Nikto nevyhral, skore bolo - %d : %d (A:B)\n", skoreA, skoreB);
        *(dataK.harabin) = 'N';
    }
}