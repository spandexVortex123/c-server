#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#define DEBUG 1
#define INFO 2
#define WARN 3
#define ERROR 4
#define MAX_BUFFER_SIZE 65535