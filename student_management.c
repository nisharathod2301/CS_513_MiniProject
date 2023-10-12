#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int generate_student_id() {
    FILE* student_data = fopen("student_data.txt", "r");
    if (student_data == NULL) {
        perror("Failed to open student_data.txt");
        exit(1);
    }

    int max_id = 0;
    char line[100];
    while (fgets(line, sizeof(line), student_data)) {
        int student_id;
        if (sscanf(line, "%d", &student_id) == 1) {
            if (student_id > max_id) {
                max_id = student_id;
            }
        }
    }

    fclose(student_data);

    // Increment the max student ID to generate a new one
    return max_id + 1;
}

void add_student(int client_socket) {
    // Receive student details from the client
    char age[10];
    char email[100];
    char address[100];
    recv(client_socket, age, sizeof(age), 0);
    recv(client_socket, email, sizeof(email), 0);
    recv(client_socket, address, sizeof(address), 0);

    // Handle student ID generation
    int student_id = generate_student_id();

    // Generate login ID (MT + student_id)
    char login_id[20];
    snprintf(login_id, sizeof(login_id), "MT%d", student_id);

    // Update user_data.txt with the new student's information
    FILE* user_data = fopen("user_data.txt", "a");
    fprintf(user_data, "%s %s %d %d\n", login_id, "auto_generated_password", 2, student_id);
    fclose(user_data);

    // Update student_data.txt with the new student's information
    FILE* student_data = fopen("student_data.txt", "a");
    fprintf(student_data, "%d %s %s %s\n", student_id, age, email, address);
    fclose(student_data);

    // Send the generated student ID and login ID back to the client
    send(client_socket, &student_id, sizeof(int), 0);
    send(client_socket, login_id, sizeof(login_id), 0);
}

