#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

int main(int argc, char *argv[]) 
{
    openlog("writer", LOG_PID, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Invalid number of arguments: expected 2, got %d", argc - 1);
        fprintf(stderr, "Usage: %s <file> <string>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    const char *write_str = argv[2];

    FILE *f = fopen(file_path, "w");
    if (f == NULL) {
        syslog(LOG_ERR, "Failed to open file: %s", file_path);
        perror("fopen");
        return 1;
    }

    if (fprintf(f, "%s", write_str) < 0) {
        syslog(LOG_ERR, "Failed to write to file: %s", file_path);
        fclose(f);
        return 1;
    }

    fclose(f);

    syslog(LOG_DEBUG, "Writing %s to %s", write_str, file_path);

    closelog();
    return 0;
}
