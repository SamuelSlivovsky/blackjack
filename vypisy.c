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
    printf("\t2 - koniec\n");
    printf("\n");
}

void restart() {
    printf("\n");
    printf("HRAT ZNOVA?\n");
    printf("\ty - ano\n");
    printf("\tn - nie\n");
    printf("\n");
}

void hracTah() {
    printf("\n");
    printf("Si na tahu, mozes:\n");
    printf("\t1 - si potiahnut kartu\n");
    printf("\t2 - neurobit nic\n");
    printf("\n");
}

void cakaj() {
    printf("\n");
    printf("Prosim cakajte...\n");
    printf("\n");
}

void vykresliKartu(char karta) {

    switch (karta) {
        case '1':
        case 'A': {
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*   A *\n");
            printf("*     *\n");
            printf("*******\n");
            break;
        }
        case '2':
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*  %2d *\n", 2);
            printf("*     *\n");
            printf("*******\n");
            break;
        case '3':
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*  %2d *\n", 3);
            printf("*     *\n");
            printf("*******\n");
            break;
        case '4':
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*  %2d *\n", 4);
            printf("*     *\n");
            printf("*******\n");
            break;
        case '5':
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*  %2d *\n", 5);
            printf("*     *\n");
            printf("*******\n");
            break;
        case '6':
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*  %2d *\n", 6);
            printf("*     *\n");
            printf("*******\n");
            break;
        case '7':
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*  %2d *\n", 7);
            printf("*     *\n");
            printf("*******\n");
            break;
        case '8':
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*  %2d *\n", 8);
            printf("*     *\n");
            printf("*******\n");
            break;
        case '9':
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*  %2d *\n", 9);
            printf("*     *\n");
            printf("*******\n");
            break;
        case '0': {
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*  %2d *\n", 10);
            printf("*     *\n");
            printf("*******\n");
            break;
        }
        case 'J': {
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*   J *\n");
            printf("*     *\n");
            printf("*******\n");
            break;
        }
        case 'Q': {
            printf("*******\n");
            printf("*     *\n");
            printf("*     *\n");
            printf("*   Q *\n");
            printf("*     *\n");
            printf("*******\n");
            break;
        }
        case 'K': {
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