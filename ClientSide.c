#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Create a socket
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // Port number
    serverAddr.sin_addr.s_addr = inet_addr("172.16.144.112"); // Server IP address

    // Connect to the server
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    // Receive and display prompts from the server
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));

    // Receive welocme wala
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("%s", buffer);

    // Send an acknowledgment to the server
    char acknowledgment[] = "Received";
    send(clientSocket, acknowledgment, sizeof(acknowledgment), 0);

    // Wait for 1 second
    sleep(1);

    memset(buffer, 0, sizeof(buffer));  // Clear the buffer

// Prompt the user to enter an integer
    int role;
    scanf("%d", &role);

    // Send the integer to the server
    send(clientSocket, &role, sizeof(role), 0);

    // Receive and display the acknowledgment from the server
    memset(buffer, 0, sizeof(buffer));
    
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("%s", buffer);

    // Wait for 1 second
    sleep(1);
    //Recieve enter username propmt
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("%s", buffer);

    
    close(clientSocket);

    return 0;
}
