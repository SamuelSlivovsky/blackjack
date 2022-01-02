#include "hrac.h"

int ukazKarty(){
    return 0;
}

void pridajKartu(int paKarta){

}

int rozhodniHodnotuEsa(DATA_H *data) {
    vypocitajSkore(data);
    if (*(data->skore) > 12)
        return 1;
    return 10;
}

void vypocitajSkore(DATA_H *data) {
    int sum = 0;
    for (int i = 0; i < *(data->pocetKariet); ++i) {
        int karta = *(data->karty[i]);
        if (karta > 10)
            karta = 10;
        sum += karta;
    }
    *(data->skore) = sum;
}