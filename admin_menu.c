// admin_menu.c
#include <stdio.h>
#include <stdlib.h>
void sendAdminMenu(int clientSocket) {
    char adminMenu[] = "...... Welcome to Admin Menu......\n1. Add Student\n2. View Student Details\n3. Add Faculty\n4. View Faculty Details\n5. Activate Student\n6. Block Student\n7. Modify Student Details\n8. Modify Faculty Details\n9. Logout and Exit\nEnter Your Choice:";
    
    send(clientSocket, adminMenu, sizeof(adminMenu), 0);
}


