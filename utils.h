#include "includes.h"

// everytime server is started or restarted debug logs will be added
#define STARTUP_LOG_FILE "start_up_log.log"

// caller needs to call free
char* get_time();

// setup start banner for start of logs
void startup_log_header();

// setup end banner for start of logs
void startup_log_footer();

// write's startup logs
void write_startup_log(char* log_message);