#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <time.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>

static volatile int stop = 0;

void sigint(int signo) {
    stop = 1;
}

int main(int argc, char **argv)
{
	size_t size = atoi(argv[1]);
    int fd;
    long long total = 0;
    time_t start = time(NULL);
    time_t end;
    struct stat s;
    char *buf;
    char *buf2 = malloc(size);
    long long offset;
    size_t map_end;
    volatile int i;

    signal(SIGINT, sigint);
    signal(SIGTERM, sigint);

    stat(argv[2], &s);
    srand(start);

    map_end = s.st_size & ~0xfff;

    fd = open(argv[2], O_RDONLY);
    buf = mmap(NULL, map_end, PROT_READ, MAP_SHARED, fd, 0);
    while(!stop) {
        offset = rand() % map_end;
        if (offset > map_end - size) {
            offset = map_end - size;
        }
        for (i = 0; i < size; i++) {
            buf2[i] = buf[i + offset];
        }
        total += size;
    }
    munmap(buf, map_end);
    close(fd);

    end = time(NULL);

    fprintf(stderr, "%lld MB in %d seconds -- %lld MB/sec\n",
        total >> 20,
        (int)(end - start),
        (total / (end - start)) >> 20);

    return 0;
}
