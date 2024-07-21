#ifndef CDIR_H
#define CDIR_H

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <getopt.h>
#include <ctype.h>

void print_usage()
{
    printf("Usage: cdir [options] <directory name>\n");
    printf("Options:\n");
    printf("  -h, --help\t\t\tPrint this help message\n");
    printf("  -f, --format <format>\t\tSpecify the format of the date to be appended to the directory name\n");
    printf("  -p, --permissions <permissions>\tSpecify the permissions of the directory\n");
}

int is_valid_dirname(const char* dirname)
{
    if (dirname == NULL || *dirname == '\0')
    {
        return 0;
    }

    while (*dirname != '\0')
    {
        if (*dirname == '/' || *dirname == '\\' || *dirname == ':' || *dirname == '*' || *dirname == '?' || *dirname ==
            '"' || *dirname == '<' || *dirname == '>' || *dirname == '|')
        {
            return 0;
        }
        dirname++;
    }

    return 1;
}


#endif // CDIR_H
