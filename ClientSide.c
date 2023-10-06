#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    // Create client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Initialize server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // Port number
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection to server failed");
        exit(1);
    }

    int role;

    // Prompt the user for their role
    printf("Welcome Back to Academia :: Course Registration\n");
    printf("Login Type\n");
    printf("Enter Your Choice (1.Admin, 2.Professor, 3. Student): ");
    scanf("%d", &role);
    send(client_socket, &role, sizeof(int), 0);

    char username[50];
    char password[50];

    // Prompt the user for their username and password
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    // Send username and password to the server
    send(client_socket, username, sizeof(username), 0);
    send(client_socket, password, sizeof(password), 0);

    // Receive the role from the server
    recv(client_socket, &role, sizeof(int), 0);

    // Check if authentication was successful
    if (role != -1) {
        switch (role) {
            case 1:
                // Admin menu options
                printf("Login Successful!\n");
                printf("Welcome, admin!\n");
                printf("Admin Menu:\n");
                // Add admin menu options here
                break;
            case 2:
                // Professor menu options
                printf("Login Successful!\n");
                printf("Welcome, professor!\n");
                printf("Professor Menu:\n");
                // Add professor menu options here
                break;
            case 3:
                // Student menu options
                printf("Login Successful!\n");
                printf("Welcome, student!\n");
                printf("Student Menu:\n");
                // Add student menu options here
                break;
            default:
                printf("Unknown role received from the server.\n");
        }
    } else {
        printf("Authentication failed. Please check your username and password.\n");
    }

    // Close the client socket
    close(client_socket);

    return 0;
}
