#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    if (argc < 1) {
        printf("Too few arguments!");
        return 0;
    }
    const char *memblock;
    int fd;
    struct stat sb;

    fd = open(argv[1], O_RDONLY);
    fstat(fd, &sb);
    uint64_t filesize = sb.st_size;
    printf("Size: %lu\n", filesize);

    memblock = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);
    if (memblock == MAP_FAILED) {
        printf("oh no it failed\n");
        return 0;
    }
    uint64_t i;
    char result;
    for (i = 0; i < filesize; i++) {
        result += memblock[i];
    }
    printf("The answer is: %d\n", result);
    return 0;
}

