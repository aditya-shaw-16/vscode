#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9020
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 5
#define EOF_MARKER "<EOF>"

void *handle_client(void *client_sock_ptr) {
    int client_sock = *((int*)client_sock_ptr);
    free(client_sock_ptr);

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';  // Ensure null termination

        printf("Client requested file: %s\n", buffer);
        FILE *file = fopen(buffer, "rb");
        if (!file) {
            perror("Error opening file");
            const char *errorMsg = "File not found\n";
            send(client_sock, errorMsg, strlen(errorMsg), 0);
        } else {
            char file_buffer[BUFFER_SIZE];
            int read_bytes;
            while ((read_bytes = fread(file_buffer, 1, BUFFER_SIZE, file)) > 0) {
                send(client_sock, file_buffer, read_bytes, 0);
            }
            send(client_sock, EOF_MARKER, strlen(EOF_MARKER), 0); // Send EOF marker
            fclose(file);
        }
    }
    close(client_sock);
    return NULL;
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr.s_addr = htonl(INADDR_ANY),
    };

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    listen(server_fd, MAX_CLIENTS);
    printf("Server listening on port %d\n", PORT);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int *new_sock = malloc(sizeof(int));
        *new_sock = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (*new_sock < 0) {
            perror("Accept failed");
            free(new_sock);
            continue;
        }

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, (void*)new_sock) != 0) {
            perror("Thread creation failed");
            free(new_sock);
        }
        pthread_detach(thread_id);
    }

    close(server_fd);
    return 0;
}


