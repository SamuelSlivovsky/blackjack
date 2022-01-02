#include "krupier.h"

void premiesajBalicek(){
int premiesane[4][13];
int karty [4][13];
    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j < 14 ; ++j) {
            karty[i][j] = j;
        }
    }
    int c = 0;
int karta = 0;
int rovnakaKarta[13];
int nahodnaKarta = 0;
bool rovnaka = true;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            nahodnaKarta = rand()%13 + 1 ;
            for (int k = 0; k < 13; ++k) {
                if (rovnakaKarta[k] != nahodnaKarta){
                    rovnaka = false;
                }else {
                    rovnaka = true;
                    j--;
                    break;
                }
            }

            if (!rovnaka){

                karta = karty[i][nahodnaKarta--];
                premiesane[i][j] = karta;
                printf("%d %d\n",nahodnaKarta, c++);
                rovnakaKarta[j] = nahodnaKarta;
            }
        }
    }
    printf("rovnake karty:\n");
    for (int i = 0; i < 13; ++i) {
        printf("%d ", rovnakaKarta[i]);
    }

    printf("\nvsetky karty:\n");
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            printf("%d " ,premiesane[i][j]) ;
        }
        printf("\n");
    }
}