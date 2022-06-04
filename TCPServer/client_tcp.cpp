#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define SERVER_PORT 5555
#define SERVER_NAME "127.0.0.1" 
#define BUFLEN      512

int writeToServer(int fd);
int readFromServer(int fd);

int main(void) {
    int err;
    int sock;
    struct sockaddr_in  server_addr;
    struct hostent*     hostinfo;

    hostinfo = gethostbyname(SERVER_NAME);
    if (hostinfo == NULL) {
        fprintf(stderr, "Unknown host %s.\n", SERVER_NAME);
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) < 0) {
        printf("\nInvalid address/ Address not supported\n");
        return -1;
    }
    char    host[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET, &(server_addr.sin_addr), host, INET_ADDRSTRLEN);

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Client: socket was not created");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof server_addr) < 0) {
        perror("Client: connect failure");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Connection is ready\n");

    while (1) {
        if (writeToServer(sock) < 0)
            break ;
        if (readFromServer(sock) < 0)
            break ;
    }
    fprintf(stdout, "The end\n");

    close(sock);
    exit(EXIT_SUCCESS);
}

int writeToServer(int fd) {
    int     nbytes;
    char    buf[BUFLEN];

    fprintf(stdout, "Send to server > ");
    if (fgets(buf, BUFLEN, stdin) == NULL)
        printf("error\n");
    buf[strlen(buf) - 1] = 0;

    nbytes = write(fd, buf, strlen(buf) + 1);
    if (nbytes < 0) {
        perror("write"); 
        return -1;
    }
    if (strstr(buf, "stop"))
        return -1;
    return 0;
}

int readFromServer(int fd) {
    int     nbytes;
    char    buf[BUFLEN];

    nbytes = read(fd, buf, BUFLEN);
    if (nbytes < 0) {
        perror("read");
        return -1;
    } else if (nbytes == 0) {
        fprintf(stderr, "Client: no message\n");
    } else {
        fprintf(stdout, "Server's replay: %s\n", buf);
    }
    return 0;
}
