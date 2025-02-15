#include "cdir.h"

#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#define mkdir _mkdir
#define mode_t int
#define F_OK 0

#include "getopt.h" // Custom implementation of getopt.h for Windows

#else
#include <unistd.h>
#include <sys/stat.h>
#include <getopt.h>
#endif

static struct option long_options[] = {
    {"help", no_argument, NULL, 'h'},
    {"format", required_argument, NULL, 'f'},
#ifndef _WIN32
    {"permissions", required_argument, NULL, 'p'},
#endif
    {NULL, 0, NULL, 0}
};

typedef struct {
    char* format;
#ifndef _WIN32
    mode_t permissions;
#endif
    char* dirName;
} Options;

Options parse_options(int argc, char* argv[]);
char* format_date(const char* format);
void create_directory(const char* dirName, const char* format
#ifndef _WIN32
    , mode_t permissions
#endif
);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    Options opts = parse_options(argc, argv);

    if (access(opts.dirName, F_OK) != -1) {
        fprintf(stderr, "Error: Directory already exists.\n");
        free(opts.dirName);
        return 1;
    }

    create_directory(opts.dirName, opts.format
#ifndef _WIN32
        , opts.permissions
#endif
    );
    free(opts.dirName);
    return 0;
}

Options parse_options(int argc, char* argv[]) {
    Options opts = { .format = "%Y%m%d",
#ifndef _WIN32
    .permissions = 0777,
#endif
    .dirName = NULL };
    int opt, option_index = 0;
    char* end = NULL;
    while ((opt = getopt_long(argc, argv, "hf:p:", long_options, &option_index)) != -1) {
        switch (opt) {
        case 'h':
            print_usage();
            exit(EXIT_SUCCESS);
        case 'f':
            opts.format = optarg;
            break;
#ifndef _WIN32
        case 'p':
            opts.permissions = (mode_t)strtol(optarg, &end, 8);
            if (*end != '\0') {
                fprintf(stderr, "Invalid permissions format.\n");
                exit(EXIT_FAILURE);
            }
            break;
#endif
        case '?':
        default:
            print_usage();
            exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        size_t len = 0;
        for (int i = optind; i < argc; ++i) {
            len += strlen(argv[i]) + 1; // +1 for space or null terminator
        }
        opts.dirName = malloc(len);
        if (opts.dirName == NULL) {
            perror("Error allocating memory for directory name");
            exit(EXIT_FAILURE);
        }
        opts.dirName[0] = '\0'; // Ensure the string is null-terminated
        for (int i = optind; i < argc; ++i) {
            strcat(opts.dirName, argv[i]);
            if (i < argc - 1) {
                strcat(opts.dirName, " ");
            }
        }
    }
    else {
        fprintf(stderr, "Error: Directory name is required.\n");
        print_usage();
        exit(EXIT_FAILURE);
    }
    return opts;
}

char* format_date(const char* format) {
    char dateStr[100];
    time_t now = time(NULL);
    struct tm* tm = localtime(&now);
    if (tm == NULL || strftime(dateStr, sizeof(dateStr), format, tm) == 0) {
        fprintf(stderr, "Failed to format date\n");
        exit(EXIT_FAILURE);
    }
    char* formattedDate = strdup(dateStr);
    if (formattedDate == NULL) {
        perror("Error allocating memory for formatted date");
        exit(EXIT_FAILURE);
    }
    return formattedDate;
}

void create_directory(const char* dirName, const char* format
#ifndef _WIN32
    , mode_t permissions
#endif
) {
    if (!is_valid_dirname(dirName)) {
        fprintf(stderr, "Error: Invalid directory name.\n");
        exit(EXIT_FAILURE);
    }

    char* dateStr = format_date(format);
    char* lowerDirName = strdup(dirName);

    if (lowerDirName == NULL) {
        perror("Error allocating memory for directory name");
        free(dateStr);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; lowerDirName[i]; i++) {
        lowerDirName[i] = (char)tolower(lowerDirName[i]);
        if (lowerDirName[i] == ' ') {
            lowerDirName[i] = '-';
        }
    }

    int dirPathLength = snprintf(NULL, 0, "%s-%s", dateStr, lowerDirName) + 1;
    char* dirPath = (char*)malloc((size_t)dirPathLength);
    if (dirPath == NULL) {
        perror("Error allocating memory for directory path");
        free(lowerDirName);
        free(dateStr);
        exit(EXIT_FAILURE);
    }
    snprintf(dirPath, dirPathLength, "%s-%s", dateStr, lowerDirName);
    if (mkdir(dirPath
#ifndef _WIN32
        , permissions
#endif
    ) != 0) {
        perror("Error creating directory");
        free(dirPath);
        free(lowerDirName);
        free(dateStr);
        exit(EXIT_FAILURE);
    }
    printf("Directory created: %s\n", dirPath);
    free(dirPath);
    free(lowerDirName);
    free(dateStr);
}
