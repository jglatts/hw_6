/*

CIS 1057 Assignment 6
Author: John Glatts
TA: Shi Kai Fang
Due Date: 6 December 2018

=========================================
 Very Hacky
 Fix and practice file operations
 Add another file read in print_file()
 =========================================

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Function Prototypes */
void store_content(char []);
void option_menu(char [], char [][100], char[][100], int[], int);
void print_file(char [][100], char [][100], int [], int);
int add_name_grade(char [][100], char [][100], int []);
void print_average(char []);
void write_to_file(char [], char [][100], char [][100], int [], int);


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


/* tore all info found in file */
void store_content(char file_name[]) {
    FILE *fp;
    char first_name[30][100], last_name[30][100];
    int grades[100], idx=0, size=0;

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("%s does not exist\n", file_name);
        option_menu(file_name, first_name, last_name, grades, size);
    }
    else {
        while (fscanf(fp, "%s %s %d", first_name[0], last_name[0], &grades[0]) != EOF) {
            fscanf(fp, "%s %s %d", first_name[idx], last_name[idx], &grades[idx]);
            idx++;
            size++;
        }
        option_menu(file_name, first_name, last_name, grades, size);
    }
    fclose(fp);
}


/* Display menu and call appropriate functions */
void option_menu(char file_name[], char first_name[][100], char last_name[][100], int grades[], int size) {
    int check, loop_size;
    char new_first_name[30][100], new_last_name[30][100];
    int new_grades[100];

    do {
        printf("__________________________________________________\n");
        printf("\n\t\tOptions...");
        printf("\n__________________________________________________\n");
        printf("\n1. Print all names and grades");
        printf("\n2. Add new name and grade");
        printf("\n3. Print Average");
        printf("\n4. Save updated list");
        printf("\n5. Exit Program\n --> ");
        scanf("%d", &check);
        if (check == 1) {
            // add logic to update list after the save option is hit
            print_file(first_name, last_name, grades, size);
        }
        else if (check == 2) {
            loop_size = add_name_grade(new_first_name, new_last_name, new_grades);
        }
        else if (check == 3) {
            //print_average(file_name);
        }
        else if (check == 4) {
            write_to_file(file_name, new_first_name, new_last_name, new_grades, loop_size);
        }
    } while (check != 5);
    return;
    // save info and exit program

}


/* Print all names and grades, display error if file is empty */
void print_file(char first_name[][100], char last_name[][100], int grades[], int size) {
    int i;

    // not displaying all content
    if (grades[0] != NULL) {
        for (i = 0; i < size; ++i) {
            printf("\n%s %s %d\n", first_name[i], last_name[i], grades[i]);
        }
    }
    else {
        printf("\nEmpty File\n");
    }
}


/* Enter a new grade and name */
int add_name_grade(char new_first_name[][100], char new_last_name[][100], int new_grades[]) {
    int loop_size;

    printf("\n\nEnter number of new students\n--> ");
    scanf("%d", &loop_size);
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


/* Save the new info to the file */
void write_to_file(char file_name[], char new_first_name[][100], char new_last_name[][100], int new_grades[], int loop_size) {
    FILE *fp;

    // only works if file has previously existed
    fp = fopen(file_name, "w");
    for (int i = 0; i < loop_size; ++i) {
        fprintf(fp, "%s %s %d", new_first_name[i], new_last_name[i], new_grades[i]);
    }
    fclose(fp);
}
