// admin_menu.c
#include <stdio.h>
#include <stdlib.h>
void sendAdminMenu(int clientSocket) {
    char adminMenu[] = "...... Welcome to Admin Menu......\n1. Add Student\n2. View Student Details\n3. Add Faculty\n4. View Faculty Details\n5. Activate Student\n6. Block Student\n7. Modify Student Details\n8. Modify Faculty Details\n9. Logout and Exit\n";
    
    send(clientSocket, adminMenu, sizeof(adminMenu), 0);
}


void handleAdminChoice(int clientSocket, int choice) {
    char buffer[256];
    
    switch (choice) {
        case 1:
            // Implement the functionality for "Add Student" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Add Student. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 2:
            // Implement the functionality for "View Student Details" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to View Student Details. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 3:
            // Implement the functionality for "Add Faculty" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Add Faculty. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 4:
            // Implement the functionality for "View Faculty Details" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to View Faculty Details. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 5:
            // Implement the functionality for "Activate Student" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Activate Student. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 6:
            // Implement the functionality for "Block Student" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Block Student. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 7:
            // Implement the functionality for "Modify Student Details" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Modify Student Details. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 8:
            // Implement the functionality for "Modify Faculty Details" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Modify Faculty Details. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 9:
            // Implement the functionality for "Logout and Exit" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Logout and Exit. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        default:
            snprintf(buffer, sizeof(buffer), "Invalid choice. Please select a valid option.");
            send(clientSocket, buffer, sizeof(buffer), 0);
    }
}


