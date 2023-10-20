// admin_menu.c
#include <stdio.h>
#include <stdlib.h>
#include "server_functions.h"
#include "model/student.h"

void sendAdminMenu(int clientSocket) {
    char adminMenu[] = "...... Welcome to Admin Menu......\n1. Add Student\n2. View Student Details\n3. Add Faculty\n4. View Faculty Details\n6. Modify Student Details\n7. Modify Faculty Details\n9. Logout and Exit\n";
    
    send(clientSocket, adminMenu, sizeof(adminMenu), 0);
}


void handleAdminChoice(int clientSocket, int choice) {
    char buffer[256];
    
    switch (choice) {
        case 1:
            // Implement the functionality for "Add Student"
            snprintf(buffer, sizeof(buffer), "You chose to Add Student. Enter the student's username and password separated by a space:");

            // Send the prompt to the client
            send(clientSocket, buffer, sizeof(buffer), 0);

            // Receive the student's username and password from the client
            char username[256];
            recv(clientSocket, username, sizeof(username), 0);
            char password[256];

            recv(clientSocket, password, sizeof(password), 0);

            int studentRole = 3; // Assuming students have a role of 3

            addLoginDetails(username, password, studentRole);
            snprintf(buffer, sizeof(buffer), "Student added successfully.");

            // Send the result to the client
            send(clientSocket, buffer, sizeof(buffer), 0);
            
            struct Student student;
            strcpy(student.username, username);
            
            char read_buffer[256];
            
            memset(read_buffer, 0, sizeof(read_buffer));
            snprintf(buffer, sizeof(buffer), "Enter the name of student: ");
            send(clientSocket, buffer, sizeof(buffer), 0);
            recv(clientSocket, read_buffer, sizeof(read_buffer), 0);
            strcpy(student.name, read_buffer);

//            memset(read_buffer, 0, sizeof(read_buffer));
//            snprintf(buffer, sizeof(buffer), "Enter the age of the student:");
//            send(clientSocket, buffer, sizeof(buffer), 0);
//            recv(clientSocket, read_buffer, sizeof(read_buffer), 0);
//            student.age = atoi(read_buffer);
            
            memset(read_buffer, 0, sizeof(read_buffer));
            snprintf(buffer, sizeof(buffer), "Enter the email of student:");
            send(clientSocket, buffer, sizeof(buffer), 0);
            recv(clientSocket, read_buffer, sizeof(read_buffer), 0);
            strcpy(student.email, read_buffer);
            
            memset(read_buffer, 0, sizeof(read_buffer));
            snprintf(buffer, sizeof(buffer), "Enter the email of student:");
            send(clientSocket, buffer, sizeof(buffer), 0);
            recv(clientSocket, read_buffer, sizeof(read_buffer), 0);
            strcpy(student.email, read_buffer);
            
            printf("Student details: %s %s %d %s", student.username, student.name, student.age, student.email);
            
//            addStudentDetails(student);
            
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
            // Implement the functionality for "Modify Student Details" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Modify Student Details. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 6:
            // Implement the functionality for "Modify Faculty Details" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Modify Faculty Details. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        case 7:
            // Implement the functionality for "Logout and Exit" and send the result to the client
            snprintf(buffer, sizeof(buffer), "You chose to Logout and Exit. Implement this functionality on the server side.");
            send(clientSocket, buffer, sizeof(buffer), 0);
            break;
        default:
            snprintf(buffer, sizeof(buffer), "Invalid choice. Please select a valid option.");
            send(clientSocket, buffer, sizeof(buffer), 0);
    }
}

