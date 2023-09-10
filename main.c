#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <arpa/inet.h>
#define DEBUG 1
#define INFO 2
#define WARN 3
#define ERROR 4
#define MAX_BUFFER_SIZE 65535
#define SO_REUSEPORT 15
#define PORT 8000

struct Request {
    int new_s;
    struct sockaddr_in *client;
};

void setup();
void *handle_request(void *args);
char* get_current_time();
char* get_request_type(char* line);

// returns current server time, caller needs to free once used
char* get_current_time() {
    time_t t = time(NULL);
    struct tm tm =*localtime(&t);
    char* buffer = (char*)malloc(25);
    sprintf(buffer, "%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return buffer;
}

// initial socket and struct setup
void setup() {
    // create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("Error creating socket.\n");
        exit(EXIT_FAILURE);
    }

    // set socket options REUSEADDR
    int reuse = 1;
    int set_socket_options_addr_result = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    if(set_socket_options_addr_result != 0) {
        perror("Error setting socket options for addr.\n");
        exit(EXIT_FAILURE);
    }

    // set socket options REUSEPORT
    int set_sock_options_port_result = setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));
    if(set_sock_options_port_result != 0) {
        perror("Error setting socket options for port.\n");
        exit(EXIT_FAILURE);
    }

    // create sockaddr_in struct
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // bind
    int bind_result = bind(sock, (struct sockaddr*)&server, sizeof(struct sockaddr));
    if(bind_result != 0) {
        perror("Error binding.\n");
        exit(EXIT_FAILURE);
    }

    // listen
    int listen_result = listen(sock, 10);
    if(listen_result != 0) {
        perror("Error listening.\n");
        exit(EXIT_FAILURE);
    }

    while(1) {
        // accept connections
        struct sockaddr_in *client = (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in)); // need to free
        socklen_t client_length = sizeof(*client);
        int new_socket = accept(sock, (struct sockaddr*)&(*client), &client_length);
        if(new_socket <= 0) {
            perror("Error accepting connections.\n");
            exit(EXIT_FAILURE);
        }

        // create struct to send to thread
        struct Request *req = (struct Request*) malloc(sizeof(struct Request)); // need to free
        if(req == NULL) {
            perror("Error creating req pointer.\n");
            exit(EXIT_FAILURE);
        }
        req->new_s = new_socket;
        req->client = client;

        // create thread and detach it
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_request, req);
        pthread_detach(thread_id);

        /*
        // get size of bytes from socket to read
        int bytes_to_read = 0;
        sleep(0.5);
        ioctl(new_socket, FIONREAD, &bytes_to_read);

        // create buffer of size bytes_to_read and read into it
        char* buffer = (char*)malloc(bytes_to_read);
        int bytes_read = read(new_socket, buffer, bytes_to_read);
        printf("bytes read: %d\n", bytes_read);
        printf("Received data: \n\n%s\n\n", buffer);
        free(buffer);

        // send response back
        char* message = "hello\n";
        sleep(10);
        write(new_socket, message, 6);
        close(new_socket);
        */
    }
}

// handles each request
void *handle_request(void *args) {
    // get client struct and new socket descriptor
    struct Request *request = (struct Request*) args;
    int new_socket = request->new_s;
    struct sockaddr_in *client = request->client;
    // get client information
    char* ip_addr = inet_ntoa(client->sin_addr);
    unsigned int port = ntohs(client->sin_port);
    printf("Connection Received from %s:%d\n", ip_addr, port);
    // get request size
    int request_size = 0;
    ioctl(new_socket, FIONREAD, &request_size);
    // create buffer for request size and read into it
    char* buffer = (char*)malloc(request_size); // need to free
    int bytes_read = read(new_socket, buffer, request_size);
    printf("bytes read: %d\n", bytes_read);
    printf("Data Received: \n\n%s\n\n", buffer);
    // send back some data
    char* message = "data received\n";
    sleep(10); // added sleep to check for multiple request handling
    write(new_socket, message, 14);
    free(buffer);
    free(client);
    close(new_socket);
    free(request);
    pthread_exit(0);
}

// returns http method type, caller needs to free once used
char* get_request_type(char* line) {
    char l[10] = { 0 };
    int i = 0;
    while(i<10) {
        l[i] = line[i];
        i++;
    }
    char** lines = (char*)malloc(sizeof(char*) * 10);
}

int main() {
    printf("%s", get_request_type("abcdefghijklmnopqrstuvwxyz"));
    return 0;
}