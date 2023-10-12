#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

struct User {
    char username[50];
    char password[50];
    int role;
    int login_id;
};

// Function to authenticate the user using user data from file
int authenticate_user(const char* username, const char* password, int role, int* login_id) {
    FILE* file = fopen("user_data.txt", "r");
    if (file == NULL) {
        perror("Failed to open user_data.txt");
        exit(1);
    }

    char stored_username[50], stored_password[50];
    int stored_role, stored_login_id;

    while (fscanf(file, "%s %s %d %d", stored_username, stored_password, &stored_role, &stored_login_id) != EOF) {
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0 && role == stored_role) {
            *login_id = stored_login_id;
            fclose(file);
            return 1; // Authentication successful
        }
    }

    fclose(file);
    return 0; // Authentication failed
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Initialize server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // Port number
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the server socket to the specified address and port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Socket binding failed");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Listening failed");
        exit(1);
    }

    printf("Server is listening...\n");

    while (1) {
        // Accept incoming client connection
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("Connection accept failed");
            continue;
        }

        int role;
        int login_id;
        char username[50];
        char password[50];

        // Receive the role from the client
        recv(client_socket, &role, sizeof(int), 0);

        // Receive username and password from the client
        recv(client_socket, username, sizeof(username), 0);
        recv(client_socket, password, sizeof(password), 0);

        // Authenticate the user with the received role
        if (authenticate_user(username, password, role, &login_id)) {
            // Send the role back to the client
            send(client_socket, &role, sizeof(int), 0);

            // Redirect based on the role
            switch (role) {
                case 1:
                    // Admin module
                    printf("Admin with Login-ID: MT%d logged in.\n", login_id);
                    break;
                case 2:
                    // Professor module
                    printf("Professor with Login-ID: MT%d logged in.\n", login_id);
                    break;
                case 3:
                    // Student module
                    printf("Student with Login-ID: MT%d logged in.\n", login_id);
                    break;
                default:
                    printf("Unknown role for user '%s'.\n", username);
            }
        } else {
            // Authentication failed
            role = -1;
            send(client_socket, &role, sizeof(int), 0);
            printf("Authentication failed. Please check your username, password, and role.\n");
        }
        // Close the client socket
        close(client_socket);
    }

    // Close the server socket (this part may not be reached in practice)
    close(server_socket);

    return 0;
}
