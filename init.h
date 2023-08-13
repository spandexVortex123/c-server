#include "includes.h"

// log messages
void log_message(char* message, int level);

// create socket and return socket descriptor
int create_socket();

// reutrns pointer to sockaddr_in structure after initializing
// need to free by the caller
struct sockaddr_in* create_sockaddr_in_struct(int flag);

// bind socket
void bind_socket(int socket_descriptor, struct sockaddr *server, socklen_t size);

// listen
void listen_server(int socket_descriptor, int backlog);

// accept
// accept's connection and returns the new socket descriptor
int accept_connection(int socket_descriptor, struct sockaddr *client, socklen_t size);

// get size of data that is send by socket
int get_size_of_data(int socket_descriptor);

// read/recv data from socket and store it in buffer
void read_data(int socket_descriptor, char* buffer, int size);

// write/send data back to connected socket from buffer
void write_data(int socket_descriptor, char* buffer, int size);