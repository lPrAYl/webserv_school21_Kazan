//  Server side C program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>  //  for addrinfo, AI_PASSIVE

#define PORT 8080

int main(int argc, char const *argv[]) {
    int     server_fd, new_socket;
    long    valread;
    struct  sockaddr_in address;

    int addrlen = sizeof(address);
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain \nContent-Length: 12\n\nHello world!";

    // ********** OLD WAY ********** 
    // address.sin_family = AF_INET;
    // address.sin_addr.s_addr = INADDR_ANY;
    // address.sin_port = htons(PORT);

    // memset(address.sin_zero, '\0', sizeof(address.sin_zero));

    // //  Creating socket file descriptor
    // if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    //     perror("In socket");
    //     exit(EXIT_FAILURE);
    // }


    // if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
    //     perror("In bind");
    //     exit(EXIT_FAILURE);
    // }

    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, "8080", &hints, &res);

     //  Creating socket file descriptor
    if ((server_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == 0) {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    int yes = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) { // for Address already in use
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    if (bind(server_fd, res->ai_addr, res->ai_addrlen) < 0) {    // or connect?
        perror("In bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while (1) {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        char buffer[30000] = {0};
        valread = read(new_socket, buffer, 30000);
        printf("%s\n", buffer);
        write(new_socket, hello, strlen(hello));
        printf("---------------Hello message sent---------------\n");
    }
    close(server_fd);
    return 0;
}