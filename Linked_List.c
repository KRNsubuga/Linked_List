/*
 *Copyright: Kenny Rogers Nsubuga, 14/11/2021, Frankfurt University of Applied Sciences
 *Programm description:
 *A simple data structure for storing x amount of people's information in alphabetic order and linking them.
 *User is able to add/delete 1 or more people, print the list or quit the execution.
 */


/*Includes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*The kind of information to be stored is declared herein*/
struct Person
{
    char name[64], address[64];
    __int8 age;
    struct Person *next_one; //A pointer to the next person in the list.
};

typedef struct Person my_type;

/*Globals*/
my_type *first = NULL;
my_type *added_person = NULL;

/*Function prototypes*/
my_type *get_person(char name_x[64], __int8 age, char address_x[64]);

my_type *add_to_list(char N[64], __int8 A, char ADD[64]);

my_type *kick_out(char n[64]);

void print_list(my_type *list);

void wait_for_input(my_type *first, my_type *added_person);

void sweep(my_type *list);

/*Main*/
int main()
{
    wait_for_input(first, added_person); 

    sweep(first);

    first = NULL;
    added_person = NULL;

    return 0;
}

/*This function allocates memory for a person and assigns his/her parameters.*/
my_type *get_person(char name_x[64], __int8 age, char address_x[64])
{
    my_type *new_person = NULL;
    new_person = (my_type *)malloc(sizeof(my_type)); //malloc returns void pointer, hence the type cast.

    /*Check whether malloc succeeded.*/
    if(new_person != NULL)
    {
        strcpy(new_person->name, name_x); //copy is needed to avoid overwriting, given the type(char array)
        strcpy(new_person->address, address_x);
        new_person->age = age;
        new_person->next_one = NULL;
        printf("\nA new person was created at 0x%p and added to the list\n\n", new_person);
    }

    else 
    {
        printf("Memory allocation failed!\n");
    }
    return new_person;
}

/*This function adds a person to the list.*/
my_type *add_to_list(char N[64], __int8 A, char ADD[64])
{
    /*Incase the list is empty..*/
    if(first == NULL)
    {
        first = get_person(N, A, ADD);

        /*Double check malloc.*/
        if(first != NULL)
        {
            added_person = first;
        }
    }

    else
    {
        added_person->next_one = get_person(N, A, ADD);

        /*Double check malloc.*/
        if(added_person->next_one != NULL)
        {
            added_person = added_person->next_one;
        }
    }
    return first;
}

/*This function deletes a person from the list.*/
my_type *kick_out(char n[64])
{
    my_type *target_node, *previous_node;
    target_node = first;
    __int8 name_index = 1;

    /*Find the position in the list.*/
    while(target_node->next_one)
    {
        if(strcmp(n, target_node->name) == 0)
        {
            break;
        }
        previous_node = target_node;
        target_node = target_node->next_one;
        name_index++;
    }

    if(strcmp(n, target_node->name) != 0)
    {
        printf("\nThere's no such name on the list. Make sure you didn't misspell.\n\n");
    }

    else
    {
        printf("\nFound %s at position %i.\n\n", n, name_index);

        if(target_node != 0)
        {
            if(target_node == first)
            {
                first = target_node->next_one;
            }
            else
            {
                previous_node->next_one = target_node->next_one;
            }
        }
        printf("%s has been successfully deleted from the list.\n\n", n);
        free(target_node); //Delete the target from memory.
    }
    return first;
}

/*This function sorts the data(names in the list) in alphabetical order (ascending ).*/


/*This funcion displays the current list's content on the terminal.*/
void print_list(my_type *list)
{
    my_type *pointer;
    pointer = list;

    if(pointer == NULL)
    {
        printf("\nThe list is empty\n\n");
    }

    else
    {
        while(pointer)
        {
            printf("\nNAME: %s\nAGE: %i\n\nADDRESS: %s\nMEM. LOCATION: %p\n\nNEXT MEM.: %p.\n\n",
            pointer->name, pointer->age, pointer->address, pointer, pointer->next_one);
            pointer = pointer->next_one;
        }
    }
}

/*This function handles the user's input.*/
void wait_for_input(my_type *first, my_type *added_person)
{
    while(1)
    {
        char command[10], name[64], address[64];
        __int8 a; 
        printf("\nPlease enter one of these commands:\n'add' = add a person to list\n'del' = delete a person from the list\n'print' = print current list\n'q' = quit programm execution\n\n");
        fgets(command, sizeof(command), stdin);

        /*print*/
        if(strcmp("print\n", command) == 0)
        {
            print_list(first);
        }

        /*add*/
        else if(strcmp("add\n", command) == 0)
        {
            printf("\nEnter name:\n");
            fgets(name, 64, stdin);
            printf("\nEnter age:\n");
            scanf("%i", &a);
            fflush(stdin);
            printf("\nEnter address:\n");
            fgets(address, 64, stdin);          
            first = add_to_list(name, a, address);
        }

        /*delete*/
        else if(strcmp("del\n", command) == 0)
        {

            if(first == NULL)
            {
                printf("\nThe list is empty\n\n");
            }

            else
            {
                printf("\nEnter the person's name you want to delete:\n\n");
                fgets(name, 64, stdin);
                first = kick_out(name);
            }
        }
        /*quit*/
        else if(strcmp("q\n", command) == 0)
        {
            printf("\nSure?\ny/n:\n\n");
            fgets(command, sizeof(command), stdin);
            if(strcmp("y\n", command) == 0)
            {
                printf("You've quit the programm execution!\n");
                break;
            }
            else
            {
                continue;
            }
        }
        /*valid input*/
        else
        {
            printf("\nInvalid input :-(\n");
            continue;
        }
    }
}

/*This function cleans up the allocated memory.*/
void sweep(my_type *list)
{
    my_type *neighbor;
    while(list)
    {
        neighbor = list->next_one;
        free(list);
        list = neighbor;
    }
}