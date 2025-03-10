//main function and basic GUI
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "ordering.h"
#include "calc.h"

//void displayMenu();


int main() {

    readStudents();
    sortByID();
    displayMenu();
    
    return 0;
}