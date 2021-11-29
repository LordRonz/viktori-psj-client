#include "client.h"

void sigint_handler(int sig) {
    puts("Terminated");
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    signal(SIGINT, sigint_handler);
    if ((argc < 2) || (argc > 5)) {  /* Test for correct number of arguments */
        fprintf(stderr, "Usage: %s <Server IP> [<Echo Port>] [tail] [n tail]\n", argv[0]);
        return EXIT_FAILURE;
    }
    run(argc, argv);
}
