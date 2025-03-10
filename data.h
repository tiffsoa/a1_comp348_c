#ifndef DATA_H
#define DATA_H

#include <stdio.h>

#define FILENAME "students.txt"
#define INITIAL_SIZE 10



typedef struct Student {
    int studentID;
    char lastName[30];
    char firstName[30];
    int a1_grade;
    int a2_grade;
    int a3_grade;
    int midterm_grade;
    int exam_grade;
    float final_grade;
    char letterGrade;
} Student;

extern struct Student *students;
extern int student_count;
extern int baseA;
extern int baseB;
extern int baseC;
extern int baseD;

void readStudents();

void printStudents (struct Student students[]);

void setFinalGrade(struct Student *student);

void setLetterGrade (struct Student *student, int baseA, int baseB, int baseC, int baseD);

#endif 