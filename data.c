// read input file and extract field
#include <stdio.h>
#include "data.h"
#include <stdlib.h>
#include <string.h>

int current_size = INITIAL_SIZE; //original size of the array of students
int read = 0; // store the number of values we read from each line
int student_count = 0; // store number of students we read from the file
char line[70];
char *token;
struct Student *students = NULL;
int baseA = 80;
int baseB = 70;
int baseC = 60;
int baseD = 50;


void readStudents() {

    FILE *file;
    file = fopen(FILENAME, "r"); // "r" is to read the file

    if (file == NULL) {
        printf("Error opening the file");
        return;
    }

    students = (struct Student*) malloc (current_size * sizeof(struct Student));


    // make a loop to go through and read each line of the file and store into array

    while (fgets(line, 70, file) != NULL) { //read each line from file and store it in line until we reach the end of the file
        //line will be store as a string of 70 chars and we want to parse each token separated by "|" using strtok

        if (current_size <= student_count) {
            current_size += 10;
            students = (struct Student*) realloc (students, current_size * sizeof(struct Student));
        }
        
        token = strtok(line, "|"); //read until "|"
        students[student_count].studentID = atoi(token); // atoi converts string to integer

        token = strtok(NULL, "|");
        strncpy(students[student_count].lastName, token, 29); // since token is already a string, jsut copy (not convert) it (29 because max is 30)

        token = strtok(NULL, "|");
        strncpy(students[student_count].firstName, token, 29);

        token = strtok(NULL, "|");
        students[student_count].a1_grade = atof(token);

        token = strtok(NULL, "|");
        students[student_count].a2_grade = atof(token);

        token = strtok(NULL, "|");
        students[student_count].a3_grade = atof(token);

        token = strtok(NULL, "|");
        students[student_count].midterm_grade = atof(token);

        token = strtok(NULL, "|");
        students[student_count].exam_grade = atof(token);

        setFinalGrade(&students[student_count]);
        setLetterGrade(&students[student_count], 80, 70, 60, 50);
        student_count++;
    }

    if (ferror(file)) {
            printf("Error reading file.\n");
            return;
        }
    
    fclose(file);


    
    //printStudents(students); //dont forget to uncomment
    
}

void printStudents (struct Student students[]) {

    printf("\n%d students read.\n\n", student_count);

    for (int i = 0; i < student_count; i++) {
        printf("%d %s %s %d %d %d %d %d %f %c\n",
        students[i].studentID,
        students[i].lastName,
        students[i].firstName,
        students[i].a1_grade,
        students[i].a2_grade,
        students[i].a3_grade,
        students[i].midterm_grade,
        students[i].exam_grade,
        students[i].final_grade,
        students[i].letterGrade);
        printf("\n");
    }
}

void setFinalGrade (struct Student *student) {
    double assignments = (student -> a1_grade) + (student -> a2_grade) + (student -> a3_grade);
    double midterm = (student -> midterm_grade)/25.0;
    double exam = (student -> exam_grade)/40.0;
    double finalgrade = ((assignments/120) * 25) + (midterm * 25) + (exam * 50);
    student -> final_grade = finalgrade;                
}

void setLetterGrade (struct Student *student, int baseA, int baseB, int baseC, int baseD) {

    if (student -> final_grade >= baseA) {
        student -> letterGrade = 'A';
    } else if (student -> final_grade >= baseB) {
        student -> letterGrade = 'B';
    } else if (student -> final_grade >= baseC) {
        student -> letterGrade = 'C';
    } else if (student -> final_grade >= baseD) {
        student -> letterGrade = 'D';
    } else {
        student -> letterGrade = 'F';
    }
}


