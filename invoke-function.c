#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

typedef int test_func(void);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        puts("Usage: runner <text section>");
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf("%s\n", strerror(errno));
        return 1;
    }
    struct stat buf;
    fstat(fd, &buf);
    off_t size = buf.st_size;
    void *exe = mmap(NULL, size, PROT_READ | PROT_EXEC, MAP_PRIVATE, fd, 0);
    if (exe == MAP_FAILED) {
        printf("mmap: %p %s\n", exe, strerror(errno));
        return 1;
    }
    close(fd);
    test_func *test = exe;
    printf("result: %d\n", test());
    return 0;
}
