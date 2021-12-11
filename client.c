#include "client.h"

volatile bool exit_requested = false;

void run(int argc, char **argv) {
    int sock;                        /* Socket descriptor */
    struct sockaddr_in server_addr; /* Echo server address */
    char *echo_string;                /* String to send to echo server */
    char echo_buffer[RCVBUFSIZE];     /* Buffer for echo string */
    unsigned int echo_string_len;      /* Length of string to echo */
    int bytes_rcvd;   /* Bytes read in single recv()
                                        and total bytes read */
    struct addrinfo hints, *res;
    int serial_fd;
    int mode = NORMAL_MODE;
    char *n_tail = NULL;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM;

    {
        char *server_port = argc > 2 ? argv[2] : "7";  /* Third arg:  local port */
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

    mode = argc > 3 ? strcmp(argv[3], "tail") == 0 ? TAIL_MODE : NORMAL_MODE : NORMAL_MODE;

    n_tail = argc == 5 ? argv[4] : "";

    echo_string = malloc(sizeof (char) * SENDBUFSIZE);
    if (mode == NORMAL_MODE) {
        serial_fd = setup_serial_port();

        if (serial_fd == -1) {
            die_with_error("open_serial() failed");
        }
    }

    /* Establish the connection to the echo server */
    if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
        die_with_error("connect() failed");
    }

    freeaddrinfo(res);

    struct sigaction sact;
    time_t t;

    for(;!exit_requested;) {
        // Setup exit handler signal
        sigemptyset(&sact.sa_mask);
        sact.sa_flags = 0;
        sact.sa_handler = catcher;
        sigaction(SIGALRM, &sact, NULL);
        alarm(5);
        time(&t);

        memset(echo_string, 0, sizeof (char) * SENDBUFSIZE);
        if (mode == TAIL_MODE) {
            strcpy(echo_string, "");
            strcat(echo_string, "tail ");
            strcat(echo_string, n_tail);
            strcat(echo_string, "\n");
        } else {
            echo_string_len = read_serial(serial_fd, echo_string, SENDBUFSIZE);
        }

        echo_string_len = strlen(echo_string);     /* Determine input length */

        /* Send the string to the server */
        if (send(sock, echo_string, echo_string_len, 0) != echo_string_len) {
            die_with_error("send() sent a different number of bytes than expected");
        } else {
            printf("Sent: %s", echo_string);
        }

        memset(echo_buffer, 0, sizeof (char) * RCVBUFSIZE);

        printf("Received: ");                /* Setup to print the echoed string */

        /* Receive up to the buffer size (minus 1 to leave space for
            a null terminator) bytes from the sender */
        bytes_rcvd = recv(sock, echo_buffer, RCVBUFSIZE - 1, 0);
        if (bytes_rcvd < 1) {
            if (errno == EINTR) {
                continue;
            }
            die_with_error("recv() failed or connection closed prematurely");
        }

        echo_buffer[bytes_rcvd] = '\0';  /* Terminate the string! */
        printf("%s", echo_buffer);      /* Print the echo buffer */

        puts("");    /* Print a final linefeed */

        if (mode == TAIL_MODE) {
            break;
        }
    }

    free(echo_string);
    if (mode == NORMAL_MODE) {
        close(serial_fd);
    }
    close(sock);
}

void catcher(int sig) {

}

void die_with_error(char *error_message) {
    perror(error_message);
    exit(EXIT_FAILURE);
}
