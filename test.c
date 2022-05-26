#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int server_fd;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("cannot create socket");
        return 0;
    }

    struct in_addr {
        unsigned long s_addr;   // load with inet_aton
    };

    struct sockaddr_in {
        __uint8_t       sin_len;
        sa_family_t     sin_family;
        in_port_t       sin_port;
        struct in_addr  sin_addr;
        char            sin_zero[8];
    };

    struct sockaddr_in address;
    const int PORT = 8080;  //  Where the clients can reach it

    /* htonl converts a long integer (e.g. address) to network representation */
    
    /* htons converts a short integer (e.g. port) to a network representation */

    memset((char *)&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);

    int bind(int socket, const struct sockaddr *address, socklen_t adress_len);

    if (bind(server_fd, (struct sockadrr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return 0;
    }

    int listen(int socket, int backlog);
    int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);

    if (listen(server_fd, 3) < 0) {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    int new_socket;
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("In accept");
        exit(EXIT_FAILURE);
    }

    char    buffer[1024] ={0};

    int valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    if (valread < 0) {
        printf("No bytes are there to read");
    }

    char *hello = "Hello from the server";  //  IMPORTANT! WE WILL GET TO IT
    write(new_socket, hello, strlen(hello));
    close(new_socket);
}
