#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student details
struct Student {
    int roll;
    char name[50];
    int age;
    float marks;
};

// Function Prototypes
void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void updateStudent();

int main() {
    int choice;

    while(1) {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Records\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Delete Student Record\n");
        printf("5. Update Student Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

/* ------------------- ADD STUDENT ------------------- */
void addStudent() {
    struct Student s;
    FILE *fp = fopen("student.dat", "ab");

    if(!fp) {
        printf("Error in opening file!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    getchar(); 
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';  

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Record Added Successfully!\n");
}

/* ------------------- DISPLAY ALL ------------------- */
void displayStudents() {
    struct Student s;
    FILE *fp = fopen("student.dat", "rb");

    if(!fp) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- All Student Records ---\n");
    while(fread(&s, sizeof(s), 1, fp)) {
        printf("\nRoll: %d\nName: %s\nAge: %d\nMarks: %.2f\n",
               s.roll, s.name, s.age, s.marks);
    }

    fclose(fp);
}

/* ------------------- SEARCH STUDENT ------------------- */
void searchStudent() {
    struct Student s;
    FILE *fp = fopen("student.dat", "rb");
    int roll, found = 0;

    if(!fp) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.roll == roll) {
            printf("\nRecord Found!\n");
            printf("Roll: %d\nName: %s\nAge: %d\nMarks: %.2f\n",
                   s.roll, s.name, s.age, s.marks);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Record Not Found!\n");

    fclose(fp);
}

/* ------------------- DELETE STUDENT ------------------- */
void deleteStudent() {
    struct Student s;
    FILE *fp = fopen("student.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    int roll, found = 0;

    if(!fp) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.roll == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("student.dat");
    rename("temp.dat", "student.dat");

    if(found)
        printf("Record Deleted Successfully!
