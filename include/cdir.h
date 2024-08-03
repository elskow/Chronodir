#ifndef CDIR_H
#define CDIR_H

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#define mkdir _mkdir
#else
#define _XOPEN_SOURCE 700
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



void print_usage(void) {
    printf("Usage: cdir [options] <directory_name>\n");
    printf("Options:\n");
    printf("  -h, --help            Show this help message and exit\n");
    printf("  -f, --format FORMAT   Specify the date format (default: %%Y%%m%%d)\n");
#ifndef _WIN32
    printf("  -p, --permissions PERMISSIONS   Specify the directory permissions (default: 0777)\n");
#endif
}

int is_valid_dirname(const char* dirname)
{
    if (dirname == NULL || *dirname == '\0')
    {
        return 0;
    }

    while (*dirname != '\0')
    {
        if (*dirname == '/' || *dirname == '\\' || *dirname == ':' || *dirname == '*' || *dirname == '?' || *dirname == '"' || *dirname == '<' || *dirname == '>' || *dirname == '|')
        {
            return 0;
        }
        dirname++;
    }

    return 1;
}

#endif // CDIR_H
