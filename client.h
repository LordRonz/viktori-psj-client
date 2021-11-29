#ifndef CLIENT_H
#define CLIENT_H

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <sys/types.h>
#include <unistd.h>     /* for close() */
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <stdint.h>
#include "serial_io.h"

#define RCVBUFSIZE 128   /* Size of receive buffer */
#define SENDBUFSIZE 128
#define NORMAL_MODE 0
#define TAIL_MODE 1

void run(int, char**);
void die_with_error(char *);  /* Error handling function */

#endif
