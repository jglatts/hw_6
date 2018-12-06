/*
CIS 1057 Assignment 6
Author: John Glatts
TA: Shi Kai Fang
Due Date: 6 December 2018
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Function Prototypes */
void store_content(char []);
int option_menu(char [], char [][30], char[][30], int[], int);
void print_file(int [], char [][30], char [][30], int);
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
    int grades[100], idx=0, grade_size=0;

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("%s does not exist\n", file_name);
        grades[0] = -1; // flag for print_average()
    }
    else {
        // check for EOF
        while (!feof(fp)) {
            fscanf(fp, "%s %s %d", first_name[idx], last_name[idx], &grades[idx]);
            idx++;
        }
    }
    // get rid of these before final
    grade_size = (sizeof(grades) / sizeof(grades[0]));
    printf("Size of array: %d --- Idx: %d", grade_size, idx);
    option_menu(file_name, first_name, last_name, grades, idx);
    fclose(fp);
}


/* Display option menu and call appropriate helper functions */
int option_menu(char file_name[], char first_name[][30], char last_name[][30], int grades[], int size) {
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
            print_file(grades, first_name, last_name, size);
        }
        else if (check == 2) {
            loop_size = add_name_grade(new_first_name, new_last_name, new_grades);
        }
        else if (check == 3) {
            print_average(grades, size);
        }
        else if (check == 4) {
            write_to_file(file_name, new_first_name, new_last_name, new_grades, loop_size);
            store_content(file_name);
        }
    } while (check != 5);
            // sometimes jumps back in the loop
            printf("\n\nLeaving Program\nThank you for using!\n");
            return 1;
}


/* Print all names and grades, display message  if file is empty */
void print_file(int grades[], char first_name[][30], char last_name[][30], int size) {
    // check if file is empty
    if (size != 0) {
        printf("\n");
        for (int i = 0; i < size - 1; ++i) {
            // work on formatting before final
            printf("\n%5s %s  %3d", first_name[i], last_name[i], grades[i]);
        }
        printf("\n");
    }
    else {
        printf("\nEmpty File...\n");
        printf("\n");
    }
}


/* Enter a new grade and name.
 * Returns the number of new entries
 * */
int add_name_grade(char new_first_name[][30], char new_last_name[][30], int new_grades[]) {
    int loop_size;

    printf("\n\nEnter number of new students\n--> ");
    scanf("%d", &loop_size);
    if (loop_size <= 100) {
        for (int i = 0; i < loop_size; ++i) {
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
    // change to w?
    fp = fopen(file_name, "a");
    for (int i = 0; i < loop_size; ++i) {
        fprintf(fp, "%s %s %d\n", new_first_name[i], new_last_name[i], new_grades[i]);
    }
    fclose(fp);
}


/* Print the average grade of the values in file */
void print_average(int grades[], int size)  {
    int sum = 0;
    int avrg = 0;

    // check for the flag
    if (grades[0] != -1) {
        for (int i = 0; i < size - 1; ++i) {
            printf("\nIteration #%d -> %d", i, grades[i]);
            sum += grades[i];
            printf("\nCurrent Sum --> %d", sum);
        }
        printf("\n");
        avrg = sum / (size - 1);
        printf("\n\nAverage grade is: %d\n\n", avrg);
    }
    else {
        printf("\n\nNo grades to calculate...\n\n");
    }

}

