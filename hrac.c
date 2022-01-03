#include "hrac.h"

void ukazKarty(DATA_H *data){
    for (int i = 0; i < 5; ++i) {
        vykresliKartu(data->karty[i]);
    }
}


int rozhodniHodnotuEsa(DATA_H *data) {
char chr = ' ';
while(chr != 'y' || chr != 'n') {
    printf("\n");
    printf("Dostali ste Eso, aku chcete aby malo hodnotu?\n");
    printf(" (y - 1, n - 10)\n");
    printf("vasa volba: ");
    scanf(" %c", &chr);
    printf("\n");
}
    if (chr =='y'){
        data->karty[*(data->pocetKariet)] = 1;
    }else if (chr == 'n'){
        data->karty[*(data->pocetKariet)] = 10;
    }

}

void vypocitajSkore(DATA_H *data) {
    int sum = 0;
    for (int i = 0; i < *(data->pocetKariet); ++i) {
        int karta = data->karty[i];
        if (karta > 10)
            karta = 10;
        sum += karta;
    }
    *(data->skore) = sum;
}