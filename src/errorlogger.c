#include "errorlogger.h"

void errorlogger(const char *errormsg){
    time_t current = time(0);
    struct tm *date_raw = gmtime(&current);
    char *date = asctime(date_raw);

    FILE *errorlog;
    char outputFilename[] = ERROR_FILE_NAME;

    printf("    Error: %s\n     Date: %s\n\n", errormsg, date );

    errorlog = fopen(outputFilename, "w");
    if (errorlog != NULL) {
        fprintf(errorlog, "Date: %s Error: %s\n\n", date, errormsg);
        fclose(errorlog);
    }
    else{
        printf("Error opening external file: %s, no errorlog saved.\n", ERROR_FILE_NAME);
    }
}
