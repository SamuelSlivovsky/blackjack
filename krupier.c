#include "krupier.h"


int hra(DATA_K dataK, DATA_H dataH1, DATA_H dataH2, HISTORY history) {

    premiesajBalicek(dataK.balicek);
    dataK.balicek[5] = 'A';
    char volba = ' ';
    int hraj = 0;
    int koniec = 0;
    int pocitadlo = 0;
    char buffer[256];

    while (hraj != 2) {
        pocitadlo++;

        if (pocitadlo % 2 != 0) {
            // HRAC 1
            while (volba != '1' && volba != '2') {
                menu();
                printf("Vasa volba: ");
                bzero(buffer, 256);
                fgets(buffer, 255, stdin);
                volba = buffer[0];
            }
        } else {
            // HRAC 2
            writeMsg(dataK, "ides");
            readMsg(dataK);
            volba = dataK.buffer[0];
        }

        switch (volba) {
            case '1':
                hraj++;
                break;
            default:
                koniec++;
                break;
        }

        if (koniec != 0) {
            writeMsg(dataK, "q");
            return 0;
        }
    }

    rozdajKarty(dataK, dataH1, dataH2);

    for (int i = 0; i < 3; ++i) {
        if (*(dataH1.lock) != 1)
            tah(dataH1, dataK);
        if (*(dataH2.lock) != 1) {
//            while (strcmp("idem", dataK.buffer) != 0) {
//                writeMsg(dataK, "ides");
//            }
            writeMsg(dataK, "ides");
            tah(dataH2, dataK);
        }
    }

    printf("Karty hraca 1: \n");
    vylozitKarty(dataH1);
    printf("Karty hraca 2: \n");
    vylozitKarty(dataH2);

    writeMsg(dataK,"cakaj");
    int pokracuj = porovnaj(dataH1, dataH2, dataK);

    //naplnenie historie
    printf("historia pred: %s\n", history.historia);

    history.historia[*(history.pocetHier)] = *(dataK.harabin);

    (*(history.pocetHier))++;
    char novePole[*(history.pocetHier) + 1];
    for (int i = 0; i < *(history.pocetHier); ++i) {
        novePole[i] = history.historia[i];
    }
    novePole[*(history.pocetHier)] = '\0';
    history.historia = novePole;

    printf("historia po: %s\n", history.historia);

    if (pokracuj == 2) {
        inicializacia(dataK, dataH1, dataH2);
        hra(dataK, dataH1, dataH2, history);
    }

    writeMsg(dataK, "q");
    return 0;
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
        dataH1.karty[i] = '_';
    }
    *(dataH1.pocetKariet) = 2;
    dataH1.skore = 0;
    dataH1.lock = 0;

// hrac B
    for (int i = 0; i < 5; ++i) {
        dataH2.karty[i] = '_';
    }
    *(dataH2.pocetKariet) = 2;
    dataH2.skore = 0;
    dataH2.lock = 0;
}

void tah(DATA_H dataH, DATA_K dataK) {
    char volba = ' ';
    char buffer[256];
    if (dataH.clsockfd == dataK.cl_2_sockfd) {
        hracTah();
        while (volba != '1' && volba != '2') {
            printf("Vasa volba: ");
            bzero(buffer, 256);
            fgets(buffer, 255, stdin);
            volba = buffer[0];
        }
    } else {
        readMsg(dataK);
        volba = dataK.buffer[0];
    }

    switch (volba) {
        case '1':
            dajKartu(dataK, dataH);
            break;
        default:
            break;
    }

    if (dataH.clsockfd != dataK.cl_2_sockfd) {

        readMsg(dataK);
        for (int i = 0; i < 5; ++i) {
            dataH.karty[i] = dataK.buffer[i];
            printf("%c\n",dataH.karty[i]);
        }


    }
}

void vylozitKarty(DATA_H dataH) {
    for (int i = 0; i < 5; ++i) {
        vykresliKartu(dataH.karty[i]);
    }
}

void premiesajBalicek(char *balicek) {
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
        dataH2.karty[i] = dataK.balicek[i + 1 + i * 1];
        printf("%c \n", dataK.balicek[i + 1 + i * 1]);
    }

    printf("karty1 = %s\n", dataH1.karty);
    printf("karty2 = %s\n", dataH2.karty);

    writeMsg(dataK, dataH2.karty);
}

void dajKartu(DATA_K dataK, DATA_H dataH) {
    char karta = dataK.balicek[*(dataK.aktualnaKarta)];
    int poc = *(dataH.pocetKariet);
    dataH.karty[poc] = karta;
    (*(dataK.aktualnaKarta))++;
    (*(dataH.pocetKariet))++;
    if (dataH.clsockfd == dataK.cl_1_sockfd)
        writeMsg(dataK, &karta);
    else {
        ukazKarty(dataH);
    }
}

void ukazKarty(DATA_H data) {
    for (int i = 0; i < 5; ++i) {
        vykresliKartu(data.karty[i]);
    }
    printf("Vase karty: ");
    for (int i = 0; i < 5; ++i) {
        if (data.karty[i] == '0') {
            printf("10 ");
        } else {
            printf("%c ", data.karty[i]);
        }
    }
    vypocitajSkore(&data);
    printf(", sucet: %d\n", *(data.skore));
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
    char buffer[250];
    char *msg;
    bzero(buffer, 250 * sizeof(char));

    if (rozdielA >= 0 && rozdielA < rozdielB || rozdielB < 0 && rozdielA >= 0) {
        sprintf(buffer, "Vyhral hrac A, skore bolo - %d : %d (A:B)\n", skoreA, skoreB);
        *(dataK.harabin) = 'A';
    } else if (rozdielB >= 0 && rozdielB < rozdielA || rozdielA < 0 && rozdielB >= 0) {
        sprintf(buffer, "Vyhral hrac B, skore bolo - %d : %d (B:A)\n", skoreB, skoreA);
        *(dataK.harabin) = 'B';
    } else if (rozdielA == rozdielB && rozdielA >= 0) {
        sprintf(buffer, "Remiza, skore bolo - %d : %d (A:B)\n", skoreA, skoreB);
        *(dataK.harabin) = 'R';
    } else {
        sprintf(buffer, "Nikto nevyhral, skore bolo - %d : %d (A:B)\n", skoreA, skoreB);
        *(dataK.harabin) = 'N';
    }

    msg = buffer;
    printf("%s", buffer);
    writeMsg(dataK, "nic");

    int pokracuj = 0;
    char volba = ' ';

    restart();
    while (volba != 'y' && volba != 'n') {
        printf("Vasa volba: ");
        bzero(buffer, 250);
        fgets(buffer, 249, stdin);
        volba = buffer[0];
    }
    if (volba == 'y') {
        pokracuj++;
    }
//    writeMsg(dataK, "ides");
//    writeMsg(dataK, "msg");
    writeMsg(dataK, msg);
    readMsg(dataK);

    if (dataK.buffer[0] == 'y') {
        pokracuj++;
    }
    writeMsg(dataK, &volba);
    return pokracuj;
}

int writeMsg(DATA_K dataK, char *msg) {
    int n = write(dataK.cl_1_sockfd, msg, strlen(msg) + 1);
    if (n < 0) {
        perror("Error writing to socket");
        return 5;
    } else {
//        printf("[INFO] - Succesfully wrote to socket %d\n", dataK.cl_1_sockfd);
        return 0;
    }
}

void readMsg(DATA_K dataK) {
    cakaj();
    pthread_mutex_lock(dataK.mutex);
    while (*(dataK.readFlag) == 0) {
        pthread_cond_wait(dataK.canRead, dataK.mutex);
    }
    *(dataK.readFlag) = 0;
    pthread_mutex_unlock(dataK.mutex);
}

void *reading(void *args) {
//    printf("reading...\n");
    DATA_K *dataK = (DATA_K *) args;
    char buffer[256];
    int sockfd = dataK->cl_1_sockfd;
    int n;

    do {
        bzero(buffer, 256 * sizeof(char));
        n = read(sockfd, buffer, 256);
        pthread_mutex_lock(dataK->mutex);
        memcpy(dataK->buffer, buffer, 256);
        *(dataK->readFlag) = 1;
        pthread_mutex_unlock(dataK->mutex);
        pthread_cond_signal(dataK->canRead);
        if (n < 0) {
            perror("Error reading from socket");
            break;
        } else {
            printf("[INFO] - Succesfully read from socket n.%d\n", sockfd);
            printf("[INFO] - buffer = %s\n", dataK->buffer);
        }
        if (buffer[0] == 'q')
            break;
    } while (n > 0);

    printf("[INFO] - Koniec citania\n");
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
//
//    cl_2_sockfd = accept(sockfd, (struct sockaddr *) &cli_2_addr, &cli_2_len);
//    if (cl_2_sockfd < 0) {
//        perror("ERROR on accept [cl_2]");
//        return 3;
//    } else {
//        printf("[INFO] - Succesfully accepted connection [cl_2]\n");
//    }

//--------------------------- uspesne prijima spojenia ------------------------------------
// krupier
    char balicek[52] = {' '};
    int aktualnaKarta = 4;
    char harabin = ' ';
    int readFlag = 0;
    int readSockfd = 0;

    // historia
    char historia[1] = {'X'};
    int pocetHier = 0;

// hrac A
    char kartyA[5] = {'_', '_', '_', '_', '_'};
    int pocetKarietA = 2;
    int skoreA = 0;
    int lockA = 0;

// hrac B
    char kartyB[5] = {'_', '_', '_', '_', '_'};
    int pocetKarietB = 2;
    int skoreB = 0;
    int lockB = 0;

// naplnenie struktur
    DATA_H dataH1 = {kartyA, &pocetKarietA, &skoreA, &lockA, cl_2_sockfd};
    DATA_H dataH2 = {kartyB, &pocetKarietB, &skoreB, &lockB, cl_1_sockfd};
    HISTORY history = {historia, &pocetHier};
    printf("[INFO] - Data initialized\n");

// vlakno, mutex a cond
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    pthread_cond_t canRead;
    pthread_cond_init(&canRead, NULL);

    DATA_K dataK = {balicek, &aktualnaKarta, &readFlag, &harabin, buffer, sockfd, cl_1_sockfd, cl_2_sockfd, &readSockfd,
                    &mutex, &canRead};

    pthread_t thread_read;
    pthread_create(&thread_read, NULL, reading, &dataK);
    printf("[INFO] - Thread created\n");

    hra(dataK, dataH1, dataH2, history);

    pthread_join(thread_read, NULL);

//--------------------------- ukoncenie prijimania spojeni ------------------------------------

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&canRead);

    close(cl_1_sockfd);
//    close(cl_2_sockfd);
    close(sockfd);

    return 0;
}