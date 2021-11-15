#include "client.h"

void run(int argc, char **argv) {
    int sock;                        /* Socket descriptor */
    struct sockaddr_in server_addr; /* Echo server address */
    char *echo_string;                /* String to send to echo server */
    char echo_buffer[RCVBUFSIZE];     /* Buffer for echo string */
    unsigned int echo_string_len;      /* Length of string to echo */
    int bytes_rcvd, total_bytes_rcvd;   /* Bytes read in single recv() 
                                        and total bytes read */
    struct addrinfo hints, *res;

    echo_string = argv[2];         /* Second arg: string to echo */

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM;

    {
        char *server_port = argc == 4 ? argv[3] : "7";  /* Third arg:  local port */
        char *server_ip = argv[1];      /* First arg: server IP address (dotted quad) */
        int status = getaddrinfo(server_ip, server_port, &hints, &res);
        if (status != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
            exit(EXIT_FAILURE);
        }
    }

    /* Create a reliable, stream socket using TCP */
    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock < 0) {
        die_with_error("socket() failed");
    }

    /* Establish the connection to the echo server */
    if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
        die_with_error("connect() failed");
    }

    echo_string_len = strlen(echo_string);     /* Determine input length */

    /* Send the string to the server */
    if (send(sock, echo_string, echo_string_len, 0) != echo_string_len) {
        die_with_error("send() sent a different number of bytes than expected");
    }

    /* Receive the same string back from the server */
    total_bytes_rcvd = 0;
    printf("Received: ");                /* Setup to print the echoed string */

    /* Receive up to the buffer size (minus 1 to leave space for
        a null terminator) bytes from the sender */
    bytes_rcvd = recv(sock, echo_buffer, RCVBUFSIZE - 1, 0);
    if (bytes_rcvd < 1) {
        die_with_error("recv() failed or connection closed prematurely");
    }
    total_bytes_rcvd += bytes_rcvd;   /* Keep tally of total bytes */
    echo_buffer[bytes_rcvd] = '\0';  /* Terminate the string! */
    printf("%s", echo_buffer);      /* Print the echo buffer */

    puts("");    /* Print a final linefeed */

    close(sock);
}

void die_with_error(char *error_message) {
    perror(error_message);
    exit(EXIT_FAILURE);
}
