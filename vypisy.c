#include "vypisy.h"

void intro() {
    printf(" --------------------------\n");
    printf("|                          |\n");
    printf("| VITAJTE V HRE BLACKJACK! |\n");
    printf("|                          |\n");
    printf(" --------------------------\n");
}

void menu() {
    printf("\n");
    printf("MENU:\n");
    printf("\t1 - hrat\n");
    printf("\t2 - historia hier\n");
    printf("\t3 - koniec\n");
    printf("\n");
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