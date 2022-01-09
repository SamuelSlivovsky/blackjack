#include "hrac.h"

void ukazKarty(DATA_H *data) {
    for (int i = 0; i < 5; ++i) {
        vykresliKartu(data->karty[i]);
    }
    printf("Vase karty: ");
    for (int i = 0; i < 5; ++i) {
        if (data->karty[i] == '0') {
            printf("10");
        } else {
            printf("%c ", data->karty[i]);
        }
    }
    vypocitajSkore(data);
    printf(", sucet: %d\n", *(data->skore));
}

void rozhodniHodnotuEsa(DATA_H *data, int pozicia) {
    char chr = ' ';

    while (chr != 'j' && chr != 'd') {
        printf("\n");
        printf("Dostali ste Eso, aku chcete aby malo hodnotu?\n");
        printf(" (j - 1, d - 10)\n");
        printf("vasa volba: ");
        scanf(" %c", &chr);
        printf("\n");
    }
    if (chr == 'j') {
        data->karty[pozicia] = '1';
    } else if (chr == 'd') {
        data->karty[pozicia] = '0';
    }
}

void vypocitajSkore(DATA_H *data) {
    int sum = 0;
    for (int i = 0; i < *(data->pocetKariet); ++i) {
        int karta = 0;
        char aktKarta = (data->karty[i]);

        switch (aktKarta) {
            case '1':
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
    data->skore = &sum;
}

int hra(DATA_H *dataH) {

    // inicializacia
    for (int i = 0; i < 5; ++i) {
        dataH->karty[i] = '_';
    }
//    dataH->karty[4] = '\0';
    dataH->skore = 0;
    *(dataH->pocetKariet) = 2;

    int zaciatok = 1;
    int pocTahov = 2;
    char buffer[256];
    bzero(buffer, 256);

    while (pocTahov < 5) {
        pocTahov++;

        // zaciatok hry, menu
        if (zaciatok == 1) {
            zaciatok = 0;
            cakaj();
            readMsg(*dataH);
            if (dataH->buffer[0] == 'q')
                return 0;
            char volba = '0';
            while (1) {
                while (volba != '1' && volba != '2') {
                    menu();
                    printf("Vasa volba: ");
                    bzero(buffer, 256);
                    fgets(buffer, 255, stdin);
                    volba = buffer[0];
                    printf("volba = %c\n", volba);
                }

                writeMsg(*dataH, buffer);

                readMsg(*dataH);

                if (volba == '1') {
                    // hrat, prisli mi karty
                    dataH->karty[0] = dataH->buffer[0];
                    if (dataH->buffer[0] == 'A') {
                        rozhodniHodnotuEsa(dataH, 0);
                    }
                    dataH->karty[1] = dataH->buffer[1];
                    if (dataH->buffer[1] == 'A') {
                        rozhodniHodnotuEsa(dataH, 1);
                    }
                    ukazKarty(dataH);
                    break;
                } else {
                    // koniec
                    zaciatok = -1;
                    printf("zaciatok 1 = %d\n", zaciatok);
                    break;
                }
            }
        }

        if (zaciatok == -1) {
            break;
        }

        // --------------------------------- TAH ------------------------------------

        // cakam kym budem na rade
        cakaj();
        readMsg(*dataH);

        // citanie vstupu od hraca
        bzero(buffer, 256);
        int volba = 0;
        hracTah();
        while (volba != 1 && volba != 2) {
            printf("Vasa volba: ");
            bzero(buffer, 256);
            fgets(buffer, 255, stdin);
            volba = atoi(&(buffer[0]));
            printf("volba = %d\n", volba);
        }

        // poslem svoju volbu na server
        writeMsg(*dataH, buffer);

        // spracovanie volby
        if (volba == 1) {
            // tahaj kartu
            readMsg(*dataH);
            int poc = *(dataH->pocetKariet);
            dataH->karty[poc] = dataH->buffer[0];
            (*(dataH->pocetKariet))++;
            printf("Prisla mi karta %c\n", dataH->buffer[0]);
            if (dataH->buffer[0] == 'A') {
                rozhodniHodnotuEsa(dataH, poc);
            }
            ukazKarty(dataH);
            printf("\n");

            writeMsg(*dataH, dataH->karty);
        }

    }

    if (zaciatok == -1) {
        return 0;
    }

    readMsg(*dataH);
    // ----------------------------------- VYSLEDKY ---------------------------------------

    // vysledky

    readMsg(*dataH);
    printf("Karty Hraca 1: \n");
    for (int i = 0; i < 5; ++i) {
        vykresliKartu(dataH->karty[i]);

    }
    printf("Karty Hraca 2: \n");
    for (int i = 0; i < 5; ++i) {
        vykresliKartu(dataH->buffer[i]);

    }

    writeMsg(*dataH, " ");
    readMsg(*dataH);
    printf("Vysledok:\n%s\n", dataH->buffer);
    // ci chce hrat znova
    char volba = ' ';
    char volba2 = ' ';
    while (volba != 'y' && volba != 'n') {
        restart();
        printf("Vasa volba: ");
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
        volba = buffer[0];
    }

    writeMsg(*dataH, buffer); // zapise svoju volbu na server
    readMsg(*dataH); // precita si odpoved, bud y alebo n
    volba2 = dataH->buffer[0];
    if (volba == 'y' && volba2 == 'y') {
        hra(dataH);
    }
    writeMsg(*dataH, "q");
    return 0;
}

int writeMsg(DATA_H dataH, char *msg) {
    int n = write(dataH.sockfd, msg, strlen(msg) + 1);

    if (n < 0) {
        perror("Error writing to socket");
        return 5;
    } else {
//        printf("[INFO] - Succesfully wrote to socket\n");
        return 0;
    }
}

void readMsg(DATA_H dataH) {

    pthread_mutex_lock(dataH.mutex);
    while (*(dataH.readFlag) == 0) {
        pthread_cond_wait(dataH.canRead, dataH.mutex);
    }
    *(dataH.readFlag) = 0;
    pthread_mutex_unlock(dataH.mutex);
}

void *reading(void *args) {
    DATA_H *dataH = (DATA_H *) args;
    char buffer[256];
    int sockfd = dataH->sockfd;
    int n;

    do {
        bzero(buffer, 256 * sizeof(char));
        n = read(sockfd, buffer, 256);
        pthread_mutex_lock(dataH->mutex);
        memcpy(dataH->buffer, buffer, 256);
        *(dataH->readFlag) = 1;
        pthread_mutex_unlock(dataH->mutex);
        pthread_cond_signal(dataH->canRead);
        if (n < 0) {
            perror("Error reading from socket");
            break;
        } else {
            //printf("[INFO] - Succesfully read from socket\n");
            // printf("buffer = %s\n", dataH->buffer);
        }
        if (buffer[0] == 'q')
            break;
    } while (n > 0);

    printf("[INFO] - Koniec citania\n");
    return 0;
}

int main(int argc, char *argv[]) {

//--------------------------- uvodne nastavovanie ------------------------------------

    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        return 1;
    }

    server = gethostbyname(argv[1]); // z hostname si ziskame info o serveri
    if (server == NULL) {
        fprintf(stderr, "Error, no such host\n");
        return 2;
    } else {
        printf("[INFO] - Succesfully connected to server\n");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr)); // vycistenie struktury
    serv_addr.sin_family = AF_INET;
    bcopy(
            (char *) server->h_addr,
            (char *) &serv_addr.sin_addr.s_addr,
            server->h_length
    );
    serv_addr.sin_port = htons(atoi(argv[2]));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 3;
    } else {
        printf("[INFO] - Succesfully created socket\n");
    }

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error connecting to socket");
        return 4;
    } else {
        printf("[INFO] - Succesfully connected to socket\n");
    }

//--------------------------- uspesne pripojeny na server ------------------------------------

    // naplnenie struktur
    char karty[5] = {'_', '_', '_', '_', '_'};
    int pocetKariet = 2;
    int skore = 0;
    int readFlag = 0;

    printf("[INFO] - Data initialized\n");

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    pthread_cond_t canRead;
    pthread_cond_init(&canRead, NULL);

    DATA_H dataH = {karty, &pocetKariet, &skore, &readFlag, buffer, sockfd, &mutex, &canRead};

    pthread_t thread_read;
    pthread_create(&thread_read, NULL, reading, &dataH);
    printf("[INFO] - Thread started\n");
    hra(&dataH);
    pthread_join(thread_read, NULL);


//--------------------------- ukoncenie pripojenia na server ------------------------------------
    close(sockfd);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&canRead);

    return 0;
}