#include "hrac.h"

void ukazKarty(DATA_H *data) {
    for (int i = 0; i < 5; ++i) {
        vykresliKartu(data->karty[i]);
    }
}

void ukazKartyProtivnika(char *karty) {
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
        data->karty[*(data->pocetKariet)] = 1;
    } else if (chr == 'n') {
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

int hra(DATA_H *data) {

    bzero(data->buffer, 256);
    int n = read(data->sockfd, data->buffer, 255);
    if (n < 0) {
        perror("Error reading from socket");
        return 6;
    }
    printf("%s\n", data->buffer);

    printf("Vasa volba: ");
    bzero(data->buffer, 256);
    fgets(data->buffer, 255, stdin);
    n = write(data->sockfd, data->buffer, strlen(data->buffer));
    if (n < 0) {
        perror("Error writing to socket");
        return 5;
    }

}

int writeMsg(DATA_H dataH, char *msg) {
    printf("writing\n");
    int n = write(dataH.sockfd, msg, strlen(msg) + 1);

    if (n < 0) {
        perror("Error writing to socket");
        return 5;
    } else {
        printf("[INFO] - Succesfully wrote to socket\n");
        return 0;
    }
}

int readMsg(DATA_H dataK) {
    printf("reading\n");
    bzero(dataK.buffer, 256);
    int n = read(dataK.sockfd, dataK.buffer, 255);
    if (n < 0) {
        perror("Error reading from socket");
        return 4;
    } else {
        printf("[INFO] - Succesfully read from socket\n");
        return 0;
    }

}

int start(DATA_H *dataH) {
    int volba = 0;
    while (volba != 1) {
        printf("Vasa volba: ");
        bzero(dataH->buffer, 256);
        fgets(dataH->buffer, 255, stdin);
        volba = atoi(&(dataH->buffer[0]));
        //ZAPIS
        writeMsg(*dataH, dataH->buffer);

        //CITAJ
        readMsg(*dataH);

        printf("%s\n", dataH->buffer);
    }

    return 0;
}
void vypisKarty(DATA_H *data){
    printf("Vase karty: ");
    for (int i = 0; i < 5; ++i) {

        printf("%c ", data->karty[i]);
    }
    printf("\n");
}
int tah(DATA_H *dataH) {
    char *msg = " ";
    readMsg(*dataH);
    writeMsg(*dataH, msg);
    dataH->karty[0] = dataH->buffer[0];
    readMsg(*dataH);
    writeMsg(*dataH, msg);
    dataH->karty[1] = dataH->buffer[0];
    readMsg(*dataH);

    ukazKarty(dataH);
    int pocTahov = 2;
    while (pocTahov != 5) {
        printf("125\n");
        pocTahov++;
        if (dataH->buffer[0] == 'n') {

            printf("Cakajte dokial druhy hrac ukonci svoje kolo\n");
        }

        while (dataH->buffer[0] != 'i') {
            readMsg(*dataH);
            printf("while\n");
        }
        printf("idem citat buffer\n");
        if (dataH->buffer[0] == 'i') {
            hracTah();
            ukazKarty(dataH);
            int volba = 0;
            while (volba != 1 && volba != 2 && volba != 3) {
                printf("Vasa volba: ");
                bzero(dataH->buffer, 256);
                fgets(dataH->buffer, 255, stdin);
                volba = atoi(&(dataH->buffer[0]));

            }

            writeMsg(*dataH, dataH->buffer);

            //CITAJ
            readMsg(*dataH);
            if (volba == 1) {
                int poc = *(dataH->pocetKariet);
                dataH->karty[poc] = dataH->buffer[0];
                (*(dataH->pocetKariet))++;
            }
            if (volba == 2){
                pocTahov = 5;
            }

            if (volba == 3){
                pocTahov = 5;
            }

            printf("164\n");
        }

    }
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
    DATA_H dataH = {karty, &pocetKariet, &skore, buffer, sockfd};

    printf("[INFO] - Data initialized\n");

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    pthread_cond_t canRead;
    pthread_cond_init(&canRead, NULL);

//    pthread_t thread_read;
//    pthread_create(&thread_read, NULL,NULL, &dataK);
//    game(dataK);
//    pthread_join(thread_read, NULL);

    printf("[INFO] - Thread initialized\n");

    printf("\nVitajte v hre blackjack\n hrat 1\n historia 2\n koniec 3\n");
    start(&dataH);
    tah(&dataH);

    readMsg(dataH);
    printf("%s", dataH.buffer);
    writeMsg(dataH," ");
    readMsg(dataH);
    ukazKartyProtivnika(dataH.buffer);
    writeMsg(dataH," ");
//--------------------------- ukoncenie pripojenia na server ------------------------------------

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&canRead);

    close(sockfd);

    return 0;
}