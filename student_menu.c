// student_menu.c
#include <stdio.h>
#include <stdlib.h>

void sendStudentMenu(int clientSocket) {
    char studentMenu[] = "...... Welcome to Student Menu .....\n1. Enroll to new Courses\n2. Unenroll from already enrolled Courses\n3. View enrolled Courses\n4. Password Change\n5. Exit\nEnter Your Choice:";
    
    send(clientSocket, studentMenu, sizeof(studentMenu), 0);
}

void handleStudentChoice(int clientSocket, int choice) {
    char buffer[256];
    
    switch (choice) {
        case 1:
            // Implement the functionality for "Enroll to new Courses" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Enroll to new Courses. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 2:
            // Implement the functionality for "Unenroll from already enrolled Courses" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Unenroll from already enrolled Courses. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 3:
            // Implement the functionality for "View enrolled Courses" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to View enrolled Courses. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 4:
            // Implement the functionality for "Password Change" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Password Change. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 5:
            // Implement the functionality for "Exit" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Exit. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        default:
            snprintf(buffer, sizeof(buffer), "Invalid choice. Please select a valid option.");
            send(clientSocket, buffer, sizeof(buffer), 0);
    }
}
