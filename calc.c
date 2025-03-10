//carry out the logic of the menu option
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "ordering.h"
#include <string.h>
#include "calc.h"

/*
1. Display spreadsheet
2. Display histogram
3. Set sort column
4. Update last name
5. Update exam grade
6. Update grade mapping
7. Delete student
8. Exit
*/

int selection;
char cont;

void displaySpreadsheet() {

    printf("COMP 348 GRADE SHEET\n\n");

    printf("%-6s %-20s %-20s %-4s %-4s %-4s %-9s %-9s %-9s %-9s", "ID", "Last",
                                        "First", "A1", "A2", "A3", "Midterm",
                                        "Exam", "Total", "Grade");

    printf("\n");
    
    printf("%-6s %-20s %-20s %-4s %-4s %-4s %-9s %-9s %-9s %-9s", "--", "----",
                                        "-----", "--", "--", "--", "-------",
                                        "----", "-----", "-----");

    
    printf("\n");


    for (int i = 0; i < student_count; i++) {
        printf("%-6d %-20s %-20s %-4d %-4d %-4d %-9d %-9d %-9.2f %-9c", students[i].studentID, 
                                        students[i].lastName,students[i].firstName, 
                                        students[i].a1_grade, students[i].a2_grade,
                                        students[i].a3_grade, students[i].midterm_grade,
                                        students[i].exam_grade, students[i].final_grade, 
                                        students[i].letterGrade);
        printf("\n");                                
    }
}

void pressContinue() {
    printf("\n");
    char input;

    printf("Press 'c' or 'C' to continue " );
    do {
        input = getchar();
    } while (input != 'c' && input != 'C');
}

void displayMenu() {
    system("clear");
    printf("Spreadsheet Menu\n"
    "----------------\n"
    "1. Display Spreadsheet\n"
    "2. Display Histogram\n"
    "3. Set sort column\n"
    "4. Update last name\n"
    "5. Update Exam Grade\n"
    "6. Update Grade Mapping\n"
    "7. Delete Student\n"
    "8. Exit\n\n");
    printf("Selection: ");
    scanf("%d", &selection);
    menuChoice();
}

void menuChoice() {
    switch(selection) {
        case 1:
            displaySpreadsheet();
            pressContinue();
            displayMenu();
            break;
        case 2:
            displayHistogram();
            pressContinue();
            displayMenu();
            break;
        case 3:
            setSortColumn();
            pressContinue();
            displayMenu();
            break;
        case 4:
            displaySpreadsheet();
            updateName();
            pressContinue();
            displayMenu();
            break;
        case 5:
            displaySpreadsheet();
            updateExamGrade();
            pressContinue();
            displayMenu();
            break;
        case 6:
            updateMapping();
            pressContinue();
            displayMenu();
            break;
        case 7:
            displaySpreadsheet();
            deleteStudent();
            pressContinue();
            displayMenu();
            break;
        case 8:
            free(students);
            printf("Goodbye and thanks for using our spreadsheet app.");
            break;
        default:
            displayMenu();    
    }
}

void setSortColumn() {
    int sort; 
    printf("Column Options\n");
    printf("--------------\n");
    printf("1. Student ID\n");
    printf("2. Last name\n");
    printf("3. Exam\n");
    printf("4. Total\n\n");
    printf("Sort Column: ");
    scanf("%d", &sort);
    printf("\n");

    switch(sort) {
        case 1:
            sortByID();
            printf("\nSort column updated\n");
            break;
        case 2:
            sortByLastName();
            printf("\nSort column updated\n");
            break;
        case 3:
            sortByExamGrade();
            printf("\nSort column updated\n");
            break;
        case 4: 
            sortByFinalGrade();
            printf("\nSort column updated\n");
            break;
        default:
            setSortColumn();    
    }

}

void updateName() {
    char name[29];
    int id;

    while (isStudentInArray(id) != 1) {
        printf("\n\nEnter Student ID: ");
        scanf("%d", &id);
    }
    printf("\n\nEnter updated Last Name: ");
    scanf("%s", name);

    for (int i = 0; i < student_count; i++) {
        if (students[i].studentID == id) {
            strncpy(students[i].lastName, name, 29);
        }
    }

    printf("\nLast name updated\n");
}

void updateExamGrade() {
    int grade;
    int id;
    while (isStudentInArray(id) != 1) {
        printf("\n\nEnter Student ID: ");
        scanf("%d", &id);
    }
    while (grade > 40 || grade < 0) {
        printf("\n\nEnter updated exam grade: ");
        scanf("%d", &grade);
    }

    for (int i = 0; i < student_count; i++) {
        if (students[i].studentID == id) {
            students[i].exam_grade = grade;
        }

        setFinalGrade(&students[i]);
    }

    printf("\nExam grade updated\n");
}

void updateMapping() {
    printf("Current Mapping:");
    printf("\n A: >= %d", baseA);
    printf("\n B: >= %d", baseB);
    printf("\n C: >= %d", baseC);
    printf("\n D: >= %d", baseD);
    printf("\n F: < %d", baseD);
    printf("\n\n\n");
    printf("Enter new A baseline: ");
    scanf("%d", &baseA);
    printf("\nEnter new B baseline: ");
    scanf("%d", &baseB);
    printf("\nEnter new C baseline: ");
    scanf("%d", &baseC);
    printf("\nEnter new D baseline: ");
    scanf("%d", &baseD);
    printf("\n\nNew Mapping:\n");
    printf(" A: >= %d", baseA);
    printf("\n B: >= %d", baseB);
    printf("\n C: >= %d", baseC);
    printf("\n D: >= %d", baseD);
    printf("\n F: < %d\n", baseD);

    for (int i = 0; i < student_count; i++) {
        setLetterGrade(&students[i], baseA, baseB, baseC, baseD);
    }
}

void deleteStudent() {
    int id;
    while (isStudentInArray(id) != 1) {
        printf("\n\nEnter Student ID: ");
        scanf("%d", &id);
    }
    int index;

    for (int i = 0; i < student_count; i++) {
        if (students[i].studentID == id) index = i;
    }

    for (int i = index; i < student_count - 1; i++) {
        students[i] = students[i+1];
    }

    student_count--;

    printf("\nStudent successfully deleted\n");
}

void displayHistogram() {

    int countA = 0;
    int countB = 0;
    int countC = 0;
    int countD = 0;
    int countF = 0;

    printf("COMP 348 Grade Distribution\n\n");

    for (int i = 0; i < student_count; i++) {
        switch(students[i].letterGrade) {
            case 'A':
                countA++;
                break;
            case 'B':
                countB++;
                break;
            case 'C':
                countC++;
                break;
            case 'D':
                countD++;
                break;
            case 'F':
                countF++;
                break;
        }
    }

    printf("A: ");
    for (int i = 0; i < countA; i++) {
        printf("*");
    }
    printf("\nB: ");
    for (int i = 0; i < countB; i++) {
        printf("*");
    }
    printf("\nC: ");
    for (int i = 0; i < countC; i++) {
        printf("*");
    }
    printf("\nD: ");
    for (int i = 0; i < countD; i++) {
        printf("*");
    }
    printf("\nF: ");
    for (int i = 0; i < countF; i++) {
        printf("*");
    }
    printf("\n");
}

int isStudentInArray(int studentID) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].studentID == studentID) return 1;
    }
    return 0;
}

