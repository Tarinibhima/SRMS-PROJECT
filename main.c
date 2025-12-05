#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student {
    int roll;
    char name[50];
    float marks;
};

void pauseForUser() {
    printf("\nPress Enter to continue...");
    fflush(stdout);
    getchar(); // consume newline if any
    getchar();
}

void clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printHeader(const char *title) {
    clearConsole();
    printf("========================================\n");
    printf("            %s\n", title);
    printf("========================================\n\n");
}

// Create student.txt automatically if missing
void checkAndCreateStudentFile() {
    FILE *fp = fopen("student.txt", "a");
    if (!fp) {
        printf("Error creating student.txt!\n");
        return;
    }
    fclose(fp);
}

// ------------------ STUDENT FUNCTIONS --------------------

void addStudent() {
    FILE *fp = fopen("student.txt", "a");
    if (!fp) {
        printf("Error opening student file!\n");
        return;
    }

    struct student s;

    printf("Enter Roll: ");
    scanf("%d", &s.roll);
    printf("Enter Name (no spaces): ");
    scanf("%s", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    fclose(fp);

    printf("\nStudent Added Successfully!\n");
    pauseForUser();
}

void displayStudents() {
    FILE *fp = fopen("student.txt", "r");
    if (!fp) {
        printf("Error opening student file!\n");
        return;
    }

    struct student s;
    printf("\n===== STUDENT LIST =====\n");
    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        printf("%d  %s  %.2f\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
    pauseForUser();
}

void searchStudent() {
    FILE *fp = fopen("student.txt", "r");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    int r;
    printf("Enter Roll to search: ");
    scanf("%d", &r);

    struct student s;
    int found = 0;

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == r) {
            printf("\nFound: %d %s %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student Not Found!\n");
    }

    fclose(fp);
    pauseForUser();
}

void updateStudent() {
    FILE *fp = fopen("student.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    int r;
    printf("Enter Roll to update: ");
    scanf("%d", &r);

    struct student s;
    int found = 0;

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == r) {
            found = 1;
            printf("Current: %d %s %.2f\n", s.roll, s.name, s.marks);
            printf("Enter new Name (no spaces): ");
            scanf("%s", s.name);
            printf("Enter new Marks: ");
            scanf("%f", &s.marks);
        }
        fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    if (!found) {
        remove("temp.txt");
        printf("Student Not Found.\n");
    } else {
        remove("student.txt");
        rename("temp.txt", "student.txt");
        printf("Student Updated Successfully!\n");
    }
    pauseForUser();
}

void deleteStudent() {
    FILE *fp = fopen("student.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    int r;
    printf("Enter Roll to delete: ");
    scanf("%d", &r);

    struct student s;
    int found = 0;

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == r) {
            found = 1; // skip writing
        } else {
            fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
        }
    }

    fclose(fp);
    fclose(temp);

    if (!found) {
        remove("temp.txt");
        printf("Roll Not Found. No deletion.\n");
    } else {
        remove("student.txt");
        rename("temp.txt", "student.txt");
        printf("Student Deleted Successfully!\n");
    }
    pauseForUser();
}

// ------------------ LOGIN SYSTEM --------------------

int loginSystem(char currentrole[]) {
    char username[50], password[50];
    char fileUser[50], filePass[50], fileRole[50];

    printHeader("LOGIN");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    FILE *fp = fopen("credentials.txt", "r");
    if (!fp) {
        printf("credentials.txt NOT FOUND!\n");
        pauseForUser();
        return 0;
    }

    while (fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) == 3) {
        if (strcmp(username, fileUser) == 0 &&
            strcmp(password, filePass) == 0) {
            strcpy(currentrole, fileRole);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// ------------------ MENUS --------------------

void adminmenu() {
    printHeader("ADMIN MENU");
    printf("1. Add Student\n");
    printf("2. Display Students\n");
    printf("3. Search Student\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Logout\n");
}

void usermenu() {
    printHeader("USER MENU");
    printf("1. Display Students\n");
    printf("2. Search Student\n");
    printf("3. Logout\n");
}

void staffmenu() {
    printHeader("STAFF MENU");
    printf("1. Display Students\n");
    printf("2. Update Student\n");
    printf("3. Logout\n");
}

void studentmenu() {
    printHeader("STUDENT MENU");
    printf("1. Search My Record\n");
    printf("2. Logout\n");
}

void guestmenu() {
    printHeader("GUEST MENU");
    printf("1. Display Students\n");
    printf("2. Logout\n");
}

// ------------------ MAIN --------------------

int main() {

    checkAndCreateStudentFile(); // creates student.txt automatically

    char currentrole[50];
    int login = loginSystem(currentrole);

    if (!login) {
        printf("\nLogin Failed. Exiting...\n");
        return 0;
    }

    printf("\nLogin Successful! Role: %s\n", currentrole);
    pauseForUser();

    int choice;

    while (1) {
        if (strcmp(currentrole, "ADMIN") == 0) {
            adminmenu();
            printf("\nEnter Choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: addStudent(); break;
                case 2: displayStudents(); break;
                case 3: searchStudent(); break;
                case 4: updateStudent(); break;
                case 5: deleteStudent(); break;
                case 6: printf("Logging Out...\n"); return 0;
                default: printf("Invalid Choice!\n"); pauseForUser();
            }
        }

        else if (strcmp(currentrole, "USER") == 0) {
            usermenu();
            printf("\nEnter Choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: displayStudents(); break;
                case 2: searchStudent(); break;
                case 3: printf("Logging Out...\n"); return 0;
                default: printf("Invalid Choice!\n"); pauseForUser();
            }
        }

        else if (strcmp(currentrole, "STAFF") == 0 || strcmp(currentrole, "TEACHER") == 0) {
            staffmenu();
            printf("\nEnter Choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: displayStudents(); break;
                case 2: updateStudent(); break;
                case 3: printf("Logging Out...\n"); return 0;
                default: printf("Invalid Choice!\n"); pauseForUser();
            }
        }

        else if (strcmp(currentrole, "STUDENT") == 0) {
            studentmenu();
            printf("\nEnter Choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: searchStudent(); break;
                case 2: printf("Logging Out...\n"); return 0;
                default: printf("Invalid Choice!\n"); pauseForUser();
            }
        }

        else if (strcmp(currentrole, "GUEST") == 0) {
            guestmenu();
            printf("\nEnter Choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: displayStudents(); break;
                case 2: printf("Logging Out...\n"); return 0;
                default: printf("Invalid Choice!\n"); pauseForUser();
            }
        } else {
            printf("Unknown role: %s. Exiting.\n", currentrole);
            return 0;
        }
    }

    return 0;
}
