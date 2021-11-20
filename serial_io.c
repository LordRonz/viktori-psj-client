#include "serial_io.h"

int open_serial() {
    int fd = open("/dev/ttyACM0", O_RDONLY);
    if (fd == -1) {
        perror("open_port: Unable to open /dev/ttyACM0 - ");
    }
    return fd;
}

int read_serial(int fd, char *s, int max_len) {
    unsigned char ichar;
    int i = 0, ifd;
    for (;i < max_len;) {
        ifd = read(fd, &ichar, 1);
        printf("This : %d\n", ichar);
        s[i++] = ichar;
        if (ichar == '\n') {
            printf("%s", s);
            break;
        }
    }
    s[i] = '\0';
    return i;
}
