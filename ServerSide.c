#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "admin_menu.c"  // Include the admin_menu.c file



// Define a structure to store user data
typedef struct {
    char username[256];
    char password[8];
    int role;
} UserData;

UserData users[4]; // Store user data for up to 4 users

// Function to read user data from the file and store it
void readUserData() {
    FILE *file = fopen("user_data.txt", "r");
    if (file == NULL) {
        perror("Error opening user_data.txt");
        exit(1);
    }

    int i = 0;
    while (fscanf(file, "%s %s %d", users[i].username, users[i].password, &users[i].role) == 3) {
        i++;
    }

    fclose(file);
}

// Function to authenticate a user
// Function to authenticate a user
int authenticateUser(const char* username, const char* password, int role) {
    FILE* file = fopen("user_data.txt", "r");
    if (file == NULL) {
        perror("Failed to open user_data.txt");
        exit(1);
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char stored_username[50], stored_password[50];
        int stored_role;
        if (sscanf(line, "%s %s %d", stored_username, stored_password, &stored_role) == 3) {
            printf("Stored Username: %s, Password: %s, Role: %d\n", stored_username, stored_password, stored_role);
            printf("Input Username: %s, Password: %s, Role: %d\n", username, password, role);
            if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
                fclose(file);
                printf("Authentication successful!\n");
                return 1; // Authentication successful
            }
        }
    }

    fclose(file);
    printf("Authentication failed\n");
    return 0; // Authentication failed
}


// Function to send authentication result to the client
void sendAuthenticationResult(int client, int result) {
    char acknowledgment[256];
    if (result) {
        char authMessage[] = "Authentication successful!";
        send(client, authMessage, sizeof(authMessage), 0);
        recv(client, acknowledgment, sizeof(acknowledgment), 0);
    } else {
        char authMessage[] = "Authentication failed. Please check your credentials.";
        send(client, authMessage, sizeof(authMessage), 0);
        recv(client, acknowledgment, sizeof(acknowledgment), 0);
    }
}

// Function to send prompts and messages to the client
void sendPrompts(int client) {
    char welcomeMessage[] = "...Welcome Back to Academia :: Course Registration...\nLogin Type \nEnter Your Choice (1.Admin, 2.Professor, 3. Student):";
    send(client, welcomeMessage, sizeof(welcomeMessage), 0);

    // Wait for an acknowledgment from the client before sending the second message
    char acknowledgment[256];
    recv(client, acknowledgment, sizeof(acknowledgment), 0);
    

}

// ... (Previous code)

// Function to handle a client connection
void* handleClient(void* clientSocket) {
    int client = *((int*)clientSocket);
    sendPrompts(client);

    int role;
    recv(client, &role, sizeof(role), 0);

    // Send an acknowledgment to the client
    char acknowledgment[256];
    send(client, acknowledgment, sizeof(acknowledgment), 0);

    if (role >= 1 && role <= 3) {
        char usernameMessage[] = "Enter username:";
        send(client, usernameMessage, sizeof(usernameMessage), 0);

        // Username part
        char username[256];
        recv(client, username, sizeof(username), 0);
        send(client, acknowledgment, sizeof(acknowledgment), 0);

        // Debug: Print username
        printf("Received Username: %s\n", username);

        // Password part
        char passwordMessage[] = "Enter Password (Must be at most 8 digits):";
        send(client, passwordMessage, sizeof(passwordMessage), 0);
        
        // ... (Previous code)

        // Receive password from the client
        char password[256];
        recv(client, password, sizeof(password), 0);

        // Authenticate the user
        int authResult = authenticateUser(username, password, role);
        
        // Send the authentication result to the client
        sendAuthenticationResult(client, authResult);
       
        // Send the admin menu to the client
        if (role == 1) {
                sendAdminMenu(client);
                int choice;
                recv(client, &choice, sizeof(choice), 0);
                handleAdminChoice(client, choice);  // Handle the choice made by the admin
            }
    } else {
        char errormessage[] = "Enter correct role ID!";
        send(client, errormessage, sizeof(errormessage), 0);
    }
    return NULL;
}

// ... (Remaining code)

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;
    pthread_t thread_id;

    // Create a socket
    serverSocket = socket(PF_INET, SOCK_STREAM, 0);

    // Configure the server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the address
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Listen for incoming connections
    listen(serverSocket, 10);

    printf("Server is listening...\n");

    while (1) {
        addr_size = sizeof(clientAddr);
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addr_size);
        int* newClient = (int*)malloc(1);
        *newClient = clientSocket;

        // Create a new thread to handle the client
        if (pthread_create(&thread_id, NULL, handleClient, (void*)newClient) != 0) {
            perror("Error creating thread");
            return 1;
        }
    }

    return 0;
}
