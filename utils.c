#include "utils.h"

char* get_time() {
    char *buffer = (char*)malloc(50);
    if(buffer == NULL) {
        printf("Error creating buffer. EXitting...\n");
        exit(EXIT_FAILURE);
    }
    memset(buffer, 0x0, 50);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return buffer;
}

void startup_log_header() {
    FILE *fptr;
    fptr = fopen(STARTUP_LOG_FILE, "w");
    char* time = get_time();
    fprintf(fptr, "--------------------SERVER START: %s--------------------\n", time);
    free(time);
    fclose(fptr);
}

void startup_log_footer() {
    FILE *fptr;
    fptr = fopen(STARTUP_LOG_FILE, "w");
    char* time = get_time();
    fprintf(fptr, "--------------------SERVER STOP: %s--------------------\n", time);
    free(time);
    fclose(fptr);
}

void write_startup_log(char *message) {
    FILE *fptr;
    fptr = fopen(STARTUP_LOG_FILE, "w");
    fprintf(fptr, "LOG =>\t\t%s\n", message);
    fclose(fptr);
}