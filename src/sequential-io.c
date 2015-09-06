#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <time.h>
#include <stdio.h>

static volatile int stop = 0;

void sigint(int signo) {
    stop = 1;
}

int main(int argc, char **argv)
{
	size_t size = atoi(argv[1]);
    int fd;
    ssize_t ret;
    long long total = 0;
    char *buf = malloc(size);
    time_t start = time(NULL);
    time_t end;

    signal(SIGINT, sigint);
    signal(SIGTERM, sigint);

	while (!stop) {
		fd = open(argv[2], O_RDONLY);
		do {
			ret = read(fd, buf, size);
            total += ret;
		} while (!stop && ret != 0);
		close(fd);
	}
    end = time(NULL);

    fprintf(stderr, "%lld MB in %d seconds -- %lld MB/sec\n",
        total >> 20,
        (int)(end - start),
        (total / (end - start)) >> 20);

    return 0;
}
