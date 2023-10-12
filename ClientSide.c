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
    printf("Sucessfully connected to Server!\n");
    // Receive and display prompts from the server
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));

    // Receive welocme wala thing from server
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("%s", buffer);
    char acknowledgment[] = "Received";
    send(clientSocket, acknowledgment, sizeof(acknowledgment), 0);
    sleep(1);
    memset(buffer, 0, sizeof(buffer));  // Clear the buffer
 
    //Send role to server
    int role;
    scanf("%d", &role);
    send(clientSocket, &role, sizeof(role), 0);
    memset(buffer, 0, sizeof(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("%s", buffer);
    sleep(1);
    
    //Recieve enter username propmt
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("%s", buffer);
    
    //Send username to server
    char username[256];
    scanf("%s", username);
    send(clientSocket, username, sizeof(username), 0);
    memset(buffer, 0, sizeof(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("%s", buffer);
    
    //Recieve enter password propmt
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("%s", buffer);

    
    // ... (Previous code)

    // ... (Previous code)

    // Send password to server
    char password[256];
    scanf("%s", password);
    send(clientSocket, password, sizeof(password), 0);

    // ... (Remaining code)

    // ... (Remaining code)

    
    //Recieve authentication report
    memset(buffer, 0, sizeof(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("%s", buffer);
    send(clientSocket, acknowledgment, sizeof(acknowledgment), 0);
    sleep(1);
    
    close(clientSocket);

    return 0;
}
