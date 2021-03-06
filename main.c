/**
* write a program that manages a set of courses a student is taking. This
* program will introduce new keywords (struct, enum), and the handling of
* heap memory allocations.
*
* Completion time: 24 hours
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
int total_credits;
struct FILE;

//place to store course information
struct CourseNode* head = NULL; //course_collection
////////////////////////////////////////////////////////////////////////////////
//FORWARD DECLARATIONS
void branching(char option);


//Have an enumeration type (called Subject) to represent subjects (SER, EGR, CSE, EEE).
typedef enum Subject {SER=4, EGR=3, CSE=1, EEE=2} Subject;
char *getSubjectName(Subject subject);

//Have a struct type (called CourseNode) to hold information about a course.
struct CourseNode {
    Subject subject;
    int number;
    char teacher[MAX_LEN];
    int credits;

    struct CourseNode* next;
};

//Create a function that adds courses to the collection and keeps it
//sorted by the course number. Populated each course with subject,
// number,teacher name, and credit hours. Prevents duplicate courses
// from being created.
void course_insert(struct CourseNode *new_node) {

    struct CourseNode* current_node = NULL;
    //insert a new_node into the course linked list at proper location
    //find the location of where it needs to go

    //insert at head
    if (head == NULL) {
        new_node->next = NULL;
        head = new_node;
    }
    //if you insert before head
    else if ((head->subject > new_node->subject) ||
            (head->subject == new_node->subject && head->number >= new_node->number)) {
        new_node->next = head;
        head = new_node;
    //find where to insert
    } else {
        current_node = head;
        while (current_node->next != NULL) {
            //insert between nodes
            if ((current_node->next->subject > new_node->subject) ||
                    (current_node->next->subject == new_node->subject && current_node->next->number >= new_node->number)) {
                    new_node->next = current_node->next;
                    current_node->next = new_node;
                    total_credits += 3;
                    return;
            } else {
                current_node = current_node->next;
            }
        }
        //if we get to the end then insert at the end
        current_node->next = new_node;
        new_node->next = NULL;
    }
    total_credits += 3;
}



//Display the contents of the CourseCollection list with
//format Subject Number Credits Teacher.
void schedule_print(struct CourseNode* node) {
    printf("\n\nClass Schedule\n");
    struct CourseNode *iter = node;
    while (iter != NULL) {
        printf("course: %s%d\tteacher: %s\tcredits: %d\n",
               getSubjectName(iter->subject), iter->number, iter->teacher, iter->credits);
        iter = iter->next;
    }
    printf("\n\n");
}

int getSubjectNum(char* str) {
    if (!strcmp(str, "CSE\n")) return 1;
    if (!strcmp(str, "EEE\n")) return 2;
    if (!strcmp(str, "EGR\n")) return 3;
    if (!strcmp(str, "SER\n")) return 4;
    else {
        printf("error blah blah blah\n");
        exit(1);
    }
}

char *getSubjectName(Subject subject) {
    switch(subject) {
        case (CSE):
            return "CSE";
        case (EEE):
            return "EEE";
        case (EGR):
            return "EGR";
        case (SER):
            return "SER";
        default:
            printf("ERROR: your selection was not in the scope.");
            exit(1);
    }
}

//Function prompts the user for a course, removes it from the collection,
//and keeps the collection sorted.

void *course_drop(struct CourseNode *node) {
    int num;
    Subject subj;
    printf("Select the course you want to drop.");
    printf("First, select the subject.\n");
    printf("Press 1 CSE, Press 2 for EEE, Press 3 for EGR, Press 4 for SER\n");
    printf("user input --> ");
    scanf("%d", &subj);
    printf("\nEnter the 3 digit course number\n");
    printf("user input --> ");
    scanf("%d", &num);

    //iterate through course_collection until you find exact match
    struct CourseNode* prev = NULL;
    struct CourseNode* iter = node;

    //if list is empty
    if(iter == NULL) {
        printf("ERROR: You're not enrolled in any classes.");
        return NULL;
    } else {
        //iterate through list
        while(iter->subject != subj && iter->number != num) {
            //if match is last node
            if(iter->next == NULL) {
                printf("ERROR: You are not enrolled in the class you selected.");
                return NULL;
            } else {
                //store iter to current node
                prev = iter;
                //move to next node
                iter = iter->next;
                total_credits -= 3;
                printf("Course %s%d is dropped.\n", getSubjectName(subj), num);
            }
        }


        //if match, update the node
        if(iter == head) {
            //change first to point to next node
            head = head->next;
            total_credits -= 3;
            printf("Course %s%d is dropped.\n", getSubjectName(subj), num);
        } else {
            //bypass the current node
            prev->next = iter->next;
            total_credits -= 3;
            printf("Course %s%d is dropped.\n", getSubjectName(subj), num);
        }
        return iter;
    }
}

//Function checks if a data file exists, and load any courses that
//it specifies.
void schedule_load(char filename[]) {

    char *s, *n, *t, *c;
    int i = 0, num = 0;
    const int BUFF_SIZE = 25;
    FILE *fp;
    char buff[BUFF_SIZE];


    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "\nNo file to open.\n");
    }
    else {
        for (char c = getc(fp); c!=EOF; c = getc(fp)) {
            if (c == '\n') {
                num += 1;
            }
        }
        num -= 1;
        num /= 4;
        fclose(fp);
    }    

    fp = fopen(filename, "r");
    
    struct CourseNode *current, *node;
        while (fgets(buff, BUFF_SIZE, fp) != NULL) {
            for (int i = 0; i < num; i++) {
        node = malloc(sizeof(struct CourseNode)); 
                s = fgets(buff, BUFF_SIZE, fp);
                node->subject = getSubjectNum(s);
                n = fgets(buff, BUFF_SIZE, (FILE *) fp);
                node->number = atoi(n);
                t = fgets(buff, BUFF_SIZE, (FILE *) fp);
                strcpy(node->teacher, t);
                c = fgets(buff, BUFF_SIZE, (FILE *) fp);
                node->credits = atoi(c);
                if(node->credits == 3) {total_credits += 3;}
        if (i == 0) {
            head = node;
            current = head;
        }
        else { // subsequent nodes
            current->next = node;
            current = node;
        }
            }

        }
        printf("\nCourse Schedule file loaded.\n");
        fclose(fp);
    }

void schedule_save() {
    FILE *fp;
    fp = fopen("schedule.txt", "w");

    //saves content of course_collection to plain text file
    fprintf(fp, "\n", NULL);
    while (head != NULL) {
        fprintf(fp, "%s\n", getSubjectName(head->subject));
        fprintf(fp, "%d\n", head->number);
        fprintf(fp, "%s", head->teacher);
    int len = strlen(head->teacher);
    if (head->teacher[len-1] != '\n') fprintf(fp, "\n");
        fprintf(fp, "%d\n", head->credits);
        head = head->next;
    }

    //if filename exists then override
    printf("Course Schedule file has been saved.\n\n");
    fclose(fp);
}



//main entry point. Starts the program by displaying a welcome and beginning an
//input loop that displays a menu and processes user input. Pressing q quits.
int main() {
    char input_buffer;
    //head = malloc(sizeof(struct CourseNode));
    printf("\n\nWelcome to ASU Class Schedule\n");

    //TODO: stuff goes here...
    schedule_load("schedule.txt");

    //menu and input loop
    do {
        printf("------------------------------------------------------\n");
        printf("Menu Options\n");
        printf("------------------------------------------------------\n");
        printf("a: Add a class\n");
        printf("d: Drop a class\n");
        printf("s: Show your classes\n");
        printf("q: Quit\n");
        printf("\nTotal Credits: %d\n", total_credits);
        printf("------------------------------------------------------\n");
        printf("Please enter a choice ---> ");


        scanf(" %c", &input_buffer);

        branching(input_buffer);
    } while (input_buffer != 'q');

    //TODO: stuff goes here...
    //moved schedule_save() to switch statement in branching

    return 0;
}

//takes a character representing an inputs menu choice and calls the appropriate
//function to fulfill that choice. display an error message if the character is
//not recognized.
void branching(char option) {
    
    switch (option) {
        case 'a':
            //get info from user
            printf("Press 1 CSE, Press 2 for EEE, Press 3 for EGR, Press 4 for SER\n");
            struct CourseNode *temp = malloc(sizeof(struct CourseNode));
            printf("user input --> ");
            scanf("%d", &temp->subject);
            printf("\nEnter the 3 digit course number\n");
            printf("user input --> ");
            scanf("%d", &temp->number);
            printf("\nEnter the professor name\n");
            printf("user input --> ");
            scanf("%s", temp->teacher);
            temp->credits=3;

            //call insert function
            course_insert(temp);
            break;

        case 'd':
            course_drop(head);
            break;

        case 's':
            schedule_print(head);
            break;

        case 'q':
            schedule_save();
            while(head != NULL) {
                temp = head;
                head = head->next; //move front to next node
                free(temp); //free malloc from removed node`
            }
            // main loop will take care of this.
            break;

        default:
            printf("\nError: Invalid Input.  Please try again...\n\n");
            break;
    }
}
