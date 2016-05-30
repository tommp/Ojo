#include "errorlogger.h"

void errorlogger(const char *errormsg){
    time_t current = time(0);
    struct tm *date_raw = gmtime(&current);
    char *date = asctime(date_raw);

    char outputFilename[] = ERROR_FILE_NAME;

    printf("    Error: %s\n     Date: %s\n\n", errormsg, date );

    FILE *errorlog = fopen(outputFilename, "a+");
    if (errorlog != NULL) {
        fprintf(errorlog, "Date: %s Error: %s\n\n", date, errormsg);
        fclose(errorlog);
    }
    else{
        printf("Error opening external file: %s, no errorlog saved.\n", ERROR_FILE_NAME);
    }
}
