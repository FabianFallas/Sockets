#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <strings.h>
#include <cstring>
#include <json-c/json.h>
#include <json-c/debug.h>
#include <json-c/json_object.h>

using namespace std;

#define PORT 3550
#define MAXDATASIZE 1000


int sendJSON(){
    char* str;
    int fd, numbytes;
    struct sockaddr_in client;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    char *hello = "Hola desde el cliente";
    char sendBuff[MAXDATASIZE];
    char recvBuff[MAXDATASIZE];

    struct hostent *he;

    if (fd < 0)
    {
        printf("Error : Could not create socket\n");
        return 1;
    }
    else
    {
        client.sin_family = AF_INET;
        client.sin_port = htons(PORT);
        client.sin_addr.s_addr = inet_addr("127.0.0.1"); //192.168.100.6
        memset(client.sin_zero, '\0', sizeof(client.sin_zero));
    }

    if (::connect(fd, (const struct sockaddr *)&client, sizeof(client)) < 0)
    {
        printf("ERROR connecting to server\n");
        return 1;
    }


    printf("Se ha conectado correctamente al servidor\n");

    send(fd, hello, MAXDATASIZE, 0);
    int valread = read(fd, recvBuff, 1024);
    printf("\nDesde el server: %s\n", recvBuff);

    ///Se limpian los Buffers
    memset(recvBuff, 0, MAXDATASIZE);
    memset(sendBuff, 0, MAXDATASIZE);

    ::close(fd);

}

int main() {
    std::cout << "Hello, World!" << std::endl;
    sendJSON();
}