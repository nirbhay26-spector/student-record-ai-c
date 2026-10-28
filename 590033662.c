/*
 * Project : AI-Assisted Student Record and Result Management System
 * Course  : PRC1001 - Programming in C (B.Tech CSE, Semester I), UPES
 * Author  : Nirbhay Chauhan (SAP ID: 590033662)
 *
 * A console-based, menu-driven program that keeps records of students,
 * calculates CGPA, sorts records, and gives simple academic advice.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define NUM_SEM 8

/* ---------- Data structure ---------- */
struct Student {
    long sapId;
    int rollNo;
    char name[50];
    char phone[15];
    char email[50];
    int year;               /* 1 to 4 */
    int semester;           /* 1 to 8 (current semester) */
    float sgpa[NUM_SEM];    /* SGPA of semesters 1..8, 0 = not available */
};

struct Student students[MAX_STUDENTS];
int count = 0;              /* number of students currently stored */

/* ---------- Function prototypes ---------- */
void readLine(char *buf, int size);
int readInt(const char *prompt, int min, int max);
long readLong(const char *prompt, long min, long max);
float readFloat(const char *prompt, float min, float max);
int isValidPhone(const char *p);
int isValidEmail(const char *e);
int findStudent(long sapId);
void loadSampleData(void);
void printStudent(const struct Student *s);
void addStudent(void);
void displayAll(void);
void searchStudent(void);
void deleteStudent(void);

/* ---------- Input helper functions ---------- */

/* Reads one line of text safely (no overflow) and removes the newline */
void readLine(char *buf, int size) {
    if (fgets(buf, size, stdin) == NULL) {
        printf("\nInput ended. Exiting program.\n");
        exit(0);
    }
    buf[strcspn(buf, "\n")] = '\0';
}

/* Keeps asking until the user enters an integer between min and max */
int readInt(const char *prompt, int min, int max) {
    char line[100];
    int value;
    while (1) {
        printf("%s", prompt);
        readLine(line, sizeof(line));
        if (sscanf(line, "%d", &value) == 1 && value >= min && value <= max) {
            return value;
        }
        printf("  Invalid input. Enter a whole number from %d to %d.\n", min, max);
    }
}

long readLong(const char *prompt, long min, long max) {
    char line[100];
    long value;
    while (1) {
        printf("%s", prompt);
        readLine(line, sizeof(line));
        if (sscanf(line, "%ld", &value) == 1 && value >= min && value <= max) {
            return value;
        }
        printf("  Invalid input. Enter a number from %ld to %ld.\n", min, max);
    }
}

float readFloat(const char *prompt, float min, float max) {
    char line[100];
    float value;
    while (1) {
        printf("%s", prompt);
        readLine(line, sizeof(line));
        if (sscanf(line, "%f", &value) == 1 && value >= min && value <= max) {
            return value;
        }
        printf("  Invalid input. Enter a number from %.1f to %.1f.\n", min, max);
    }
}

/* Phone number must be exactly 10 digits */
int isValidPhone(const char *p) {
    int i;
    if (strlen(p) != 10) {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (!isdigit((unsigned char)p[i])) {
            return 0;
        }
    }
    return 1;
}

/* Very simple email check: must contain '@' and '.' */
int isValidEmail(const char *e) {
    return (strlen(e) > 5 && strchr(e, '@') != NULL && strchr(e, '.') != NULL);
}

/* ---------- Basic record functions ---------- */

/* Returns the position of the student in the array, or -1 if not found */
int findStudent(long sapId) {
    int i;
    for (i = 0; i < count; i++) {
        if (students[i].sapId == sapId) {
            return i;
        }
    }
    return -1;
}

/* Loads 5 sample students so the program has data to work with */
void loadSampleData(void) {
    struct Student sample[5] = {
        {590010001L, 101, "Aarav Sharma", "9876543210", "aarav.sharma@stu.upes.ac.in",
         1, 2, {9.1, 8.9, 0, 0, 0, 0, 0, 0}},
        {590010002L, 102, "Diya Verma", "9812345678", "diya.verma@stu.upes.ac.in",
         1, 2, {7.2, 7.6, 0, 0, 0, 0, 0, 0}},
        {590010003L, 103, "Kabir Singh", "9898989898", "kabir.singh@stu.upes.ac.in",
         2, 3, {6.0, 5.5, 5.8, 0, 0, 0, 0, 0}},
        {590010004L, 104, "Meera Nair", "9123456780", "meera.nair@stu.upes.ac.in",
         3, 5, {4.5, 4.2, 4.8, 4.0, 4.6, 0, 0, 0}},
        {590010005L, 105, "Rohan Gupta", "9765432108", "rohan.gupta@stu.upes.ac.in",
         4, 7, {8.2, 8.5, 8.0, 8.8, 8.6, 8.4, 8.7, 0}}
    };
    int i;
    for (i = 0; i < 5; i++) {
        students[i] = sample[i];
    }
    count = 5;
}

/* Prints all details of one student */
void printStudent(const struct Student *s) {
    int i;
    printf("--------------------------------------------------\n");
    printf("SAP ID   : %ld\n", s->sapId);
    printf("Roll No. : %d\n", s->rollNo);
    printf("Name     : %s\n", s->name);
    printf("Phone    : %s\n", s->phone);
    printf("Email    : %s\n", s->email);
    printf("Year     : %d    Semester: %d\n", s->year, s->semester);
    printf("SGPA     : ");
    for (i = 0; i < NUM_SEM; i++) {
        if (s->sgpa[i] > 0) {
            printf("S%d=%.2f ", i + 1, s->sgpa[i]);
        } else {
            printf("S%d=-- ", i + 1);
        }
    }
    printf("\n");
}

/* Function 1: add a new student */
void addStudent(void) {
    struct Student s;
    char prompt[40];
    int i, ok;

    if (count >= MAX_STUDENTS) {
        printf("Record list is full. Cannot add more students.\n");
        return;
    }

    printf("\n--- Add New Student ---\n");
    s.sapId = readLong("SAP ID (9 digits): ", 100000000L, 999999999L);
    if (findStudent(s.sapId) != -1) {
        printf("A student with this SAP ID already exists. Not added.\n");
        return;
    }

    s.rollNo = readInt("Roll No.: ", 1, 99999);

    do {
        printf("Name: ");
        readLine(s.name, sizeof(s.name));
    } while (strlen(s.name) == 0);

    do {
        printf("Phone No. (10 digits): ");
        readLine(s.phone, sizeof(s.phone));
        ok = isValidPhone(s.phone);
        if (!ok) {
            printf("  Invalid phone number.\n");
        }
    } while (!ok);

    do {
        printf("Email ID: ");
        readLine(s.email, sizeof(s.email));
        ok = isValidEmail(s.email);
        if (!ok) {
            printf("  Invalid email ID.\n");
        }
    } while (!ok);

    s.year = readInt("Year (1-4): ", 1, 4);
    do {
        s.semester = readInt("Semester (1-8): ", 1, 8);
        ok = ((s.semester + 1) / 2 == s.year);
        if (!ok) {
            printf("  Semester %d does not belong to year %d. Try again.\n",
                   s.semester, s.year);
        }
    } while (!ok);

    printf("Enter SGPA of each semester (enter 0 if not available yet):\n");
    for (i = 0; i < NUM_SEM; i++) {
        sprintf(prompt, "  Semester %d SGPA: ", i + 1);
        s.sgpa[i] = readFloat(prompt, 0, 10);
    }

    students[count] = s;
    count++;
    printf("Student added successfully.\n");
}

/* Function: display the records of all students */
void displayAll(void) {
    int i;
    if (count == 0) {
        printf("No records to display.\n");
        return;
    }
    printf("\n=== All Student Records (%d) ===\n", count);
    for (i = 0; i < count; i++) {
        printStudent(&students[i]);
    }
    printf("--------------------------------------------------\n");
}

/* Function 2: search a student by SAP ID and display the record */
void searchStudent(void) {
    long sap;
    int pos;
    printf("\n--- Search Student ---\n");
    sap = readLong("Enter SAP ID to search: ", 100000000L, 999999999L);
    pos = findStudent(sap);
    if (pos == -1) {
        printf("No student found with SAP ID %ld.\n", sap);
    } else {
        printStudent(&students[pos]);
        printf("--------------------------------------------------\n");
    }
}

/* Function: delete one student record using SAP ID */
void deleteStudent(void) {
    long sap;
    int pos, i;
    char answer[10];

    printf("\n--- Delete Student ---\n");
    sap = readLong("Enter SAP ID to delete: ", 100000000L, 999999999L);
    pos = findStudent(sap);
    if (pos == -1) {
        printf("No student found with SAP ID %ld.\n", sap);
        return;
    }

    printf("Are you sure you want to delete %s? (y/n): ", students[pos].name);
    readLine(answer, sizeof(answer));
    if (answer[0] != 'y' && answer[0] != 'Y') {
        printf("Deletion cancelled.\n");
        return;
    }

    /* shift all records after pos one place to the left */
    for (i = pos; i < count - 1; i++) {
        students[i] = students[i + 1];
    }
    count--;
    printf("Record deleted successfully.\n");
}

/* ---------- Main program ---------- */
int main(void) {
    int choice;

    loadSampleData();
    printf("=====================================================\n");
    printf("  Student Record and Result Management System\n");
    printf("=====================================================\n");

    do {
        printf("\n------------------- MENU -------------------\n");
        printf(" 1. Add a student\n");
        printf(" 2. Display all students\n");
        printf(" 3. Search a student by SAP ID\n");
        printf(" 4. Delete a student\n");
        printf(" 5. CGPA of each student\n");
        printf(" 6. Average CGPA of each year\n");
        printf(" 7. Display students sorted by SAP ID\n");
        printf(" 8. Display students sorted by Name\n");
        printf(" 9. Academic advisor (advice from CGPA)\n");
        printf(" 0. Exit\n");
        choice = readInt("Enter your choice: ", 0, 9);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                printf("Feature under development.\n");
                break;
            case 0: printf("Thank you. Goodbye!\n"); break;
            default: printf("Option not available yet.\n");
        }
    } while (choice != 0);

    return 0;
}
