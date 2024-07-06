#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9020
#define BUFFER_SIZE 1024
#define EOF_MARKER "<EOF>"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <server_ip>\n", argv[0]);
        return 1;
    }

    const char *files[] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"};
    int num_files = sizeof(files) / sizeof(files[0]);

    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT)
    };
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    for (int i = 0; i < num_files; i++) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Cannot create socket");
            continue;
        }

        if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            perror("Connect failed");
            close(sock);
            continue;
        }

        send(sock, files[i], strlen(files[i]), 0);

        char buffer[BUFFER_SIZE];
        int total_bytes = 0;
        printf("Received contents of %s:\n", files[i]);
        while (1) {
            int bytes_received = recv(sock, buffer, BUFFER_SIZE - 1, 0);
            if (bytes_received <= 0) break;
            buffer[bytes_received] = '\0';
            if (strstr(buffer, EOF_MARKER)) {
                *strstr(buffer, EOF_MARKER) = '\0';
                printf("%s", buffer);
                break;
            }
            printf("%s", buffer);
            total_bytes += bytes_received;
        }
        printf("\n");
        close(sock);
    }

    return 0;
}
