// faculty_menu.c
#include <stdio.h>
#include <stdlib.h>

void sendFacultyMenu(int clientSocket) {
    char facultyMenu[] = "...... Welcome to Faculty Menu ......\n1. View Offering Courses\n2. Add New Course\n3. Remove Course from Catalog\n4. Update Course Details\n5. Change Password\n6. Logout and Exit\nEnter Your Choice:";
    
    send(clientSocket, facultyMenu, sizeof(facultyMenu), 0);
}

void handleFacultyChoice(int clientSocket, int choice) {
    char buffer[256];
    
    switch (choice) {
        case 1:
            // Implement the functionality for "View Offering Courses" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to View Offering Courses. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 2:
            // Implement the functionality for "Add New Course" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Add New Course. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 3:
            // Implement the functionality for "Remove Course from Catalog" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Remove Course from Catalog. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 4:
            // Implement the functionality for "Update Course Details" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Update Course Details. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 5:
            // Implement the functionality for "Change Password" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Change Password. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 6:
            // Implement the functionality for "Logout and Exit" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Logout and Exit. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        default:
            snprintf(buffer, sizeof(buffer), "Invalid choice. Please select a valid option.");
            send(clientSocket, buffer, sizeof(buffer), 0);
    }
}

