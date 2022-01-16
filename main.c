/**
* write a program that manages a set of courses a student is taking. This
* program will introduce new keywords (struct, enum), and the handling of
* heap memory allocations.
*
* Completion time: 5 hours
*
* @author Brett Perry, Professor Acuna
* @version 1.16.22
*/

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
//MACROS: CONSTANTS
#define MAX_LEN 1024


////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES



////////////////////////////////////////////////////////////////////////////////
//GLOBAL VARIABLES




//place to store course information
struct CourseNode* course_collection = NULL;

////////////////////////////////////////////////////////////////////////////////
//FORWARD DECLARATIONS
void branching(char option);

//Have an enumeration type (called Subject) to represent subjects (SER, EGR, CSE, EEE).
enum {SER, EGR, CSE, EEE} Subject;


//Have a struct type (called CourseNode) to hold information about a course.
struct CourseNode {
    char Subject;
    int number;
    char teacher[MAX_LEN];
    int credits;

    struct CourseNode*  next;
};


//main entry point. Starts the program by displaying a welcome and beginning an
//input loop that displays a menu and processes user input. Pressing q quits.
int main() {
    char input_buffer;

    printf("\n\nWelcome to ASU Class Schedule\n");

    //TODO: stuff goes here...
    struct CourseNode* n = malloc(sizeof(struct CourseNode));
    n->Subject = "SER";
    printf("subject: %c", n->Subject);


    /*
    //menu and input loop
    do {
        printf("\nMenu Options\n");
        printf("------------------------------------------------------\n");
        printf("a: Add a class\n");
        printf("d: Drop a class\n");
        printf("s: Show your classes\n");
        printf("q: Quit\n");
        printf("\nTotal Credits: %d\n\n", TODO);
        printf("Please enter a choice ---> ");

        scanf(" %c", &input_buffer);

        branching(input_buffer);
    } while (input_buffer != 'q');

    //TODO: stuff goes here...
    */
    return 0;
}

//takes a character representing an inputs menu choice and calls the appropriate
//function to fulfill that choice. display an error message if the character is
//not recognized.
void branching(char option) {
    switch (option) {
        case 'a':
            //TODO
            break;

        case 'd':
            //TODO
            break;

        case 's':
            //TODO
            break;

        case 'q':
            // main loop will take care of this.
            break;

        default:
            printf("\nError: Invalid Input.  Please try again...");
            break;
    }
}

