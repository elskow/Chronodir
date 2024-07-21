#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>

void print_usage() {
    printf("Usage: ./cdir <directory name> [--format date_format] [--permissions mode]\n");
    printf("Options:\n");
    printf("  --format\tSpecify the date format. Default is '%%Y-%%m-%%d'.\n");
    printf("  --permissions\tSpecify the directory permissions in octal. Default is '0777'.\n");
    printf("  -h, --help\tShow this help message and exit.\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    char *format = "%Y-%m-%d";
    mode_t permissions = 0777;
    char *dirName = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage();
            return 0;
        } else if (strcmp(argv[i], "--format") == 0 && i + 2 < argc) { // Ensure there's an argument after --format
            format = argv[++i];
        } else if (strcmp(argv[i], "--permissions") == 0 && i + 2 < argc) { // Ensure there's an argument after --permissions
            permissions = strtol(argv[++i], NULL, 8);
        } else if (argv[i][0] != '-') {
            dirName = argv[i];
            break;
        }
    }

    if (dirName == NULL) {
        fprintf(stderr, "Error: Directory name is required.\n");
        return 1;
    }

    if (access(dirName, F_OK) != -1) {
        fprintf(stderr, "Error: Directory already exists.\n");
        return 1;
    }

    char dateStr[100];
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    if (tm == NULL || strftime(dateStr, sizeof(dateStr), format, tm) == 0) {
        fprintf(stderr, "Failed to format date\n");
        return 1;
    }

    int dirPathLength = snprintf(NULL, 0, "%s %s", dateStr, dirName) + 1;
    char *dirPath = malloc(dirPathLength);
    if (dirPath == NULL) {
        perror("Error allocating memory for directory path");
        return 1;
    }
    snprintf(dirPath, dirPathLength, "%s %s", dateStr, dirName);

    if (mkdir(dirPath, permissions) == -1) {
        perror("Error creating directory");
        free(dirPath);
        return 1;
    }

    printf("Directory created: %s\n", dirPath);
    free(dirPath);
    return 0;
}