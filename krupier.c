#include "krupier.h"

void hra(DATA_K dataK, DATA_H dataH1, DATA_H dataH2, HISTORY history) {

    //HISTORY history = {historia, *(dataK.pocetHier)};

    premiesajBalicek(dataK.balicek);
    rozdajKarty(dataK, dataH1, dataH2);

    for (int i = 0; i < 3; ++i) {
        tah(dataH1, dataK, *(dataH2.lock));
        tah(dataH2, dataK, *(dataH1.lock));
    }

    printf("Karty hraca 1: \n");
    vylozitKarty(dataH1);
    printf("Karty hraca 2: \n");
    vylozitKarty(dataH2);

    int pokracuj = porovnaj(dataH1, dataH2, dataK);

    //naplnenie historie
    history.historia[*(history.pocetHier)] = *(dataK.harabin);

    printf("historia pred>\n");
    for (int i = 0; i < *(history.pocetHier); ++i) {
        printf(" %c ", history.historia[i]);
    }
    printf("\n");
    printf(" %s ", history.historia);
    printf("\n");

    (*(history.pocetHier))++;
    char novePole[*(history.pocetHier) + 1];
    for (int i = 0; i < *(history.pocetHier); ++i) {
        novePole[i] = history.historia[i];
    }
    history.historia = novePole;

    printf("historia po>\n");
    for (int i = 0; i < *(history.pocetHier); ++i) {
        printf(" %c ", history.historia[i]);
    }
    printf("\n");
    printf(" %s ", history.historia);
    printf("\n");

    if (pokracuj == 2) {
        inicializacia(dataK, dataH1, dataH2);
        hra(dataK, dataH1, dataH2, history);
    }
    //KONIEC

}

void inicializacia(DATA_K dataK, DATA_H dataH1, DATA_H dataH2) {
    // krupier
    for (int i = 0; i < 52; ++i) {
        dataK.balicek[i] = ' ';
    }

    *(dataK.aktualnaKarta) = 4;
    *(dataK.harabin) = ' ';

// hrac A
    for (int i = 0; i < 5; ++i) {
        dataH1.karty[i] = 'X';
    }
    *(dataH1.pocetKariet) = 2;
    dataH1.skore = 0;
    dataH1.lock = 0;

// hrac B
    for (int i = 0; i < 5; ++i) {
        dataH2.karty[i] = 'X';
    }
    *(dataH2.pocetKariet) = 2;
    dataH2.skore = 0;
    dataH2.lock = 0;
}

void tah(DATA_H dataH, DATA_K dataK, int lock) {
    printf("aktualny lock: %d\n", *(dataH.lock));
    if (*(dataH.lock) != 1) {
        writeCharMsg(dataK, "i", dataH.clsockfd);
        if (dataH.clsockfd == dataK.cl_1_sockfd) {
            printf("lock 2: %d\n", lock);
            if (lock != 1) {
                writeCharMsg(dataK, "n", dataK.cl_2_sockfd);
                printf("pls1\n");
            }
        } else {
            printf("lock 1: %d\n", lock);
            if (lock != 1) {
                writeCharMsg(dataK, "n", dataK.cl_1_sockfd);
                printf("pls2\n");
            }
        }
        readMsg(dataK, dataH.clsockfd);
        char volba = dataK.buffer[0];
        switch (volba) {
            case '1':
                dajKartu(dataK, dataH);
                break;
            case '2':
                *(dataH.lock) = 1;
                printf("lock\n");
                break;
            default:
                break;
        }
    }
}

void vylozitKarty(DATA_H dataH) {
    for (int i = 0; i < 5; ++i) {
        vykresliKartu(dataH.karty[i]);
    }
}

void premiesajBalicek(char *balicek) {
    printf("premiesaj balicek\n");
    int nahodnaKarta;
    char znaky[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K'};
    bool rovnakaChar = true;
    char znak = ' ';

    for (int i = 0; i < 52; ++i) {
        balicek[i] = ' ';
    }

    for (int i = 0; i < 52; ++i) {

        nahodnaKarta = rand() % 13;
        znak = znaky[nahodnaKarta];
        int opakChar = 0;
        for (int k = 0; k < 52; ++k) {
            if (balicek[k] != znak) {
                rovnakaChar = false;
            }
            if (balicek[k] == znak && opakChar < 4) {
                opakChar++;
                rovnakaChar = false;
            }
            if (opakChar > 3) {
                i--;
                rovnakaChar = true;
                break;
            }
        }
        if (!rovnakaChar) {
            balicek[i] = znak;
        }

    }
    for (int i = 0; i < 52; ++i) {
        printf("%c ", balicek[i]);
    }
    printf("\n");
}

void rozdajKarty(DATA_K dataK, DATA_H dataH1, DATA_H dataH2) {

    printf("rozdaj karty\n");
    for (int i = 0; i < 2; ++i) {
        dataH1.karty[i] = dataK.balicek[i + i * 1];
        printf("%c \n", dataK.balicek[i + i * 1]);
        writeCharMsg(dataK, &(dataK.balicek[i + i * 1]), dataH1.clsockfd);

        readMsg(dataK, dataK.cl_1_sockfd);
        dataH2.karty[i] = dataK.balicek[i + 1 + i * 1];
        printf("%c \n", dataK.balicek[i + 1 + i * 1]);
        writeCharMsg(dataK, &(dataK.balicek[i + 1 + i * 1]), dataH2.clsockfd);
        readMsg(dataK, dataK.cl_2_sockfd);
    }
}

void dajKartu(DATA_K dataK, DATA_H dataH) {
    char karta = dataK.balicek[*(dataK.aktualnaKarta)];
    int poc = *(dataH.pocetKariet);
    dataH.karty[poc] = karta;
    (*(dataK.aktualnaKarta))++;
    (*(dataH.pocetKariet))++;
    writeCharMsg(dataK, &karta, dataH.clsockfd);
}

void vypocitajSkore(DATA_H *data) {
    int sum = 0;
    for (int i = 0; i < *(data->pocetKariet); ++i) {
        int karta = 0;

        switch (data->karty[i]) {
            case 'A':
                karta = 1;
                break;
            case '2':
                karta = 2;
                break;
            case '3':
                karta = 3;
                break;
            case '4':
                karta = 4;
                break;
            case '5':
                karta = 5;
                break;
            case '6':
                karta = 6;
                break;
            case '7':
                karta = 7;
                break;
            case '8':
                karta = 8;
                break;
            case '9':
                karta = 9;
                break;
            default:
                karta = 10;
                break;
        }

        sum += karta;
    }
    *(data->skore) = sum;
}

int porovnaj(DATA_H dataH1, DATA_H dataH2, DATA_K dataK) {
    vypocitajSkore(&dataH1);
    vypocitajSkore(&dataH2);

    int skoreA = *(dataH1.skore);
    int skoreB = *(dataH2.skore);
    int rozdielA = 21 - skoreA;
    int rozdielB = 21 - skoreB;
    char *msg1 = " ";
    char *msg2 = " ";

    if (rozdielA >= 0 && rozdielA < rozdielB || rozdielB < 0 && rozdielA >= 0) {
        printf("Vyhral hrac A, skore bolo - %d : %d (A:B)\n", skoreA, skoreB);
        *(dataK.harabin) = 'A';
        msg1 = "Vyhral si\n";
        msg2 = "Prehral si\n";
    } else if (rozdielB >= 0 && rozdielB < rozdielA || rozdielA < 0 && rozdielB >= 0) {
        printf("Vyhral hrac B, skore bolo - %d : %d (B:A)\n", skoreB, skoreA);
        *(dataK.harabin) = 'B';
        msg1 = "Prehral si\n";
        msg2 = "Vyhral si\n";
    } else if (rozdielA == rozdielB && rozdielA >= 0) {
        printf("Remiza, skore bolo - %d : %d (A:B)\n", skoreA, skoreB);
        *(dataK.harabin) = 'R';
        msg1 = "Remiza\n";
        msg2 = "Remiza\n";
    } else {
        printf("Nikto nevyhral, skore bolo - %d : %d (A:B)\n", skoreA, skoreB);
        *(dataK.harabin) = 'N';
        msg1 = "Nikto nevyhral\n";
        msg2 = "Nikto nevyhral\n";
    }

    int pokracuj = 0;
// NEMENIT PORADIE
    writeCharMsg(dataK, msg1, dataK.cl_1_sockfd);
    readMsg(dataK, dataK.cl_1_sockfd);

    writeCharMsg(dataK, msg2, dataK.cl_2_sockfd);
    readMsg(dataK, dataK.cl_2_sockfd);

    writeCharMsg(dataK, dataH2.karty, dataK.cl_1_sockfd);
    readMsg(dataK, dataK.cl_1_sockfd);

    if (dataK.buffer[0] == 'y') {
        pokracuj++;
    }
    writeCharMsg(dataK, dataH1.karty, dataK.cl_2_sockfd);
    readMsg(dataK, dataK.cl_2_sockfd);

    if (dataK.buffer[0] == 'y') {
        pokracuj++;
    }


    return pokracuj;
}

int writeCharMsg(DATA_K dataK, char *msg, int client) {
    int n = write(client, msg, strlen(msg) + 1);
    if (n < 0) {
        perror("Error writing to socket");
        return 5;
    } else {
        printf("[INFO] - Succesfully wrote to socket %d\n", client);
        return 0;
    }
}

int readMsg(DATA_K dataK, int client) {
    bzero(dataK.buffer, 256);
    int n = read(client, dataK.buffer, 255);
    if (n < 0) {
        perror("Error reading from socket");
        return 4;
    } else {
        printf("[INFO] - Succesfully read from socket %d\n", client);
        return 0;
    }
}

int start(DATA_K dataK, DATA_H dataH1, DATA_H dataH2) {

    int potvrdH1 = 2;
    int potvrdH2 = 3;
    char *msg = "I got your message";
    char volba = ' ';
    while (potvrdH1 != potvrdH2) {
// CITANIE Z HRAC1

        if (potvrdH1 == 2) {
            readMsg(dataK, dataK.cl_1_sockfd);

            // VYPIS
            printf("Here is the message: %s\n", dataK.buffer);

            // SPRACOVANIE HRAC1
            volba = dataK.buffer[0];
            switch (volba) {
                case '1':
                    msg = "lets play!";
                    potvrdH1 = 1;
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

            // ZAPIS HRAC1
            writeCharMsg(dataK, msg, dataK.cl_1_sockfd);
        }

        if (potvrdH2 == 3) {
            // CITANIE HRAC2
            readMsg(dataK, dataK.cl_2_sockfd);
            printf("Here is the message: %s\n", dataK.buffer);

            msg = "I got your message";

            // SPRACOVANIE HRAC2
            volba = dataK.buffer[0];
            switch (volba) {
                case '1':
                    msg = "lets play!";
                    potvrdH2 = 1;
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

            // ZAPIS HRAC2
            writeCharMsg(dataK, msg, dataK.cl_2_sockfd);
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {

//--------------------------- uvodne nastavovanie ------------------------------------

    srand(time(NULL));
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
        printf("[INFO] - Succesfully accepted connection [cl_1]\n");
    }

    cli_2_len = sizeof(cli_2_addr);

    cl_2_sockfd = accept(sockfd, (struct sockaddr *) &cli_2_addr, &cli_2_len);
    if (cl_2_sockfd < 0) {
        perror("ERROR on accept [cl_2]");
        return 3;
    } else {
        printf("[INFO] - Succesfully accepted connection [cl_2]\n");
    }

//--------------------------- uspesne prijima spojenia ------------------------------------
// krupier
    char balicek[52] = {' '};
    int aktualnaKarta = 4;
    char harabin = ' ';

// hrac A
    char kartyA[5] = {'X', 'X', 'X', 'X', 'X'};
    int pocetKarietA = 2;
    int skoreA = 0;
    int lockA = 0;

// hrac B
    char kartyB[5] = {'X', 'X', 'X', 'X', 'X'};
    int pocetKarietB = 2;
    int skoreB = 0;
    int lockB = 0;

    // historia

    char historia[1] = {'X'};
    int pocetHier = 0;
// naplnenie struktur
    DATA_H dataH1 = {kartyA, &pocetKarietA, &skoreA, &lockA, cl_1_sockfd};
    DATA_H dataH2 = {kartyB, &pocetKarietB, &skoreB, &lockB, cl_2_sockfd};
    DATA_K dataK = {balicek, &aktualnaKarta, &harabin, buffer, sockfd, cl_1_sockfd, cl_2_sockfd};
    HISTORY history = {historia, &pocetHier};
    printf("[INFO] - Data initialized\n");

// vlakno, mutex a cond
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    pthread_cond_t canRead;
    pthread_cond_init(&canRead, NULL);

//    pthread_t thread_read;
//    pthread_create(&thread_read, NULL,NULL, &dataK);
//    hra(dataK, dataH1, dataH2);
//    pthread_join(thread_read, NULL);

    printf("[INFO] - Thread initialized\n");

//    while () {
//        if ()
//            start(dataK, dataH1, dataH2);
//        hra(dataK, dataH1, dataH2);
//    }

    start(dataK, dataH1, dataH2);
    hra(dataK, dataH1, dataH2, history);

//--------------------------- ukoncenie prijimania spojeni ------------------------------------

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&canRead);

    close(cl_1_sockfd);
    close(cl_2_sockfd);
    close(sockfd);

    return 0;
}