#include <stdio.h>
#include <stdlib.h>

struct Node *add_record();
int dis_by_id();
int dis_by_year();
int dis_by_fac();
int del_rec();
int sort();
void print_menu();
void display_stack();

struct Node
{
    // each node holds integer data
    // conversion needed while printing name_surname
    int data;
    struct Node *next;
};

// our record stacks
struct Node *record_stack[500]; // main stack (is used when a record is added)
int stack_marker = 0;           // number of records on the main stack

int main()
{
    while (1) // infinite loop
    {
        // Getting option from the user
        int choice;
        print_menu();
        scanf("%1d", &choice);

        if (choice == 1)
        {
            // add record, increment record count
            struct Node *record = (struct Node *)malloc(sizeof(struct Node *));
            record = add_record();
            record_stack[stack_marker] = record;
            stack_marker++;
        }
        else if (choice == 2)
        {
            dis_by_id();
        }
        else if (choice == 3)
        {
            dis_by_year();
        }
        else if (choice == 4)
        {
            dis_by_fac();
        }
        else if (choice == 5)
        {
            // del record, decrement count
            stack_marker--;
            // del_rec();
        }
        else if (choice == 6)
        {
            // exit the program
            exit(0);
        }
        else
        {
            printf("Wrong option. Please pick a valid one.\n");
        }
    }
}

struct Node *add_record()
{
    /*Adds the pointer of records to the main stack.
    Records are in the form of a linked list:
    student_id->n->a->m->e */
    struct Node *head = (struct Node *)malloc(sizeof(struct Node *));
    struct Node *current_pt = NULL;
    struct Node *node = (struct Node *)malloc(sizeof(struct Node *));
    head = node;
    current_pt = node;

    printf("\nEnter school number: ");
    scanf("%9d", &(node->data));
    getchar();
    printf("\nEnter  Name Surname: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        struct Node *new_Node = (struct Node *)malloc(sizeof(struct Node));
        current_pt->next = new_Node;
        current_pt = new_Node;
        current_pt->next = NULL;
        current_pt->data = c;
    }
    current_pt->next = NULL;
    return head;
}

int dis_by_id()
{
    // sort();
    display_stack();
}

int dis_by_year()
{
    // sort();
    display_stack();
}

int dis_by_fac()
{
    sort(9, 7);
    display_stack();
}

int del_rec()
{
    // sort();
}

int sort(int start_id, int end_id)
{
    /*
    does sorting given which parts of student id is considered when sorting
    insertion sort is used
    start & end id: which part of student id is used when sorting
    e.g. -> start_id = 9, ed_id = 7, heads[0]->data = 123456789
    123 is cropped and used for sorting
    */

    for (int i = 1; i < stack_marker; i++)
    {
        int value_to_insert;
        int compared_value;
        int j;
        struct Node *value_to_insert_pt;

        j = i;

        value_to_insert = record_stack[i]->data; // BOOKMARK: THIS WILL BE MODIFIED
        value_to_insert_pt = record_stack[i];

        while (j > 0 && (compared_value = record_stack[j - 1]->data) > value_to_insert) // AND THIS TOO
        {
            record_stack[j] = record_stack[j - 1];
            j--;
        }
        record_stack[j] = value_to_insert_pt;
    }
}

void display_stack()
{
    struct Node *record_head;

    for (int i = 0; i < stack_marker; i++) // for each record till stack_marker
    {
        printf("School ID: ");
        record_head = record_stack[i];
        printf("%d", record_head->data);
        record_head = record_head->next;

        printf("\n");
        printf("Name Surname: ");
        while (record_head != NULL)
        {
            printf("%c", record_head->data);
            record_head = record_head->next;
        }
        printf("\n");
    }
}

void print_menu()
{
    // prints the main menu
    printf("1-Enter record with school number\n");
    printf("2-Display school numbers sorted by ID\n");
    printf("3-Display school numbers sorted by year\n");
    printf("4-Display school numbers sorted by the faculty codes\n");
    printf("5-Delete a record by school number\n");
    printf("6-Exit\n");
    printf("Enter choice: ");
}