#ifndef SERIAL_IO_H
#define SERIAL_IO_H

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

int setup_serial_port();
int open_serial();
int read_serial(int, char *, int);

#endif
