#include "init.h"

void log_message(char* message, int level) {
    switch(level) {
        case DEBUG: printf("[!] DEBUG => %s\n", message);
                    break;

        case INFO:  printf("[!] INFO => %s\n", message);
                    break;

        case WARN:  printf("[!] WARN => %s\n", message);
                    break;

        case ERROR: printf("[!] ERROR => %s\n", message);
                    break;

        default:    printf("[!] LOG-MESSAGE => %s\n", message);
                    break;
    }
}

int create_socket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock <= 0) {
        printf("[-] Error creating socket. Exitting\n");
        exit(EXIT_FAILURE);
    }
    char buffer[100];
    sprintf(buffer, "Socket created with %d as socket descriptor", sock);
    log_message(buffer, DEBUG);
    return sock;
}

struct sockaddr_in* create_sockaddr_in_struct(int flag) {
    struct sockaddr_in *server = (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in));
    
    if (server == NULL) {
        printf("[-] Error creating sockaddr_in structure. Exitting\n");
        exit(EXIT_FAILURE);
    }
    if(flag == 0) {
        server->sin_family = AF_INET;
        (server->sin_addr).s_addr = INADDR_ANY;
        server->sin_port = htons(8000);
    }
    return server;
}

void bind_socket(int socket_descriptor, struct sockaddr *server, socklen_t size) {
    int result = bind(socket_descriptor, server, size);
    if(result != 0) {
        log_message("Error binding socket. Exitting\n", ERROR);
        exit(EXIT_FAILURE);
    }
}

void listen_server(int socket_descriptor, int backlog) {
    int result = listen(socket_descriptor, backlog);
    if(result != 0) {
        log_message("Error listening on socket.\n", ERROR);
        exit(EXIT_FAILURE);
    }
}

int accept_connection(int socket_descriptor, struct sockaddr *client, socklen_t size) {
    int new_socket_descriptor = accept(socket_descriptor, client, &size);
    if(new_socket_descriptor <= 0) {
        log_message("Error accepting connection\n", ERROR);
        exit(EXIT_FAILURE);
    }
    return new_socket_descriptor;
}

int get_size_of_data(int socket_descriptor) {
    sleep(0.4);
    int size;
    int result = ioctl(socket_descriptor, FIONREAD, &size);
    char* buffer = (char*)malloc(50);
    sprintf(buffer, "Bytes to read from socket is %d\n", size);
    printf(buffer);
    free(buffer);
    return size;
}

void read_data(int socket_descriptor, char* buffer, int size) {
    int bytes_read = read(socket_descriptor, buffer, size);
}

void write_data(int socket_descriptor, char* buffer, int size) {
    int bytes_wrote = write(socket_descriptor, buffer, size);
}