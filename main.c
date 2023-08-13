#include "init.h"
#include "utils.h"

void setup() {
    int s = create_socket();
    char* buffer = (char*)malloc(50);
    memset(buffer, 0x0, 50);
    sprintf(buffer, "Socket Created With Descriptor: %d\n", s);
    write_startup_log(buffer);
    memset(buffer, 0x0, 50);
    struct sockaddr_in *server = create_sockaddr_in_struct(0);
    sprintf(buffer, "Struct sockaddr_in Initialized\n");
    write_startup_log(buffer);
    memset(buffer, 0x0, 50);
    bind_socket(s, (struct sockaddr*)&(*server), sizeof(struct sockaddr));
    sprintf(buffer, "Binding socket to all interfaces at port 8000\n");
    write_startup_log(buffer);
    memset(buffer, 0x0, 50);
    listen_server(s, 3);
    sprintf(buffer, "Listening on port 8000\n");
    write_startup_log(buffer);
    memset(buffer, 0x0, 50);
}

void loop() {
    printf("------------START------------\n");
    int s = create_socket();
    struct sockaddr_in *server = create_sockaddr_in_struct(0); // need to free
    bind_socket(s, (struct sockaddr*)&(*server), sizeof(struct sockaddr));
    listen_server(s, 3);
    struct sockaddr_in *client = create_sockaddr_in_struct(1); // need to free
    socklen_t client_size = sizeof(*client);
    int new_s = accept_connection(s, (struct sockaddr*)&(*client), client_size);
    int read_size = get_size_of_data(new_s);
    char* buffer = (char*) malloc(read_size);
    memset(buffer, 0x0, read_size);
    read_data(new_s, buffer, read_size);
    printf("Data Read: \n\n%s\n\n", buffer);
    // parse request
    char* sample_message = "Hello World, Data Received\n";
    write_data(new_s, sample_message, 27);
    printf("-------END--------\n");
    free(client);
    free(server);
    close(new_s);
    close(s);    
}

int main() {
    char* time = get_time();
    printf("time now: %s\n", time);
    free(time);
    return 0;
}