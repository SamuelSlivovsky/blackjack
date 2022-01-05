#include "krupier.h"

void hra(DATA_K dataK, DATA_H dataH1, DATA_H dataH2) {
    premiesajBalicek(dataK.balicek);
    rozdajKarty(dataK, dataH1, dataH2);

    for (int i = 0; i < 3; ++i) {
        tah(dataH1, dataK);
        tah(dataH2, dataK);
    }

    vylozitKarty(dataH1);
    vylozitKarty(dataH2);

    porovnaj(dataH1, dataH2, dataK);
}

void tah(DATA_H dataH, DATA_K dataK) {
    if (*(dataH.lock) == 0) {
        writeCharMsg(dataK, "ides", dataH.clsockfd);
        pthread_cond_signal(dataK.canRead);
        char volba = dataK.buffer[0];
        switch (volba) {
            case '1':
                dajKartu(dataK, dataH);
                break;
            case '2':
                *(dataH.lock) = 1;
                break;
            default:
                break;
        }
    }
}

void vylozitKarty(DATA_H dataH) {
    printf("");
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

void rozdajKarty(DATA_K dataK, DATA_H dataH1, DATA_H dataH2) {

//    for (int i = 0; i < 2; ++i) {
//        pthread_mutex_lock(dataK.mutex);
//        writeIntMsg(dataK, &dataK.balicek[i+i*1], dataK.cl_1_sockfd);
//        writeIntMsg(dataK, &dataK.balicek[i+1+i*1], dataK.cl_2_sockfd);
//        pthread_mutex_unlock(dataK.mutex);
//        pthread_cond_signal(dataK.canRead);
//    }

    for (int i = 0; i < 2; ++i) {
        dataH1.karty[i] = dataK.balicek[i+i*1];
        writeIntMsg(dataK, dataK.balicek[i+i*1], dataH1.clsockfd);
        dataH2.karty[i] = dataK.balicek[i+1+i*1];
        writeIntMsg(dataK, dataK.balicek[i+1+i*1], dataH2.clsockfd);
    }

}

void dajKartu(DATA_K dataK, DATA_H dataH) {
    int karta = dataK.balicek[*(dataK.aktualnaKarta)];
    int poc = *(dataH.pocetKariet);
    dataH.karty[poc] = karta;
    (*(dataK.aktualnaKarta))++;
    (*(dataH.pocetKariet))++;
    writeIntMsg(dataK, karta, dataH.clsockfd);
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

int writeCharMsg(DATA_K dataK, char *msg, int client) {
    int n = write(client, msg, strlen(msg) + 1);
    if (n < 0) {
        perror("Error writing to socket");
        return 5;
    } else {
        printf("[INFO] - Succesfully wrote to socket\n");
        return 0;
    }
}

int writeIntMsg(DATA_K dataK, int msg, int client) {
    char str[2];
    sprintf(str, "%d", msg);
    int n = write(client, str, strlen(str) + 1);
    if (n < 0) {
        perror("Error writing to socket");
        return 5;
    } else {
        printf("[INFO] - Succesfully wrote to socket\n");
        return 0;
    }
}

int readMsg(DATA_K dataK, int client) {
    int n = read(client, dataK.buffer, 255);
    if (n < 0) {
        perror("Error reading from socket");
        return 4;
    } else {
        printf("[INFO] - Succesfully read from socket\n");
        return 0;
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

    cli_2_len = sizeof(cli_2_addr);

    cl_2_sockfd = accept(sockfd, (struct sockaddr *) &cli_2_addr, &cli_2_len);
    if (cl_2_sockfd < 0) {
        perror("ERROR on accept [cl_2]");
        return 3;
    }

//--------------------------- uspesne prijima spojenia ------------------------------------
    // krupier
    int balicek[52] = {0};
    int aktualnaKarta = 4;
    char harabin = ' ';

    // hrac A
    int kartyA[5] = {0};
    int pocetKarietA = 2;
    int skoreA = 0;
    int lockA = 0;

    // hrac B
    int kartyB[5] = {0};
    int pocetKarietB = 2;
    int skoreB = 0;
    int lockB = 0;

    // naplnenie struktur
    DATA_H dataH1 = {kartyA, &pocetKarietA, &skoreA, &lockA, cl_1_sockfd};
    DATA_H dataH2 = {kartyB, &pocetKarietB, &skoreB, &lockB, cl_2_sockfd};
    DATA_K dataK = {balicek, &aktualnaKarta, &harabin, buffer, sockfd, cl_1_sockfd, cl_2_sockfd};

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

    // CITANIE
    readMsg(dataK, dataK.cl_1_sockfd);
    /*n = read(cl_1_sockfd, buffer, 255);
    if (n < 0) {
        perror("Error reading from socket");
        return 4;
    } else {
        printf("[INFO] - Succesfully read from socket\n");
    }*/

    // VYPIS
    printf("Here is the message: %s\n", dataK.buffer);

    char *msg = "I got your message";

    // SPRACOVANIE
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

    // ZAPIS
    writeCharMsg(dataK, msg, dataK.cl_1_sockfd);
    /*n = write(cl_1_sockfd, msg, strlen(msg) + 1);
    if (n < 0) {
        perror("Error writing to socket");
        return 5;
    } else {
        printf("[INFO] - Succesfully wrote to socket\n");
    }*/

    // CITANIE
    readMsg(dataK, dataK.cl_1_sockfd);
    /*n = read(cl_1_sockfd, buffer, 255);
    if (n < 0) {
        perror("Error reading from socket");
        return 4;
    } else {
        printf("[INFO] - Succesfully read from socket\n");
    }*/

    // VYPIS
    printf("Here is the message: %s\n", dataK.buffer);

    // SPRACOVANIE
    volba = buffer[0];
    switch (volba) {
        case '1':
            msg = "karta";
            printf(" - case 1\n");
            break;
        case '2':
            msg = "lock";
            printf(" - case 2\n");
            break;
        case '3':
            msg = "nic";
            printf(" - case 3\n");
            return 0;
        default:
            break;
    }

    // ZAPIS
    writeCharMsg(dataK, msg, dataK.cl_1_sockfd);
    /*n = write(cl_1_sockfd, msg, strlen(msg) + 1);
    if (n < 0) {
        perror("Error writing to socket");
        return 5;
    } else {
        printf("[INFO] - Succesfully wrote to socket\n");
    }*/

//--------------------------- ukoncenie prijimania spojeni ------------------------------------

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&canRead);

    close(cl_1_sockfd);
    close(cl_2_sockfd);
    close(sockfd);

    return 0;
}