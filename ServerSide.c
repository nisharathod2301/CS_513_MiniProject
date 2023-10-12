#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>



// Function to send prompts and messages to the client
// ... Other code ...

// Function to send prompts and messages to the client
void sendPrompts(int client) {
    char welcomeMessage[] = "...Welcome Back to Academia :: Course Registration...\nLogin Type \n Enter Your Choice (1.Admin, 2.Professor, 3. Student):";
    send(client, welcomeMessage, sizeof(welcomeMessage), 0);

    // Wait for an acknowledgment from the client before sending the second message
    char acknowledgment[256];
    recv(client, acknowledgment, sizeof(acknowledgment), 0);

}

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
            char usernameMessage[] = "Enter username: ";
            send(client, usernameMessage, sizeof(usernameMessage), 0);
    }
    else{
        char errormessage[] = "Enter correct role ID!";
        send(client, errormessage, sizeof(errormessage),0);
    }
    return NULL;
}

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
