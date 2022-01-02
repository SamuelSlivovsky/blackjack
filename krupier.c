#include "krupier.h"

void premiesajBalicek() {
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
               if(premiesane[k] == nahodnaKarta && opakovanie <4){
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

void kartaObr(int num) {

    switch (num) {
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
            printf("*  %2d *\n", num);
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