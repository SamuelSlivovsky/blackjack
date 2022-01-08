#include "hrac.h"

void ukazKarty(char *karty) {
    for (int i = 0; i < 5; ++i) {
        vykresliKartu(karty[i]);
    }
}

int rozhodniHodnotuEsa(DATA_H *data) {
    char chr = ' ';
    while (chr != 'y' || chr != 'n') {
        printf("\n");
        printf("Dostali ste Eso, aku chcete aby malo hodnotu?\n");
        printf(" (y - 1, n - 10)\n");
        printf("vasa volba: ");
        scanf(" %c", &chr);
        printf("\n");
    }
    if (chr == 'y') {
        data->karty[*(data->pocetKariet)] = '1';
    } else if (chr == 'n') {
        data->karty[*(data->pocetKariet)] = '0';
    }
    return 0;
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
            case '0':
                karta = 10;
            default:
                break;
        }

        sum += karta;
    }
    *(data->skore) = sum;
}

int start(DATA_H *dataH) {
    int volba = 0;
    while (volba != 1) {
        printf("Vasa volba: ");
        bzero(dataH->buffer, 256);
        fgets(dataH->buffer, 255, stdin);
        volba = atoi(&(dataH->buffer[0]));

        writeMsg(*dataH, dataH->buffer);
        readMsg(*dataH);

        printf("\n%s\n\n", dataH->buffer);
    }

    return 0;
}

void vypisKarty(DATA_H *data) {
    printf("Vase karty: ");
    for (int i = 0; i < 5; ++i) {
        if (data->karty[i] == '0') {
            printf("10 ");
        } else {
            printf("%c ", data->karty[i]);
        }
    }
    vypocitajSkore(data);
    printf(", skore: %d\n", *(data->skore));
}

int hra(DATA_H *dataH) {

    // inicializacia
    for (int i = 0; i < 5; ++i) {
        dataH->karty[i] = 'X';
    }
    dataH->skore = 0;
    *(dataH->pocetKariet) = 2;

    int zaciatok = 1;
    int pocTahov = 2;
    char buffer[256];

    while (pocTahov < 5) {
        printf("pocet tahov %d\n", pocTahov);
        pocTahov++;
        printf("pocet tahov %d\n", pocTahov);

        // zaciatok hry, menu
        if (zaciatok == 1) {
            zaciatok = 0;
            char volba = '0';
            while (1) {
                while (volba != '1' && volba != '2' && volba != '3') {
                    menu();
                    printf("Vasa volba: ");
                    bzero(buffer, 256);
                    fgets(buffer, 255, stdin);
                    volba = buffer[0];
                    printf("volba = %c\n", volba);
//                    printf("\n%s\n\n", buffer);
                }

                printf("idem pisat volbu\n");
                writeMsg(*dataH, buffer);
                printf("napisal som volbu\n");

                printf("idem citat odpoved\n");
                readMsg(*dataH);
                printf("precital som odpoved\n");

                if (volba == '1') {
                    // hrat, prisli mi karty
                    dataH->karty[0] = dataH->buffer[0];
                    dataH->karty[1] = dataH->buffer[1];
//                    pocTahov = 2;
                    printf("zobral som si karty %s\n", dataH->buffer);
                    break;
                } else if (volba == '2') {
                    // historia
                    printf("\n%s\n\n", buffer);
                } else {
                    // koniec
                    zaciatok = -1;
                    printf("zaciatok 1 = %d\n", zaciatok);
                    break;
                }
            }
        }

        if (zaciatok == -1) {
            printf("obaja hraci chceli skoncit\n");
            break;
        }

        printf("som za zaciatkom\n");
        readMsg(*dataH); // cakam kym budem na rade

        // citanie vstupu od hraca
        bzero(buffer, 256);
        int volba = 0;
        hracTah();
        while (volba != 1 && volba != 2 && volba != 3) {
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
            printf("Potiahol si %c\n", dataH->buffer[0]);
            ukazKarty(dataH->karty);
            printf("\n");

            for (int i = 0; i < 5; ++i) {
                if (dataH->karty[i] == '0') {
                    printf("10 ");
                } else {
                    printf("%c ", dataH->karty[i]);
                }
            }
            printf("\n");

//            vypocitajSkore(dataH);
//            printf(", skore: %d\n", *(dataH->skore));

        } else if (volba == 2) {
            pocTahov = 5;
        } else {
            // do nothing
        }
    }

    if (zaciatok == -1) {
        printf("zaciatok 3 = %d\n", zaciatok);
        return 0;
    }

    // vysledky
    printf("vysledky\n");
    readMsg(*dataH);
    printf("\n%s\n\n", buffer);

    // ci chce hrat znova
    char volba = ' ';
    while (volba != 'y' && volba != 'n') {
        restart();
        printf("Vasa volba: ");
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
        volba = buffer[0];
    }

    writeMsg(*dataH, buffer);
    readMsg(*dataH);
    volba = dataH->buffer[0];
    if (volba == 'y') {
        hra(dataH);
    }

    return 0;
}

int writeMsg(DATA_H dataH, char *msg) {
    printf("writing...\n");
    int n = write(dataH.sockfd, msg, strlen(msg) + 1);

    if (n < 0) {
        perror("Error writing to socket");
        return 5;
    } else {
//        printf("[INFO] - Succesfully wrote to socket\n");
        return 0;
    }
}

int readMsg(DATA_H dataH) {
    pthread_mutex_lock(dataH.mutex);
    while (*(dataH.readFlag) == 0) {
        printf("1\n");
        pthread_cond_wait(dataH.canRead, dataH.mutex);
        printf("2\n");
    }
    printf("[INFO] - Som precital\n");
    *(dataH.readFlag) = 0;
    pthread_mutex_unlock(dataH.mutex);
}

void *reading(void *args) {
    printf("reading...\n");
    DATA_H *dataH = (DATA_H *) args;
    char buffer[256];
    int sockfd = dataH->sockfd;
    int n;

    do {
        bzero(buffer, 256*sizeof(char));
        n = read(sockfd, buffer, 256);
        pthread_mutex_lock(dataH->mutex);
        memcpy(dataH->buffer,buffer,256);
        *(dataH->readFlag) = 1;
        pthread_mutex_unlock(dataH->mutex);
        pthread_cond_signal(dataH->canRead);
        if (n < 0) {
            perror("Error reading from socket");
            break;
        } else {
            printf("[INFO] - Succesfully read from socket\n");
            printf("n = %d, buffer = %s\n", n, dataH->buffer);
        }
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
    char karty[5] = {'X', 'X', 'X', 'X', 'X'};
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
    printf("\nVitajte v hre blackjack\n hrat 1\n historia 2\n koniec 3\n");
    //start(&dataH);
    hra(&dataH);
    pthread_join(thread_read, NULL);

//    printf("[INFO] - Thread initialized\n");

//    printf("\nVitajte v hre blackjack\n hrat 1\n historia 2\n koniec 3\n");
//    start(&dataH);
//    hra(&dataH);

//--------------------------- ukoncenie pripojenia na server ------------------------------------
    close(sockfd);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&canRead);

    return 0;
}