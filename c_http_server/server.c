#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define PORT 8080
#define BUFFER_SIZE 4096

void serve_file(int client_socket, const char *path) {
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "public%s", path);

    if (strcmp(path, "/") == 0) {
        strcpy(full_path, "public/index.html");
    }

    int file_fd = open(full_path, O_RDONLY);

    if (file_fd < 0) {
        char *not_found =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/plain\r\n\r\n"
            "404 Not Found";
        write(client_socket, not_found, strlen(not_found));
        return;
    }

    char header[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n\r\n";

    write(client_socket, header, strlen(header));

    char buffer[BUFFER_SIZE];
    int bytes;
    while ((bytes = read(file_fd, buffer, BUFFER_SIZE)) > 0) {
        write(client_socket, buffer, bytes);
    }

    close(file_fd);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 10);

    printf("Server running on http://localhost:%d\n", PORT);

    while (1) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

        memset(buffer, 0, BUFFER_SIZE);
        read(client_socket, buffer, BUFFER_SIZE);

        char method[16], path[256];
        sscanf(buffer, "%s %s", method, path);

        printf("Request: %s %s\n", method, path);

        if (strcmp(method, "GET") == 0) {
            serve_file(client_socket, path);
        } else {
            char *msg =
                "HTTP/1.1 405 Method Not Allowed\r\n"
                "Content-Type: text/plain\r\n\r\n"
                "Only GET supported";
            write(client_socket, msg, strlen(msg));
        }

        close(client_socket);
    }

    return 0;
}
