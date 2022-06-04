//#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
//#include <iostream>
#include <poll.h>

#define	PORT		5555
#define	SERVER_NAME		"127.0.0.1"
#define BUFLEN			512

void	writeToClient(int fd, char *buffer);
int	readFromClient(int fd, char *buffer);

#include <vector>

int	main(void) {

	std::vector<> a;

	int	i, err, opt = 1;
	int	sock, new_sock;
	struct sockaddr_in	addr;
	struct sockaddr_in	client;
	char buf[BUFLEN];
	socklen_t	size;

	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Server: cannot create socket");
		exit(EXIT_FAILURE);
	}
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const void*)&opt, sizeof(opt));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((bind(sock, (struct sockaddr*)&addr, sizeof(addr))) < 0) {
		perror("Server: cannot bind socket");
		exit(EXIT_FAILURE);
	}
	if (listen(sock, 5) < 0) {
		perror("Server: listen queue failure");
		exit(EXIT_FAILURE);
	}

	pollfd	act_set[100];
	act_set[0].fd = sock;
	act_set[0].events = POLLIN;
	act_set[0].revents = 0;
	int	num_set = 1;

	while (1) {
		int ret = poll(act_set, num_set, -1);
		if (ret < 0) {
			perror("Server poll failure");
			exit(EXIT_FAILURE);
		}
		if (ret > 0) {
			for (int i = 0; i < num_set; i++) {
				if (act_set[i].revents & POLLIN) {
					printf("get POLLIN at fd %d\n", act_set[i].fd);
					act_set[i].revents &= ~POLLIN;
					if (i == 0) {
						size = sizeof(client);
						new_sock = accept(act_set[i].fd,
											(struct sockaddr*)&client, &size);
						printf("new client at port %u\n",
						 								ntohs(client.sin_port));
						if (num_set < 100) {
							act_set[num_set].fd = new_sock;
							act_set[num_set].events = POLLIN;
							act_set[num_set].revents = 0;
							num_set++;
						} else {
							printf("no more sockets for client\n");
							close(new_sock);
						}
					} else {
						err = readFromClient(act_set[i].fd, buf);
						printf("%d [%s] %p\n", err, buf, strstr(buf, "stop"));
						if (err < 0 || strstr(buf, "stop")) {
							printf("get stop\n");
							close(act_set[i].fd);
							if (i < num_set - 1) {
								act_set[i] = act_set[num_set - 1];
								num_set--;
								i--;
							}
						} else {
							printf("Hello");
							writeToClient(act_set[i].fd, buf);
						}
					}
				}
			}
		}
	}

}

void	writeToClient(int fd, char *buffer) {
	int	nbytes;
	unsigned char	*s;

	for (s = (unsigned char*)buffer; *s; s++)
		*s = toupper(*s);
	nbytes = write(fd, buffer, strlen(buffer) + 1);
	fprintf(stdout, "Write back: %s\nnbytes=%d\n", buffer, nbytes);

	if (nbytes < 0)
		perror("Server write failure");
}

int readFromClient(int fd, char *buffer) {
	int	nbytes;

	nbytes = read(fd, buffer, BUFLEN);
	if (nbytes < 0) {
		perror("Server: read failure");
		return -1;
	} else if (nbytes == 0) {
		return -1;
	} else {
		fprintf(stdout, "Server got message: %s\n", buffer);
		return 0;
	}
	return 0;
}

hello, world!
