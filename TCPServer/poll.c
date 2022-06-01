#include <stdio.h>
#include <unistd.h>
#include <sys/poll.h>

#define TIMEOUT 5

int main() {
	struct pollfd fds[2];

	fds[0].fd = 0;
	fds[0].events = POLLIN;

	fds[1].fd = 1;
	fds[1].events = POLLOUT;

	while (1)
	{
		int ret = poll(fds, 1, TIMEOUT * 1000);
		if (!ret) {
			printf("TIMEOUT\n");
		} else {
				char str[256];
			if (fds[0].revents & POLLIN) {
				scanf("%s", str);
				printf("%s\n", str);
			}
			if (fds[1].revents & POLLOUT)
				printf("%s\nOutput is writeable\n", str);
		}
	}
	return 0;
}
