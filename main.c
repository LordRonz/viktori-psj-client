#include "client.h"

void sigint_handler(int sig) {
    puts("Terminated");
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    signal(SIGINT, sigint_handler);
    if ((argc < 3) || (argc > 4)) {  /* Test for correct number of arguments */
        fprintf(stderr, "Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n", argv[0]);
        return EXIT_FAILURE;
    }
    run(argc, argv);
    read_file(open_file());
}
