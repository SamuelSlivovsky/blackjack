#include "krupier.h"

int game(DATA_K dataK) {
    //spusti intro
    //intro();
    const char* msg = "Vitajte v hre blackjack\n hrat 1\nhistoria 2\nkoniec 3\n";

    int n1 = write(dataK.cl_1_sockfd, msg, strlen(msg)+1);
    if (n1 < 0) {
        perror("Error writing to socket");
        return 5;
    }
   /* bzero(dataK.buffer, 256);
    int n2 = write(dataK.cl_2_sockfd, dataK.buffer, strlen(dataK.buffer) + 1);
    if (n2 < 0) {
        perror("Error writing to socket");
        return 5;
    }*/

    //caka na odpovede od hracov
    bzero(dataK.buffer, 256);
    n1 = read(dataK.cl_1_sockfd, dataK.buffer, 255);
    if (n1 < 0) {
        perror("Error reading from socket");
        return 4;
    }
    char volba1 = dataK.buffer[0];
    //bzero(dataK.buffer, 256);
    //n2 = read(dataK.cl_2_sockfd, dataK.buffer, 255);

    /*if (n2 < 0) {
        perror("Error reading from socket");
        return 4;
    }
    char volba2 = dataK.buffer[0];
    if (volba1 == '3'){
        printf("koniec");
        return 0;
    }*/
    char chr = 'n';
    int volba = 1;
    while (true) {
       // menu();
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

            DATA_H dataH1 = {kartyA, &pocetKarietA, &skoreA};
            DATA_H dataH2 = {kartyB, &pocetKarietB, &skoreB};

            //spustenie hry
            hra(dataK, dataH1, dataH2);

            //naplnenie historie
            /* history.pocetHier++;
             char novePole[history.pocetHier];
             for (int i = 0; i < history.pocetHier; ++i) {
                 novePole[i] = history.historia[i];

             }
             //novePole[history.pocetHier] = '\0';
             history.historia = novePole;
             history.historia[history.pocetHier] = *(dataK.harabin);
 */
            printf("\n");
            printf("Chcete hrat znova?\n");
            printf(" (y - ano, n - nie)\n");
            printf("vasa volba: ");
            scanf(" %c", &chr);
            printf("\n");

        } else if (volba == 2) {
            printf("...coskoro...\n");

            // printf("%c\n", *history.historia);


        } else if (volba == 3) {
            return 0;
        } else {
            printf("Zadajte iba moznosti z MENU.\n");
        }
    }
}

void hra(DATA_K dataK, DATA_H dataH1, DATA_H dataH2) {
    premiesajBalicek(dataK.balicek);
    rozdajKarty(dataK.balicek, dataH1.karty, dataH2.karty);

    printf("\npo rozdani kariet:\n");
    printf("kartyA: %d %d %d %d %d\n", dataH1.karty[0], dataH1.karty[1], dataH1.karty[2], dataH1.karty[3],
           dataH1.karty[4]);
    printf("kartyB: %d %d %d %d %d\n", dataH2.karty[0], dataH2.karty[1], dataH2.karty[2], dataH2.karty[3],
           dataH2.karty[4]);

    for (int i = 0; i < 3; ++i) {
        int tahaA = rand() % 2;
        if (tahaA == 0)
            dajKartu(dataK.balicek, dataH1.karty, dataK.aktualnaKarta, dataH1.pocetKariet);
        int tahaB = rand() % 2;
        if (tahaB == 0)
            dajKartu(dataK.balicek, dataH2.karty, dataK.aktualnaKarta, dataH2.pocetKariet);
    }

    printf("\npo tahani kariet:\n");
    printf("kartyA: %d %d %d %d %d\n", dataH1.karty[0], dataH1.karty[1], dataH1.karty[2], dataH1.karty[3],
           dataH1.karty[4]);
    printf("kartyB: %d %d %d %d %d\n", dataH2.karty[0], dataH2.karty[1], dataH2.karty[2], dataH2.karty[3],
           dataH2.karty[4]);

    printf("\nKARTY HRAC A:\n");
    //ukazKarty(&dataH1);

    printf("\nKARTY HRAC B:\n");
    //ukazKarty(&dataH2);

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
            if (balicek[k] != nahodnaKarta) {
                rovnaka = false;
            }
            if (balicek[k] == nahodnaKarta && opakovanie < 4) {
                opakovanie++;
                rovnaka = false;
            }
            if (opakovanie > 3) {
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
    // vypocitajSkore(&dataH1);
    //vypocitajSkore(&dataH2);

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

int main(int argc, char *argv[]) {

//--------------------------- uvodne nastavovanie ------------------------------------

    int sockfd, cl_1_sockfd, cl_2_sockfd; // deskriptory socketov pre server a klientov
    socklen_t cli_1_len, cli_2_len;
    struct sockaddr_in serv_addr, cli_1_addr, cli_2_addr; // adresy pre server a klientov
    int n;
    char buffer[256]; // buffer na komunikaciu

    if (argc < 2) {
        fprintf(stderr, "usage %s port\n", argv[0]);
        return 1;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr)); // vycistenie struktury
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    } else {
        printf("[INFO] - Succesfully created socket\n");
    }

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error binding socket address");
        return 2;
    } else {
        printf("[INFO] - Succesfully binded socket address\n");
    }

    listen(sockfd, 5);
    cli_1_len = sizeof(cli_1_addr);

    cl_1_sockfd = accept(sockfd, (struct sockaddr *) &cli_1_addr, &cli_1_len);
    if (cl_1_sockfd < 0) {
        perror("ERROR on accept [cl_1]");
        return 3;
    } else {
        printf("[INFO] - Succesfully accepted connection\n");
    }

//    cli_2_len = sizeof(cli_2_addr);
//
//    cl_2_sockfd = accept(sockfd, (struct sockaddr *) &cli_2_addr, &cli_2_len);
//    if (cl_2_sockfd < 0) {
//        perror("ERROR on accept [cl_2]");
//        return 3;
//    }

//--------------------------- uspesne prijima spojenia ------------------------------------

    int balicek[52] = {0};
    int aktualnaKarta = 4;
    char harabin = ' ';
    //DATA_K dataK = {balicek, &aktualnaKarta, &harabin, buffer, sockfd, cl_1_sockfd, cl_2_sockfd};

    printf("[INFO] - Data initialized\n");

    //game(dataK);

    n = read(cl_1_sockfd, buffer, 255);
    if (n < 0)
    {
        perror("Error reading from socket");
        return 4;
    } else {
        printf("[INFO] - Succesfully read from socket\n");
    }

    printf("Here is the message: %s\n", buffer);

    const char* msg = "I got your message";
    n = write(cl_1_sockfd, msg, strlen(msg) + 1);
    if (n < 0)
    {
        perror("Error writing to socket");
        return 5;
    } else {
        printf("[INFO] - Succesfully wrote to socket\n");
    }

    char volba = buffer[0];
    switch (volba) {
        case '1':
            msg = "lets play!";
            printf(" - case 1\n");
            break;
        case '2':
            msg = "...coskoro...";
            printf(" - case 2\n");
            break;
        case '3':
            printf(" - case 3\n");
            return 0;
        default:
            break;
    }

    n = write(cl_1_sockfd, msg, strlen(msg) + 1);
    if (n < 0)
    {
        perror("Error writing to socket");
        return 5;
    } else {
        printf("[INFO] - Succesfully wrote to socket\n");
    }

//--------------------------- ukoncenie prijimania spojeni ------------------------------------

    close(cl_1_sockfd);
//    close(cl_2_sockfd);
    close(sockfd);

    return 0;
}