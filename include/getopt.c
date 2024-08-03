#include "getopt.h"
#include <stdio.h>
#include <string.h>

char* optarg;
int optind = 1, opterr = 1, optopt;

static char* nextchar;

int getopt(int argc, char* const argv[], const char* optstring) {
    if (optind >= argc || argv[optind][0] != '-' || argv[optind][1] == '\0') {
        return -1;
    }

    if (argv[optind][1] == '-' && argv[optind][2] == '\0') {
        optind++;
        return -1;
    }

    if (!nextchar || *nextchar == '\0') {
        nextchar = argv[optind] + 1;
    }

    char c = *nextchar++;
    const char* temp = strchr(optstring, c);

    if (!temp) {
        if (opterr) {
            fprintf(stderr, "Unknown option `-%c'.\n", c);
        }
        optopt = c;
        return '?';
    }

    if (temp[1] == ':') {
        if (*nextchar != '\0') {
            optarg = nextchar;
            nextchar = NULL;
        }
        else if (++optind >= argc) {
            if (opterr) {
                fprintf(stderr, "Option `-%c' requires an argument.\n", c);
            }
            optopt = c;
            return ':';
        }
        else {
            optarg = argv[optind];
            nextchar = NULL;
        }
    }

    if (!nextchar || *nextchar == '\0') {
        optind++;
    }

    return c;
}


int getopt_long(int argc, char* const argv[], const char* optstring,
	const struct option* longopts, int* longindex) {
	return getopt(argc, argv, optstring);
}
