// any code related to sorting the spreadsheet
#include <stdio.h>
#include "ordering.h"
#include <stdlib.h>
#include "data.h"
#include <string.h>

void sortByID() {
    qsort(students, student_count, sizeof(struct Student), compare_studentID);
}

void sortByLastName() {
    qsort(students, student_count, sizeof(struct Student), compare_lastName);
}

void sortByExamGrade() {
    qsort(students, student_count, sizeof(struct Student), compare_examGrade);
}

void sortByFinalGrade() {
    qsort(students, student_count, sizeof(struct Student), compare_finalGrade);
}

int compare_studentID(const void *a, const void *b) { // parameters are pointers to void and can point to any data type, necessary to use qsort
    const struct Student *studentA = (const struct Student *)a; // casting void pointers to struct student pointers
    const struct Student *studentB = (const struct Student *)b;

    if (studentA == NULL) return 1;
    if (studentB == NULL) return -1;

    if (studentA -> studentID < studentB -> studentID) return -1; // puts A before B
    if (studentA -> studentID > studentB -> studentID) return 1;  // B before A

    return 0;
}

int compare_lastName(const void *a, const void *b) { // parameters are pointers to void and can point to any data type, necessary to use qsort
    const struct Student *studentA = (const struct Student *)a; // casting void pointers to struct student pointers
    const struct Student *studentB = (const struct Student *)b;

    if (studentA == NULL) return 1;
    if (studentB == NULL) return -1;

    return strcmp(studentA -> lastName, studentB -> lastName); // compares alphabetical order of a and b

    return 0;
}

int compare_examGrade(const void *a, const void *b) { // parameters are pointers to void and can point to any data type, necessary to use qsort
    const struct Student *studentA = (const struct Student *)a; // casting void pointers to struct student pointers
    const struct Student *studentB = (const struct Student *)b;

    if (studentA == NULL) return 1;
    if (studentB == NULL) return -1;

    if (studentA -> exam_grade < studentB -> exam_grade) return 1; // puts B before A
    if (studentA -> exam_grade > studentB -> exam_grade) return -1;  // A before B

    return 0;
}

int compare_finalGrade(const void *a, const void *b) { // parameters are pointers to void and can point to any data type, necessary to use qsort
    const struct Student *studentA = (const struct Student *)a; // casting void pointers to struct student pointers
    const struct Student *studentB = (const struct Student *)b;

    if (studentA == NULL) return 1;
    if (studentB == NULL) return -1;

    if (studentA -> final_grade < studentB -> final_grade) return 1; // puts B before A
    if (studentA -> final_grade > studentB -> final_grade) return -1;  // A before B

    return 0;
}
