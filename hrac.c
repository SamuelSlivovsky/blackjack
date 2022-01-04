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

int hra(DATA_H *data){

    bzero(data->buffer,256);
    int n = read(data->sockfd, data->buffer, 255);
    if (n < 0)
    {
        perror("Error reading from socket");
        return 6;
    }
    printf("%s\n", data->buffer);

    printf("Vasa volba: ");
    bzero(data->buffer, 256);
    fgets(data->buffer, 255, stdin);
    n = write(data->sockfd, data->buffer, strlen(data->buffer));
    if (n < 0)
    {
        perror("Error writing to socket");
       return 5;
   }

}

int main(int argc, char *argv[])
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent* server;

    char buffer[256];

    if (argc < 3)
    {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        return 1;
    }

    server = gethostbyname(argv[1]); // z hostname si ziskame info o serveri
    if (server == NULL)
    {
        fprintf(stderr, "Error, no such host\n");
        return 2;
    }

    bzero((char*)&serv_addr, sizeof(serv_addr)); // vycistenie struktury
    serv_addr.sin_family = AF_INET;
    bcopy(
            (char*)server->h_addr,
            (char*)&serv_addr.sin_addr.s_addr,
            server->h_length
    );
    serv_addr.sin_port = htons(atoi(argv[2]));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return 3;
    }

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error connecting to socket");
        return 4;
    }

    //  uspesne pripojeny na server
    bzero(buffer, 256);
    int karty[5] = {0};
    int pocetKariet = 2;
    int skore = 0;
    //naplnenie struktur
    DATA_H dataH = {karty, &pocetKariet, &skore,buffer,sockfd};
   // hra(&dataH);

    bzero(buffer,256);
    n = read(sockfd, buffer, 255);
    if (n < 0)
    {
        perror("Error reading from socket");
        return 6;
    }
    printf("%s\n", buffer);

    printf("Vasa volba: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
    {
        perror("Error writing to socket");
        return 5;
    }

//    printf("Please enter a message: ");
//    bzero(buffer,256);
//    fgets(buffer, 255, stdin);
//
//    n = write(sockfd, buffer, strlen(buffer));
//    if (n < 0)
//    {
//        perror("Error writing to socket");
//        return 5;
//    }
//
//    bzero(buffer,256);
//    n = read(sockfd, buffer, 255);
//    if (n < 0)
//    {
//        perror("Error reading from socket");
//        return 6;
//    }
//
//    printf("%s\n",buffer);

    // ukoncenie pripojenia

    close(sockfd);

    return 0;
}