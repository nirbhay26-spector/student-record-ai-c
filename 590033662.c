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
float calcCGPA(const struct Student *s);
void displayAllCGPA(void);
void yearWiseAverage(void);
int compareNames(const char *a, const char *b);
void displaySortedBySap(void);
void displaySortedByName(void);
int weakestSemester(const struct Student *s);
void giveAdvice(const struct Student *s);
void academicAdvisor(void);

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

/* Function 3: CGPA = average of the SGPA values that are available (> 0) */
float calcCGPA(const struct Student *s) {
    float sum = 0;
    int n = 0, i;
    for (i = 0; i < NUM_SEM; i++) {
        if (s->sgpa[i] > 0) {
            sum = sum + s->sgpa[i];
            n++;
        }
    }
    if (n == 0) {
        return 0;
    }
    return sum / n;
}

/* Shows the CGPA of every student */
void displayAllCGPA(void) {
    int i;
    if (count == 0) {
        printf("No records available.\n");
        return;
    }
    printf("\n=== CGPA of Each Student ===\n");
    printf("%-12s %-20s %s\n", "SAP ID", "Name", "CGPA");
    printf("--------------------------------------------\n");
    for (i = 0; i < count; i++) {
        printf("%-12ld %-20s %.2f\n", students[i].sapId, students[i].name,
               calcCGPA(&students[i]));
    }
}

/* Function 4: average CGPA of the students of each year */
void yearWiseAverage(void) {
    int y, i, n;
    float sum;
    printf("\n=== Average CGPA Year-wise ===\n");
    for (y = 1; y <= 4; y++) {
        sum = 0;
        n = 0;
        for (i = 0; i < count; i++) {
            if (students[i].year == y && calcCGPA(&students[i]) > 0) {
                sum = sum + calcCGPA(&students[i]);
                n++;
            }
        }
        if (n == 0) {
            printf("Year %d : no students with CGPA available\n", y);
        } else {
            printf("Year %d : %.2f  (%d student(s))\n", y, sum / n, n);
        }
    }
}

/* Compares two names ignoring upper/lower case. Works like strcmp. */
int compareNames(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        char x = tolower((unsigned char)a[i]);
        char y = tolower((unsigned char)b[i]);
        if (x != y) {
            return x - y;
        }
        i++;
    }
    return (unsigned char)a[i] - (unsigned char)b[i];
}

/* Function 5: display records in increasing order of SAP ID (bubble sort) */
void displaySortedBySap(void) {
    struct Student temp[MAX_STUDENTS];
    struct Student swap;
    int i, j;

    if (count == 0) {
        printf("No records to display.\n");
        return;
    }
    for (i = 0; i < count; i++) {   /* sort a copy, keep the original order */
        temp[i] = students[i];
    }
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            if (temp[j].sapId > temp[j + 1].sapId) {
                swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }
    printf("\n=== Records sorted by SAP ID (increasing) ===\n");
    for (i = 0; i < count; i++) {
        printStudent(&temp[i]);
    }
    printf("--------------------------------------------------\n");
}

/* Function 6: display records in increasing (A to Z) order of Name */
void displaySortedByName(void) {
    struct Student temp[MAX_STUDENTS];
    struct Student swap;
    int i, j;

    if (count == 0) {
        printf("No records to display.\n");
        return;
    }
    for (i = 0; i < count; i++) {
        temp[i] = students[i];
    }
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            if (compareNames(temp[j].name, temp[j + 1].name) > 0) {
                swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }
    printf("\n=== Records sorted by Name (A to Z) ===\n");
    for (i = 0; i < count; i++) {
        printStudent(&temp[i]);
    }
    printf("--------------------------------------------------\n");
}

/* Returns the semester number (1-8) that has the lowest SGPA, 0 if none */
int weakestSemester(const struct Student *s) {
    int i, weakest = 0;
    float lowest = 11;
    for (i = 0; i < NUM_SEM; i++) {
        if (s->sgpa[i] > 0 && s->sgpa[i] < lowest) {
            lowest = s->sgpa[i];
            weakest = i + 1;
        }
    }
    return weakest;
}

/* Part B: AI-assisted academic advisor.
 * The four categories were designed with help from an AI tool (see
 * AI_USAGE_LOG.md) and then checked and adjusted by me.
 * The advice itself is decided here in C using if-else. */
void giveAdvice(const struct Student *s) {
    float cgpa = calcCGPA(s);
    int weak = weakestSemester(s);

    printf("%s (SAP %ld) | CGPA = %.2f\n", s->name, s->sapId, cgpa);

    if (cgpa == 0) {
        printf("  No SGPA available yet - advice cannot be given.\n");
    } else if (cgpa >= 8.5) {
        printf("  Category : Excellent Performance\n");
        printf("  Advice   : Excellent performance - maintain your current study pattern.\n");
    } else if (cgpa >= 7.0) {
        printf("  Category : Good Performance\n");
        printf("  Advice   : Good performance - keep revising regularly and aim for 8.5+.\n");
    } else if (cgpa >= 5.0) {
        printf("  Category : Needs Improvement\n");
        printf("  Advice   : Needs improvement - focus more on subjects with lower SGPA");
        printf(" (weakest: semester %d).\n", weak);
    } else {
        printf("  Category : Requires Immediate Attention\n");
        printf("  Advice   : Requires immediate attention - meet your faculty mentor and");
        printf(" make a study plan (weakest: semester %d).\n", weak);
    }
}

/* Menu option: advice for one student or for all students */
void academicAdvisor(void) {
    long sap;
    int pos, i;

    printf("\n--- AI-Assisted Academic Advisor ---\n");
    sap = readLong("Enter SAP ID (0 for all students): ", 0, 999999999L);
    if (sap == 0) {
        for (i = 0; i < count; i++) {
            giveAdvice(&students[i]);
        }
    } else {
        pos = findStudent(sap);
        if (pos == -1) {
            printf("No student found with SAP ID %ld.\n", sap);
        } else {
            giveAdvice(&students[pos]);
        }
    }
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
            case 5: displayAllCGPA(); break;
            case 6: yearWiseAverage(); break;
            case 7: displaySortedBySap(); break;
            case 8: displaySortedByName(); break;
            case 9: academicAdvisor(); break;
            case 0: printf("Thank you. Goodbye!\n"); break;
            default: printf("Option not available yet.\n");
        }
    } while (choice != 0);

    return 0;
}
