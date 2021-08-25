/*
*Title:Assignment - Employee Database Implementation
*Course:CST8234 -C language
*Term :Summer 2021
*
*
*   Status:
*   All Requirements completed.
**/

/**************************************************************************
Declare include files
***************************************************************************/
#include "assign2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**************************************************************************
 Declare MACROs
**************************************************************************/

#define MAX_NAME_LENGTH 100
#define MAX_JOB_LENGTH 100

/**************************************************************************
 Declare global variables
**************************************************************************/
/* Employee structure*/
struct Employee
{
    /* Employee details */
    int *empID;
    int *age;
    char *name;
    char *gender;
    char *job_description;

    /* pointers to next employee structures in the linked list*/
    struct Employee *next;

}; /*end struct Employee*/

/*Pointer to the first element of the Linked list*/
struct Employee *employee_list;

/*Database MAX capacity*/
int number_employees = 150;

/**************************************************************************
 * Main function
 *This project implements a program that create, populate and maintain an 
 *employee database, with each employee represented by his/her name, gender, 
 *age and job description 
 * 
 * Version: 1.0
 * Author/Student Name: Younes Boutaleb
 **************************************************************************/

int main()
{
    /*This is the user input for employee name to be modified/deleted*/
    char name[100];
    /*This is a pointer to employee name*/
    char *emp_name = name;
    /*This is the user input for employee gender o be modified/deleted*/
    char gender;
    /*This is a pointer to employee gender*/
    char *emp_gender = &gender;
    /*This is the user input for employee job profile o be modified/deleted*/
    char profile[100];
    /*This is a pointer to employee job profile*/
    char *emp_profile = profile;
    /*This is the user input for employee age  o be modified/deleted*/
    int emp_age;
    /*this is the return code of the user input*/
    int rc;
    /*this is the action chosen by the user from the main menu*/
    char action = '0';
    /*this is for loop variable*/
    int index = 0;
    /*Number of entries corresponding to the entered feature*/
    int i;
    /*The entry selected by the user to be modified/deleted*/
    int entry;
    /*The current number of employees in the database*/
    int count = 0;
    /*struct Employee variable used to iterate through the database*/
    struct Employee *current;
    /*The head of the ll*/
    employee_list = NULL;
    /*C-String which holds the feature entered by the user*/
    char str1[21];
    /*Pointer to the str1 String*/
    char *feature = str1;
    /*C-String which holds the confirmation/deny of update/delete operation*/
    char str2[2];
    /*Pointer to the str2 String*/
    char *choice = str2;
    /*Array of integers which stores the IDs of employees having the same entered feature*/
    int indexArray[number_employees];

    /**************************************************************************
Prompt for the action to be performed
***************************************************************************/

    /*Display menu*/
    menu();

    while (action != 'q')
    {

        /*Prompt for the action to be performed and validates the input */
        action = getAction();

        /**************************************************************************
Define all actions
***************************************************************************/

        /*This switch statements executes the chosen action */
        switch (action)
        {

        /*Insert a new employee*/
        case '1':
            /*Go to the main menu if the database is full*/
            if (count == number_employees)
            {
                puts("The database is Full. All employees' information already entered.");
                break;
            } /*end if*/

            /**************************************************************************
Allocate memory to the new database element
***************************************************************************/

            /*struct Employee to be inserted in the database*/
            struct Employee *newEmployee;
            /*Allocate and initialize memory for all structs and their memebers*/

            newEmployee = (struct Employee *)malloc(sizeof(struct Employee));
            newEmployee->next = (struct Employee *)malloc(sizeof(struct Employee));

            newEmployee->name = (char *)malloc(sizeof(char) * MAX_NAME_LENGTH);
            newEmployee->gender = (char *)malloc(sizeof(char));
            newEmployee->age = (int *)malloc(sizeof(int));
            newEmployee->empID = (int *)malloc(sizeof(int));
            newEmployee->job_description = (char *)malloc(sizeof(char) * MAX_JOB_LENGTH);

            if ((newEmployee == NULL) || (newEmployee->next == NULL) || (newEmployee->name == NULL) || (newEmployee->gender == NULL) || (newEmployee->age == NULL) || (newEmployee->job_description == NULL))
            {
                fprintf(stderr, "Error - could not allocate memory");
                exit(EXIT_FAILURE);
            } /*end if    */

            /**************************************************************************
Initialize memory of the new database element
***************************************************************************/
            memset(newEmployee->name, '\0', sizeof(char) * MAX_NAME_LENGTH);
            memset(newEmployee->gender, '\0', sizeof(char));
            memset(newEmployee->age, '\0', sizeof(int));
            memset(newEmployee->empID, '\0', sizeof(int));
            memset(newEmployee->job_description, '\0', sizeof(char) * MAX_JOB_LENGTH);

            /**************************************************************************
Get new employee features and insert it in the database
***************************************************************************/
            /*Get the employee name*/
            strcpy(newEmployee->name, getName());
            /*Get the employee gender*/
            strcpy(newEmployee->gender, getGender());
            /*Get the employee age*/
            puts("Enter age: ");
            *newEmployee->age = checkIntegerInput();
            /*Get the employee ID*/
            *newEmployee->empID = count + 1;
            /*Get the employee job profile*/
            strcpy(newEmployee->job_description, getProfile());

            /*Check if the employee aready exixts in the database*/
            current = employee_list;
            while (current != NULL)
            {
                /*If all the features of the current employee are same as the new added employee then discard the new added employee*/
                if ((strcmp(newEmployee->name, current->name) == 0) && (strcmp(newEmployee->gender, current->gender) == 0) && (strcmp(newEmployee->job_description, current->job_description) == 0) && (*newEmployee->age == *current->age))
                {
                    puts("\nThis employee already exists in the database");
                    break;

                } /*end if*/
                else
                {
                    /*If the current employee does not have the same features as the inserted employee then move to the next employee*/
                    current = current->next;
                } /*end else*/

            } /*end while*/

            if (current == NULL)
            {
                /*Add the inserted employee at the linked list head if it's empty*/
                if (employee_list == NULL)
                {
                    employee_list = newEmployee;
                    employee_list->next = NULL;
                } /*end if*/
                  /*Add the inserted employee at the second postion of  the linked list*/
                else if (employee_list->next == NULL)
                {
                    employee_list->next = newEmployee;
                    employee_list->next->next = NULL;
                } /*end else if*/

                else
                { /*go to the the last position of the LL*/
                    current = employee_list;
                    while (current->next != NULL)
                    { /*advance to the next position*/
                        current = current->next;
                    } /*end while*/
                    /*Add the added employee in the last position of the LL */
                    if (current->next == NULL)
                    {
                        current->next = newEmployee;
                        /*The newly added employee points to NULL*/
                        current->next->next = NULL;
                    }
                } /*end else*/

                /*Print the newly added employee information */
                printf("Newly added Employee information:\nName: %s, Gender: %s, Age: %d, Job profile: %s.", newEmployee->name, newEmployee->gender, *newEmployee->age, newEmployee->job_description);
                /*Increment the number of employees in the database*/
                count++;
            } /*end if*/
            puts("\nWhat would you like to do next");
            break;

        /*Modify existing employee information*/
        case '2':
            /*Go back to main menu if the database is empty*/
            if (count == 0)
            {
                puts("The database is empty. Please insert employees information.");
                break;
            } /*end if*/
            /*Prompt for the employee feature to be updated*/
            printf("Enter the employee feature (name, gender, age, job profile) you wish to change:\n");
            /*Get and validate the employee feature */
            strcpy(feature, getFeature());

            /*Update by name*/
            if ((strcmp(feature, "NAME") == 0))
            {
                /*Get the name of the employee to be updated*/
                strcpy(emp_name, getName());
                /*This is the number of employees having the entered feature*/
                i = 0;
                /*Loop through the database */
                current = employee_list;
                while (current != NULL)
                {

                    if ((strcmp(current->name, emp_name) == 0))
                    {
                        /*store the ID of corresponding employee in the indexArray array*/
                        indexArray[i] = *current->empID;
                        /*Display all corresponding entries*/
                        printf("%d) %s %s %d %s\n", i + 1, current->name, current->gender, *current->age, current->job_description);
                        /*Increment the number of corresponding entries*/
                        i++;
                    } /*end if*/

                    current = current->next;
                } /*end while*/

                /*Go to main menu if no corresponding entry*/
                if (i == 0)
                {
                    puts("The entered information doesn't correspond to any of the existing employees");
                    puts("What would you like to do next");
                    break;
                } /*end if*/

                else
                {
                    puts("Select which entry you'd like to modify:");
                }

                /*Ask user to select the entry to be modified from the displayed entries*/
                entry = checkIntegerInput();
                /*Prompt for the new value*/
                strcpy(emp_name, getName());
                /*confirm the user's decision to modify the chosen entry*/
                strcpy(choice, confirmChoice());
                /*If the user confirms then overwrite the employee feature with the new value*/
                if (strcmp(choice, "Y") == 0)
                {
                    current = employee_list;
                    while (current != NULL)
                    {

                        if (indexArray[entry - 1] == *current->empID)
                        {
                            strcpy(current->name, emp_name);
                            /*Print the employee updated info*/
                            printf("Modified Employee information:\nName: %s, Gender: %s, Age: %d, Job profile: %s.", current->name, current->gender, *current->age, current->job_description);
                            break;
                        }
                    } /*end while*/

                } /*end if*/

                /*If the user didn't confirm the update operation then go to the main menu*/
                else
                {
                    puts("\nEntry not changed");
                } /*end else*/
            }
            else if ((strcmp(feature, "GENDER") == 0))
            {
                /*Get the gender of the employee to be updated*/
                strcpy(emp_gender, getGender());
                /*This is the number of employees having the entered feature*/
                i = 0;
                /*Loop through the database */
                current = employee_list;
                while (current != NULL)
                {

                    if ((strcmp(current->gender, emp_gender) == 0))
                    {
                        /*store the ID of corresponding employee in the indexArray array*/
                        indexArray[i] = *current->empID;
                        /*Display all corresponding entries*/
                        printf("%d) %s %s %d %s\n", i + 1, current->name, current->gender, *current->age, current->job_description);
                        /*Increment the number of corresponding entries*/
                        i++;
                    } /*end if*/

                    current = current->next;
                } /*end while*/

                /*Go to main menu if no corresponding entry*/
                if (i == 0)
                {
                    puts("The entered information doesn't correspond to any of the existing employees");
                    puts("What would you like to do next");
                    break;
                } /*end if*/
                else
                {
                    puts("Select which entry you'd like to modify:");
                } /*end else*/

                /*Ask user to select the entry to be modified from the displayed entries*/
                entry = checkIntegerInput();
                /*Prompt for the new value*/
                strcpy(emp_gender, getGender());
                /*confirm the user's decision to modify the chosen entry*/
                strcpy(choice, confirmChoice());
                /*If the user confirms then overwrite the employee feature with the new value*/
                if (strcmp(choice, "Y") == 0)
                {
                    current = employee_list;
                    while (current != NULL)
                    {

                        if (indexArray[entry - 1] == *current->empID)
                        {
                            strcpy(current->gender, emp_gender);
                            /*Print the employee updated info*/
                            printf("Modified Employee information:\nName: %s, Gender: %s, Age: %d, Job profile: %s.", current->name, current->gender, *current->age, current->job_description);
                            break;
                        }
                    } /*end while*/

                } /*end if*/
                /*If the user didn't confirm the update operation then go to the main menu*/
                else
                {
                    puts("\nEntry not changed");
                } /*end else*/
            }     /*end else if*/

            else if ((strcmp(feature, "AGE") == 0))
            {
                /*Get the age of the employee to be updated*/
                puts("\nEnter age:");
                emp_age = checkIntegerInput();
                /*This is the number of employees having the entered feature*/
                i = 0;
                /*Loop through the database */
                current = employee_list;
                while (current != NULL)
                {

                    if (*current->age == emp_age)
                    {
                        /*store the ID of corresponding employee in the indexArray array*/
                        indexArray[i] = *current->empID;
                        /*Display all corresponding entries*/
                        printf("%d) %s %s %d %s\n", i + 1, current->name, current->gender, *current->age, current->job_description);
                        /*Increment the number of corresponding entries*/
                        i++;
                    } /*end if*/

                    current = current->next;
                } /*end while*/
                /*Go to main menu if no corresponding entry*/
                if (i == 0)
                {
                    puts("The entered information doesn't correspond to any of the existing employees");
                    puts("What would you like to do next");
                    break;
                } /*end if*/
                else
                {
                    /*Display all corresponding entries*/
                    puts("Select which entry you'd like to modify:");

                } /*end else*/
                /*Ask user to select the entry to be modified from the displayed entries*/
                entry = checkIntegerInput();
                /*Prompt for the new value*/
                puts("Enter age:");
                emp_age = checkIntegerInput();
                /*confirm the user's decision to modify the chosen entry*/
                strcpy(choice, confirmChoice());
                /*If the user confirms then overwrite the employee feature with the new value*/
                if (strcmp(choice, "Y") == 0)
                {
                    current = employee_list;
                    while (current != NULL)
                    {

                        if (indexArray[entry - 1] == *current->empID)
                        {
                            *current->age = emp_age;
                            /*Print the employee updated info*/
                            printf("Modified Employee information:\nName: %s, Gender: %s, Age: %d, Job profile: %s.", current->name, current->gender, *current->age, current->job_description);
                            break;
                        }
                    } /*end while*/
                }     /*end if*/
                      /*If the user didn't confirm the update operation then go to the main menu*/
                else
                {
                    puts("\nEntry not changed");
                } /*end else*/
            }     /*end else if*/
            /*Get the job profile of the employee to be updated*/
            else if ((strcmp(feature, "JOB PROFILE") == 0))
            {
                strcpy(emp_profile, getProfile());
                /*This is the number of employees having the entered feature*/
                i = 0;
                /*Loop through the database */
                current = employee_list;
                while (current != NULL)
                {

                    if ((strcmp(current->job_description, emp_profile) == 0))
                    {
                        /*store the ID of corresponding employee in the indexArray array*/
                        indexArray[i] = *current->empID;
                        /*Display all corresponding entries*/
                        printf("%d) %s %s %d %s\n", i + 1, current->name, current->gender, *current->age, current->job_description);
                        /*Increment the number of corresponding entries*/
                        i++;
                    } /*end if*/

                    current = current->next;
                } /*end while*/
                /*Go to main menu if no corresponding entry*/
                if (i == 0)
                {
                    puts("The entered information doesn't correspond to any of the existing employees");
                    puts("What would you like to do next");
                    break;
                } /*end if*/
                else
                {
                    /*Display all corresponding entries*/
                    puts("Select which entry you'd like to modify:");

                } /*end else*/
                /*Ask user to select the entry to be modified from the displayed entries*/
                entry = checkIntegerInput();
                /*Prompt for the new value*/
                strcpy(emp_profile, getProfile());
                /*confirm the user's decision to modify the chosen entry*/
                strcpy(choice, confirmChoice());
                /*If the user confirms then overwrite the employee feature with the new value*/
                if (strcmp(choice, "Y") == 0)
                {
                    current = employee_list;
                    while (current != NULL)
                    {
                        if (indexArray[entry - 1] == *current->empID)
                        {
                            strcpy(current->job_description, emp_profile);
                            /*Print the employee updated info*/
                            printf("Modified Employee information:\nName: %s, Gender: %s, Age: %d, Job profile: %s.", current->name, current->gender, *current->age, current->job_description);
                            break;
                        }
                    } /*end while*/
                }     /*end if*/

                /*If the user didn't confirm the update operation then go to the main menu*/
                else
                {

                    puts("\nEntry not changed");
                } /*end else*/
            }     /*end else if*/
            puts("\nWhat would you like to do next");
            break;

        /*Delete employees*/
        case '3':
            /*Go back to main menu if the database is empty*/
            if (count == 0)
            {

                puts("The database is empty. Please insert employees information.");
                break;
            } /*end if*/
            /*Prompt for the employee feature to be deleted*/
            printf("Enter the employee feature (name, gender, age, job profile) you wish to delete:\n");
            /*Get and validate the employee feature */
            strcpy(feature, getFeature());

            /*Deletion by name*/
            if ((strcmp(feature, "NAME") == 0))
            {
                /*Get the name of the employee to be updated*/
                strcpy(emp_name, getName());
                /*This is the number of employees having the entered feature*/
                i = 0;
                /*Loop through the database */
                current = employee_list;
                while (current != NULL)
                {

                    if ((strcmp(current->name, emp_name) == 0))
                    {
                        /*store the ID of corresponding employee in the indexArray array*/
                        indexArray[i] = *current->empID;
                        /*Display all corresponding entries*/
                        printf("%d) %s %s %d %s\n", i + 1, current->name, current->gender, *current->age, current->job_description);
                        /*Increment the number of corresponding entries*/
                        i++;
                    } /*end if*/

                    current = current->next;
                } /*end while*/

                /*Go to main menu if no corresponding entry*/
                if (i == 0)
                {

                    puts("The entered information doesn't correspond to any of the existing employees");
                    puts("What would you like to do next");
                    break;
                } /*end if*/
                else
                {
                    /*Display all corresponding entries*/
                    puts("Select which entry you'd like to delete");

                } /*end else*/

                /*Ask user to select the entry to be deleted from the displayed entries*/
                entry = checkIntegerInput();
                /*confirm the user's decision to delete the chosen entry*/
                strcpy(choice, confirmChoice());
                /*If the user confirms then delete the entry*/
                /*decrement the number of employees*/
                /*call the delete function using the employee ID*/
                if (strcmp(choice, "Y") == 0)
                {
                    deleteEntry(indexArray[entry - 1]);
                    count--;
                } /*end if*/

                /*If the user didn't confirm the deletion operation then go to the main menu*/
                else
                {
                    puts("\nEntry not changed");
                } /*end else*/
            }

            /*Deletion by Gender*/
            else if ((strcmp(feature, "GENDER") == 0))
            {
                /*Get the gender  of the employee to be deleted*/
                strcpy(emp_gender, getGender());
                /*This is the number of employees having the entered feature*/
                i = 0;
                /*Loop through the database */
                current = employee_list;
                while (current != NULL)
                {

                    if ((strcmp(current->gender, emp_gender) == 0))
                    {
                        /*store the ID of corresponding employee in the indexArray array*/
                        indexArray[i] = *current->empID;
                        /*Display all corresponding entries*/
                        printf("%d) %s %s %d %s\n", i + 1, current->name, current->gender, *current->age, current->job_description);
                        /*Increment the number of corresponding entries*/
                        i++;
                    } /*end if*/

                    current = current->next;
                } /*end while*/

                /*Go to main menu if no corresponding entry*/
                if (i == 0)
                {

                    puts("The entered information doesn't correspond to any of the existing employees");
                    puts("What would you like to do next");
                    break;
                } /*end if*/
                else
                {
                    puts("Select which entry you'd like to delete");

                } /*end else*/
                /*Ask user to select the entry to be deleted from the displayed entries*/
                entry = checkIntegerInput();
                /*confirm the user's decision to delete the chosen entry*/
                strcpy(choice, confirmChoice());
                /*If the user confirms then delete the entry*/
                /*decrement the number of employees*/
                /*call deletEntry method using employee's ID stored in thye arrayIndex*/
                if (strcmp(choice, "Y") == 0)
                {
                    deleteEntry(indexArray[entry - 1]);
                    count--;
                } /*end if*/
                /*If the user didn't confirm the deletion operation then go to the main menu*/
                else
                {
                    puts("\nEntry not changed");
                } /*end else*/
            }     /*end if else*/

            /*Deletion by Age*/
            else if ((strcmp(feature, "AGE") == 0))
            {
                /*Get the age of the employee to be deleted*/
                puts("Enter age");
                emp_age = checkIntegerInput();
                /*This is the number of employees having the entered feature*/
                i = 0;
                /*Loop through the database */
                current = employee_list;
                while (current != NULL)
                {

                    if (*current->age == emp_age)
                    {
                        /*store the ID of corresponding employee in the indexArray array*/
                        indexArray[i] = *current->empID;
                        /*Display all corresponding entries*/
                        printf("%d) %s %s %d %s\n", i + 1, current->name, current->gender, *current->age, current->job_description);
                        /*Increment the number of corresponding entries*/
                        i++;
                    } /*end if*/

                    current = current->next;
                } /*end while*/

                /*Go to main menu if no corresponding entry*/
                if (i == 0)
                {
                    /*Display all corresponding entries*/
                    puts("The entered information doesn't correspond to any of the existing employees");
                    puts("What would you like to do next");
                    break;
                } /*end if*/
                else
                {
                    puts("Select which entry you'd like to delete ");

                } /*end else*/
                /*Ask user to select the entry to be deleted from the displayed entries*/
                entry = checkIntegerInput();
                /*confirm the user's decision to delete the chosen entry*/
                strcpy(choice, confirmChoice());
                /*If the user confirms then delete the entry*/
                /*decrement the number of employees*/
                /*call deletEntry method using employee's ID stored in thye arrayIndex*/
                if (strcmp(choice, "Y") == 0)
                {
                    deleteEntry(indexArray[entry - 1]);
                    count--;
                } /*end if*/
                /*If the user didn't confirm the deletion operation then go to the main menu*/
                else
                {
                    puts("\nEntry not changed");
                } /*end else*/
            }     /*end if else*/
            /*Deletion by Job profile*/
            else if ((strcmp(feature, "JOB PROFILE") == 0))
            {
                /*Get the age of the employee to be deleted*/
                strcpy(emp_profile, getProfile());
                /*This is the number of employees having the entered feature*/
                i = 0;
                /*Loop through the database */
                current = employee_list;
                while (current != NULL)
                {
                    if ((strcmp(current->job_description, emp_profile) == 0))
                    {
                        /*store the ID of corresponding employee in the indexArray array*/
                        indexArray[i] = *current->empID;
                        /*Display all corresponding entries*/
                        printf("%d) %s %s %d %s\n", i + 1, current->name, current->gender, *current->age, current->job_description);
                        /*Increment the number of corresponding entries*/
                        i++;
                    } /*end if*/

                    current = current->next;
                } /*end while*/

                /*Go to main menu if no corresponding entry*/
                if (i == 0)
                {
                    /*Display all corresponding entries*/
                    puts("The entered information doesn't correspond to any of the existing employees");
                    puts("What would you like to do next");
                    break;
                } /*end if*/
                else
                {
                    puts("Select which entry you'd like to delete ");

                } /*end else*/
                /*Ask user to select the entry to be deleted from the displayed entries*/
                entry = checkIntegerInput();
                /*confirm the user's decision to delete the chosen entry*/
                strcpy(choice, confirmChoice());
                /*If the user confirms then delete the entry*/
                /*decrement the number of employees*/
                /*call deletEntry method using employee's ID stored in thye arrayIndex*/
                if (strcmp(choice, "Y") == 0)
                {
                    deleteEntry(indexArray[entry - 1]);
                    count--;
                } /*end if*/
                else
                {
                    /*If the user didn't confirm the deletion operation then go to the main menu*/
                    puts("\nEntry not changed");
                } /*end else*/
            }     /*end if else*/
            puts("\nWhat would you like to do next");
            break;
        /*Show all database entries*/
        case '4':
            /*Go to main menu if database is empty*/
            if (count == 0)
            {
                puts("The database is empty. Please insert employees information.");
                break;
            } /*end if */
            /*Printthe number of employees in the database*/
            printf("\nTotal number of employees: %d.\n", count);
            /*Print all entries*/
            current = employee_list;
            while (current != NULL)
            {
                printf("\nName: %s, Gender: %s, Age: %d, Job profile: %s.", current->name, current->gender, *current->age, current->job_description);
                current = current->next;
            } /*end while*/
            puts("\n\nWhat would you like to do next");
            break;
        /*Exit the program*/
        case 'q':
            puts("Have a nice time!");
            break;

        /*Print error message and Re-prompt for a valid action*/
        default:

            puts("Not accepted. Enter a valid option number [1-4 or q]");
            break;

        } /*end switch*/
    }     /*end while*/

    /**************************************************************************
  Free memory allocated to datastructures
***************************************************************************/
    current = employee_list;

    while (current != NULL)
    {
        /*Free all structures and their members*/
        free(current->gender);
        free(current->job_description);
        free(current->age);
        free(current->empID);
        free(current->name);
        free(current->next); 
        free(current);

        current = current->next;

    } /*end while*/

    return EXIT_SUCCESS;

} /*end main*/

/**************************************************************************
   Display menu of actions
***************************************************************************/
void menu()
{

    printf("Choose one of the following actions:\n");
    printf("[1]- Insert data of another employee\n");
    printf("[2]- Modify existing employee information\n");
    printf("[3]- Delete an employee's data\n");
    printf("[4]- Show all database enteries\n");
    printf("[5]- To quit \n");
} /* end menu() */

/**************************************************************************
  Check for integer inputs
***************************************************************************/

int checkIntegerInput()
{

    /*This is the user input */
    int number;
    /*This the return code */
    int rc = 0;
    /*This the next char after scanf() terminates */
    char nextChar;

    /*Loops untill the user enter a valid input */
    while (rc != 1)
    {
        /*it takes 1 if scanf reads an integer*/
        rc = scanf(" %d", &number);
        /*Read the next character in stdin after scanf is executed*/
        nextChar = getchar();

        /*Checks for clrt-d input which stands for the end of input EOF
    Exits the game with failure if the user enters the EOF character*/
        if (nextChar == -1)
        {
            puts("Program shutdown.\n");
            exit(EXIT_FAILURE);
        } /*end if*/

        /*Prints an error message if the user enters an invalid input (strings/float/negative integer)
    and goes back to the while loop*/
        else if (rc != 1 || nextChar != '\n' || number < 0)
        {
            rc = 0;
            printf("Error - enter a positive integer number: ");

            /*if not a valid input clear the stdin*/
            if (nextChar != '\n')
            {

                while (getchar() != '\n')
                {
                    /*chomp stdin*/
                } /*end while*/
            }     /*end  if*/
        }         /*end else if*/
    }

    /*return valid input*/
    return number;

} /* end checkIntegerInput */

/**************************************************************************
   Prompt  for employee name
***************************************************************************/
char *getName()
{
    /*A pointer to the user input*/
    char *name;
    /*Allocate and initialize memory and point to using name pointer*/
    name = (char *)malloc(sizeof(char) * MAX_JOB_LENGTH);
    memset(name, '\0', sizeof(char) * MAX_JOB_LENGTH);
    /*This is the return code*/
    int rc = 0;
    /*Prompt for employee name*/
    printf("Enter name:\n");
    rc = scanf(" %100[^\n]s", name);

    /*Shutdown the program if the user enters the EOF charachter*/
    if (rc == -1)
    {
        puts("Program terminated.");
        exit(EXIT_FAILURE);
    } /*end if*/

    while (getchar() != '\n')
    {
        /* chomp stdin */
    } /*end  while*/

    return name;
} /*end getName*/

/**************************************************************************
   Prompt  for employee gender
***************************************************************************/
char *getGender()
{
    /*A pointer to the user input*/
    char *gender;
    /*Allocate and initialize memory and point to using gender pointer*/
    gender = (char *)malloc(sizeof(char));
    memset(gender, '\0', sizeof(char));
    /*This is the return code*/
    int rc = 0;
    /*Prompt for employee gender and validate the input*/
    while (strcmp(gender, "F") != 0 && strcmp(gender, "M") != 0)
    {
        rc = 0;
        printf("Enter Gender: \n");
        rc = scanf(" %1[^\n]s", gender);
        gender = toUpperCase(gender);

        /*Shutdown the program if the user enters the EOF charachter*/
        if (rc == -1)
        {
            puts("Program terminated.");
            exit(EXIT_FAILURE);

        } /*end if*/
        else if (strcmp(gender, "F") != 0 && strcmp(gender, "M") != 0)
        {
            puts("Enter a valid Gender: F for female, and M for male");

            while (getchar() != '\n')
            {
                /* chomp stdin */
            } /*end  while*/
        }     /*end if*/

    } /*end while*/

    return gender;
} /*end getGender*/

/**************************************************************************
   Prompt  for employee job profile
***************************************************************************/
char *getProfile()
{
    /*A pointer to the user input*/
    char *profile;
    /*Allocate and initialize memory and point to using profile pointer*/
    profile = (char *)malloc(sizeof(char) * MAX_JOB_LENGTH);
    memset(profile, '\0', sizeof(char) * MAX_JOB_LENGTH);
    /*This is the return code*/
    int rc = 0;
    /*Prompt for employee job profile*/
    printf("Enter Job Profile: \n");
    rc = scanf(" %100[^\n]s", profile);

    /*Shutdown the program if the user enters the EOF charachter*/
    if (rc == -1)
    {
        puts("Program terminated.");
        exit(EXIT_FAILURE);
    } /*end if*/

    while (getchar() != '\n')
    {
        /* chomp stdin */
    } /*end  while*/
    return profile;
} /*end getProfile*/

/**************************************************************************
   Prompt  for employee feature to be updated/deleted
***************************************************************************/
char *getFeature()
{
    /*This is the return code*/
    int rc = 0;
    /*A pointer to the user input*/
    char *feature;
    /*Allocate and initialize memory and point to using feature pointer*/
    feature = (char *)malloc(sizeof(char) * MAX_JOB_LENGTH);
    memset(feature, '\0', sizeof(char) * MAX_JOB_LENGTH);
    /*Prompt for feature and validate input*/
    while ((strcmp(feature, "NAME") != 0) && (strcmp(feature, "GENDER") != 0) && (strcmp(feature, "AGE") != 0) && (strcmp(feature, "JOB PROFILE") != 0))
    {
        rc = scanf(" %[^\n]s", feature);
        /*Convert the input to uppercase*/
        feature = toUpperCase(feature);

        /*Shutdown the program if the user enters the EOF charachter*/
        if (rc == -1)
        {
            puts("\nProgram terminated.");
            exit(EXIT_FAILURE);
        } /*end if*/

        if ((strcmp(feature, "NAME") != 0) && (strcmp(feature, "GENDER") != 0) && (strcmp(feature, "AGE") != 0) && (strcmp(feature, "JOB PROFILE") != 0))
        {

            puts("Enter the employee feature (name, gender, age, job profile) you wish to change:");
        }

        while (getchar() != '\n')
        {
            /* chomp stdin */
        } /*end  while*/
    }

    return feature;
} /*end getFeature*/

/**************************************************************************
  convert a string to uppercase
***************************************************************************/
char *toUpperCase(char *feature)
{
    /*This is the index of a specific charachter in the feature String*/
    int i = 0;
    while (feature[i])
    {
        /*Convert the curent charachter to uppercase*/
        feature[i] = toupper(feature[i]);
        i++;
    }
    return feature;
} /*end toUpperCase*/

/**************************************************************************
  Prompt user to confirm update/deletion operation
***************************************************************************/
char *confirmChoice()
{
    /*A pointer to the user input*/
    char *choice;
    /*Allocate and initialize memory and point to using choice pointer*/
    choice = (char *)malloc(sizeof(char) * 2);
    memset(choice, '\0', sizeof(char) * 2);
    /*This is the return code*/
    int rc = 0;
    /*Prompt for employee job choice and validate the input*/
    while ((strcmp(choice, "Y") != 0) && (strcmp(choice, "N") != 0))
    {
        rc = 0;
        printf("Are you sure: \n");
        rc = scanf(" %[^\n]s", choice);
        choice = toUpperCase(choice);

        /*Shutdown the program if the user enters the EOF charachter*/
        if (rc == -1)
        {
            puts("Program terminated.");
            exit(EXIT_FAILURE);

        } /*end if*/
        else if (strcmp(choice, "Y") != 0 && strcmp(choice, "N") != 0)
        {
            puts("Enter a valid choice: Y for Yes, and N for No");
        } /*end if*/

        while (getchar() != '\n')
        {
            /* chomp stdin */
        } /*end  while*/

    } /*end while*/

    return choice;
} /*end confirmChoice*/

/**************************************************************************
  deletes an employee from the database
  index: the index of the entry tobe deleted in the database
  count: number of entries in the database
***************************************************************************/
void deleteEntry(int emp_ID)
{
;

    /*delete the LinkedList head if it's ID corresponds to emp_ID*/
    if (*employee_list->empID == emp_ID)
    {
        printf("Employee named %s succesfully deleted.", employee_list->name);
        /*The LL head now points to the second element*/
        employee_list = employee_list->next;

    } /*end if*/
    /*delete the LinkedList second element if it's ID corresponds to emp_ID*/
    else if (*employee_list->next->empID == emp_ID)
    {


        printf("Employee named %s succesfully deleted.", employee_list->next->name);
        /*The third elemet is now the next element to the head*/
        employee_list->next = employee_list->next->next;

    } /*end if*/
    else
    {
        /*loop through the LL to find the element to delete starting from the head*/
        struct Employee *current;
        current = employee_list;
        while (current->next != NULL)
        {
            if (emp_ID == *current->next->empID)
            {
                printf("Employee named %s succesfully deleted.", current->next->name);
                /*when the element to delete is found its previous element will point to its next element*/
                current->next = current->next->next;
                break;
            }
            /*Go to the next element in the LL if the element to delete is not found*/
            current = current->next;

        } /*end while*/
    }


} /*end deleteEntry*/

/**************************************************************************
  Asks user to chose an option from the main menu
***************************************************************************/
char getAction()
{
    /*This is the return code*/
    int rc = 0;
    /*This is the menu option to be performed*/
    char action = '0';
    /*A pointer to the user input*/
    char *input;
    /*Allocate and initialize memory and point to using input pointer*/
    input = (char *)malloc(sizeof(char) * 100);
    memset(input, '\0', sizeof(char) * 100);
    /*Prompt for employee job choice and validate the input*/
    rc = scanf(" %100[^\n]s", input);
    printf("You pressed: %s\n", input);

    /*Shutdown the program if the user enters the EOF charachter*/
    if (rc == -1)
    {
        puts("Program terminated.");
        exit(EXIT_FAILURE);

    } /*end if*/
    /*Convert valid inputs to charachters*/
    if ((strcmp(input, "1") == 0) || (strcmp(input, "2") == 0) || (strcmp(input, "3") == 0) || (strcmp(input, "4") == 0) || (strcmp(input, "q") == 0))
    {
        action = input[0];
    } /*end if*/

    while (getchar() != '\n')
    {
        /* chomp stdin */
    } /*end  while*/

    return action;
}
