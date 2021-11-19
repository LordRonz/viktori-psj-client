#include "serial_io.h"

int open_file() {
    int fd = open("/dev/ttyACM0", O_RDONLY);
    if (fd == -1) {
        perror("open_port: Unable to open /dev/ttyACM0 - ");
    }
    return fd;
}

int read_file(int fd) {
    unsigned char ichar;
    char s[100];
    int i = 0, ifd;
    for (;;) {
        ifd = read(fd, &ichar, 1);
        s[i++] = ichar;
        if (ichar == '\n') {
            s[i] = '\0';
            printf("%s", s);
            i = 0;
        }
    }
    close(fd);
}
