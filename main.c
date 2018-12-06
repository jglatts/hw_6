/*

CIS 1057 Assignment 6
Author: John Glatts
TA: Shi Kai Fang
Due Date: 6 December 2018

 ===========================================================
 - Fix and practice file operations
 - Add another file read in print_file()
 - Correct the grades[index] that is causing problems
 ===========================================================

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Function Prototypes */
void store_content(char []);
void option_menu(char [], char [][30], char[][30], int[], int);
void print_file(char []);
int add_name_grade(char [][30], char [][30], int []);
void print_average(int [], int);
void write_to_file(char [], char [][30], char [][30], int [], int);


int main(int argc, char const *argv[])
{
    char file_name[50];
    char str_helper[] = ".txt";

    printf("__________________________________________________\n");
    printf("\n\tEnter a filename to use as a datafile");
    printf("\n__________________________________________________\n--> ");
    scanf("%s", &file_name);
    strcat(file_name, str_helper);
    store_content(file_name);

    return 0;
}


/* Store all info found in file */
void store_content(char file_name[]) {
    FILE *fp;
    char first_name[100][30], last_name[100][30];
    char eof_check;
    int grades[100], idx=0, grade_size=0;

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("%s does not exist\n", file_name);
    }
    else {
        // check for EOF
        while (!feof(fp)) {
            fscanf(fp, "%s %s %d", first_name[idx], last_name[idx], &grades[idx]);
            idx++;
        }
    }
    grade_size = (sizeof(grades) / sizeof(grades[0]));
    printf("Size of array: %d --- Idx: %d", grade_size, idx);
    for (int i = 0; i < idx - 1; ++i) {
        printf("\n%d\n", grades[i]);
    }
    option_menu(file_name, first_name, last_name, grades, idx);
    fclose(fp);
}


/* Display menu and call appropriate functions */
void option_menu(char file_name[], char first_name[][30], char last_name[][30], int grades[], int size) {
    int check, loop_size;
    char new_first_name[100][30], new_last_name[100][30];
    int new_grades[100];

    do {
        printf("\n");
        printf("***************************\n");
        printf("\tOptions");
        printf("\n***************************");
        printf("\n1. Print all names and grades");
        printf("\n2. Add new name and grade");
        printf("\n3. Print Average");
        printf("\n4. Save updated list");
        printf("\n5. Exit Program\n --> ");
        scanf("%d", &check);
        if (check == 1) {
            print_file(file_name);
        }
        else if (check == 2) {
            // change back to void
            loop_size = add_name_grade(new_first_name, new_last_name, new_grades);
        }
        else if (check == 3) {
            print_average(grades, size);
        }
        else if (check == 4) {
            // add function() to update info
            // add printf() that displays it's being saved
            write_to_file(file_name, new_first_name, new_last_name, new_grades, loop_size);
            store_content(file_name);
        }
    } while (check != 5);
            printf("\n\nLeaving Program\nThank you for using!\n");
}


/* Print all names and grades, display error if file is empty */
void print_file(char file_name[]) {
    FILE *fp;

    fp = fopen(file_name, "r");
    if (fp != NULL) {
        char fname[30], lname[30];
        int grade;
        printf("\n\n");
        while (fscanf(fp, "%s %s %d", fname, lname, &grade) != EOF) {
            printf("%s %s --> %d\n", fname, lname, grade);
        }
    }
    else {
        printf("\nEmpty File...\n");
    }
}


/* Enter a new grade and name */
int add_name_grade(char new_first_name[][30], char new_last_name[][30], int new_grades[]) {
    int loop_size;

    printf("\n\nEnter number of new students\n--> ");
    scanf("%d", &loop_size);
    if (loop_size <= 100) {
        for (int i = 0; i < loop_size; ++i) {
            // easier to write to file
            printf("\nEnter student first name\n --> ");
            scanf("%s", new_first_name[i]);
            printf("\nEnter student last name\n --> ");
            scanf("%s", new_last_name[i]);
            printf("\nEnter grade for %s\n --> ", new_first_name[i]);
            scanf("%d", &new_grades[i]);
        }
        return loop_size;
    }
    else {
        printf("\n\nThis program can only store 100 students\n\n");
        return 0;
    }
}


/* Save the new info to the file */
void write_to_file(char file_name[], char new_first_name[][30], char new_last_name[][30], int new_grades[], int loop_size) {
    FILE *fp;

    // only works if file has previously existed
    fp = fopen(file_name, "a");
    for (int i = 0; i < loop_size; ++i) {
        // change formating to add a newline at end
        fprintf(fp, "%s %s %d\n", new_first_name[i], new_last_name[i], new_grades[i]);
    }
    fclose(fp);
}


/* Print the average grade of the values in file */
void print_average(int grades[], int size)  {
    int sum = 0;
    int avrg = 0;

    // not iterating, get correct size
    for (int i = 0; i < size - 1; ++i) {
        printf("\nIteration #%d -> %d", i, grades[i]);
        sum += grades[i];
        printf("\nCurrent Sum --> %d", sum);
    }
    printf("\n");
    avrg = sum / (size - 1);
    printf("\n\nAverage grade is: %d\n\n", avrg);
}

