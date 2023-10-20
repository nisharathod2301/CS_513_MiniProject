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
    printf("Successfully connected to Server!\n");

    // Receive and display prompts from the server
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));

    // Receive welcome message from the server
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("%s", buffer);
    char acknowledgment[] = "Received";
    send(clientSocket, acknowledgment, sizeof(acknowledgment), 0);
    sleep(1);
    memset(buffer, 0, sizeof(buffer));  // Clear the buffer

    // Send role to the server
    int role;
    scanf("%d", &role);
    send(clientSocket, &role, sizeof(role), 0);
    memset(buffer, 0, sizeof(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("%s", buffer);
    sleep(1);

    // Receive "Enter username" prompt
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("%s", buffer);

    // Send username to the server
    char username[256];
    scanf("%s", username);
    send(clientSocket, username, sizeof(username), 0);
    memset(buffer, 0, sizeof(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("%s", buffer);

    // Receive "Enter password" prompt
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("%s", buffer);

    // Send password to the server
    char password[256];
    scanf("%s", password);
    send(clientSocket, password, sizeof(password), 0);

    // Receive authentication report
    memset(buffer, 0, sizeof(buffer)); // Added missing closing parenthesis
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("%s", buffer);
    send(clientSocket, acknowledgment, sizeof(acknowledgment), 0);
    sleep(1);

    // Receive and display the server's response (which is the menu)
    char menu[1024];  // Adjust the buffer size as needed
    recv(clientSocket, menu, sizeof(menu), 0);
    printf("%s", menu);


    int adminchoice;

    // Add Student
    printf("Enter Your Choice: ");
    scanf("%d", &adminchoice);

    // Send the user's choice to the server
    send(clientSocket, &adminchoice, sizeof(adminchoice), 0);

    char serverResponse[1024];  // Adjust the buffer size as needed
    recv(clientSocket, serverResponse, sizeof(serverResponse), 0);
    printf("%s\n", serverResponse);

    // Handle the "Add Student" case
    if (adminchoice == 1) {
//        // After receiving the prompt
//        recv(clientSocket, buffer, sizeof(buffer), 0);
//        printf("%s", buffer);

        // User enters the username and password separated by a space
        char username[256];
        memset(username, 0, sizeof(username));
        scanf("%s", username);
        printf("username %s \n", username);
        
        send(clientSocket, username, sizeof(username), 0);

        char password[256];
        memset(password, 0, sizeof(password));
        scanf("%s", password);
        printf("password %s \n", password);
        send(clientSocket, password, sizeof(password), 0);

        // After sending the student information, receive and display the server's response
        char serverResponse[1024];
        recv(clientSocket, serverResponse, sizeof(serverResponse), 0);
        printf("gygu %s\n", serverResponse);
        
        // student details
        for (int i=0; i<3; i++) {
            printf("in loop");
            memset(serverResponse, 0, sizeof(serverResponse));
            recv(clientSocket, serverResponse, sizeof(serverResponse), 0);
            printf("%s \n", serverResponse);
            
            memset(serverResponse, 0, sizeof(serverResponse));
            scanf("%s", serverResponse);
            send(clientSocket, serverResponse, sizeof(serverResponse), 0);
        }

    }

    // Close the client socket
    close(clientSocket);

    return 0;
}
