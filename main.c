/*

CIS 1057 Assignment 6
Author: John Glatts
TA: Shi Kai Fang
Due Date: 6 December 2018

=====================================
 Very Hacky
 Fix and practice file operations
=====================================

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Function Prototypes */
void option_menu(char []);
void print_file(char []);
void add_name_grade(char []);
void print_average(char []);


int main(int argc, char const *argv[])
{
    char file_name[50];
    char str_helper[] = ".txt";

    printf("__________________________________________________\n");
    printf("\n\tEnter a filename to use as a datafile");
    printf("\n__________________________________________________\n--> ");
    scanf("%s", &file_name);
    strcat(file_name, str_helper);
    option_menu(file_name);

    return 0;
}


/* Display menu and call appropriate functions */
void option_menu(char file_name[]) {
    int check;

    do {
        printf("__________________________________________________\n");
        printf("\n\t\tOptions...");
        printf("\n__________________________________________________\n");
        printf("\n1. Print all names and grades");
        printf("\n2. Add new name and grade");
        printf("\n3. Print Average");
        printf("\n4. Save updated list\n --> ");
        scanf("%d", &check);
        if (check == 1) {
            print_file(file_name);
        }
        else if (check == 2) {
            add_name_grade(file_name);
        }
        else if (check == 3) {
            //print_average(file_name);
        }
    } while (check != 4);
        return;
        // save info and exit program

}


/* Print all names and grades, display error if file is empty */
void print_file(char file_name[]) {
    FILE *fp;
    int c;
    char buff[255];

    fp = fopen(file_name, "r");
    if (fp != NULL) {
        printf("\n");
        while ((c = getc(fp)) != EOF)
            putchar(c);
        fclose(fp);
        printf("\n");
    }
    else {
        printf("\nEmpty File\n");
    }

}


/* Enter a new grade and name */
void add_name_grade(char file_name[]) {
    FILE *fp;
    int c, grade;
    // will have to be 2D array --> [50][100]
    char name[55];

    // add logic to enter more grades
    // check w/ prof if mode should be 'a' or 'w'
    fp = fopen(file_name, "a");
    printf("Enter  Name: ");
    scanf(" %[^\n]s", name);
    printf("Enter  Grade: ");
    scanf("%d", &grade);
    printf("\n");

    // Save data
    fprintf(fp, "\n%s\t%d\n", name, grade);
    fclose(fp);

}
