#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/vm_sockets.h>
#include <stdlib.h>
#include <unistd.h>

void fatal(const char* msg) {
    perror(msg);
    exit(1);
}

void sendall(int sock, const char* buffer, size_t len) {
    while (len > 0) {
        ssize_t sent = send(sock, buffer, len, /*flags=*/0);
        if (sent == -1) {
            fatal("send failed.");
        }
        if (sent == 0) {
            puts("eof during send.");
            return;
        }
        buffer += sent;
        len -= sent;
    }
}

int main() {
    puts("server starting");
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket() failed: ");
        exit(1);
    }

    sockaddr_vm addr {
        .svm_family = AF_INET,
        .svm_reserved1 = 0,
        .svm_port = 8080,
        .svm_cid = -1u,
    };

    int result = bind(sock, (const sockaddr*)&addr, sizeof(sockaddr_vm));
    if (result == -1) {
        fatal("bind() failed: ");
    }

    result = listen(sock, 1);
    if (result == -1) {
        fatal("listen() failed: ");
    }
    puts("listening...");

    char buffer[1024];
    while (1) {
        puts("awaiting accept.");
        int client = accept(sock, nullptr, nullptr);
        if (client == -1) {
            fatal("accept failed: ");
        }
        ssize_t bytes = recv(client, buffer, 1023, 0);
        if (bytes == -1) {
            fatal("recv failed: ");
        }
        buffer[bytes] = 0;
        printf("recv: '%s'\n", buffer);

        sendall(client, buffer, bytes);
        close(client);
    }


    puts("done");
    return 0;
}
