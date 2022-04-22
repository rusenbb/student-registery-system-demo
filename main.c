#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

struct Node *add_record();             // adds record to the main stack
void dis_by_id();                      // displays records by id
void dis_by_year();                    // displays records by year
void dis_by_fac();                     // displays records by faculty
void del_rec(int index);               // deletes record
int bin_search(int wanted_student_id); // used with del_rec
void sort(int start_id, int end_id);   // sorting func used with dis_by_... & bin_search funcs
void print_menu();                     // for clean code purposes
void display_stack();                  // for clean code purposes

struct Node
{
    // each node holds integer data
    // conversion needed while printing name_surname
    int data;
    struct Node *next;
};

// our record stacks
struct Node *record_stack[500]; // main stack (is used when a record is added or accesed)
int stack_marker = 0;           // number of records on the main stack

int main()
{
    while (true) // infinite loop
    {
        // Getting option from the user
        int choice;
        int last_choice = -1; // keeps track of the last action
        // e.g. if last choice already made program sort by id no need to repeat
        print_menu();
        scanf("%1d", &choice);

        if (choice == 1)
        {
            // add record, increment record count
            struct Node *record = (struct Node *)malloc(sizeof(struct Node));
            record = add_record();
            record_stack[stack_marker] = record;
            stack_marker++;
            last_choice = 1;
        }
        else if (choice == 2)
        {
            dis_by_id(last_choice);
            last_choice = 2;
        }
        else if (choice == 3)
        {
            dis_by_year(last_choice);
            last_choice = 3;
        }
        else if (choice == 4)
        {
            dis_by_fac(last_choice);
            last_choice = 4;
        }
        else if (choice == 5)
        {
            // del record, decrement count
            int student_id;
            int index;
            printf("Write the ID of the student in order to remove it from system: ");
            scanf("%d", &student_id);
            index = bin_search(student_id);
            if (index == -1)
            {
                printf("ID Not Found.\n Coudln't delete.\n");
                last_choice = 5;
                continue;
            }
            del_rec(index); // deletes the record and rearranges the stack
            printf("Deleted student that corresponds to ID: %d\n", student_id);
            printf("Currently there are %d students on the system.\n", stack_marker);
            last_choice = 5;
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
    struct Node *head = (struct Node *)malloc(sizeof(struct Node));
    struct Node *current_pt = NULL;
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
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

void dis_by_id(int last_choice)
{
    if (!(last_choice == 2))
    {
        sort(1, 4);
    }

    display_stack();
}

void dis_by_year(int last_choice)
{
    if (!(last_choice == 3))
    {
        sort(5, 6);
    }

    display_stack();
}

void dis_by_fac(int last_choice)
{
    if (!(last_choice == 3))
    {
        sort(7, 9);
    }

    display_stack();
}

int bin_search(int wanted_student_id)
{
    sort(1, 9); // first sort ids. using all numbers of id from first to nineth
    int low = 0;
    int high = stack_marker;
    int mid = (low + high) / 2;

    while (true)
    { // 1, 2, 3, 4, 5, 6,7
        if (wanted_student_id > record_stack[mid]->data)
        {
            low = mid + 1;
            mid = (low + high) / 2;
        }
        else if (wanted_student_id < record_stack[mid]->data)
        {
            high = mid - 1;
            mid = (low + high) / 2;
        }
        else
        {
            return mid;
        }

        if (low == high)
        {
            if (wanted_student_id != record_stack[mid]->data)
            {
                return -1;
            }
            return low; // could also be high
        }
    }
}

void sort(int start_id, int end_id)
{
    /*
    does sorting given which parts of student id is considered when sorting
    insertion sort is used
    start & end id: which part of student id is used when sorting
    e.g. -> end_id = 9, start_id = 7, heads[0]->data = 123456789
    123 is cropped and used for sorting
    */
    int crop_size;                                                              // This determines which part of id is thrown away e.g. 3 -> 12345678 ==> 12345
    int compare_part_len;                                                       // This determines which length of id is used e.g. 2 -> 12345 ==> 45
    crop_size = (int)pow((double)10, (double)(start_id - 1));                   // used with division /
    compare_part_len = (int)pow((double)10, (double)((end_id - start_id) + 1)); // used with remainder %

    for (int i = 1; i < stack_marker; i++)
    {
        int value_to_insert;
        int compared_value;
        int j;
        struct Node *value_to_insert_pt;

        j = i;
        value_to_insert = record_stack[i]->data;
        value_to_insert = (value_to_insert / crop_size) % compare_part_len;
        value_to_insert_pt = record_stack[i];

        while (j > 0 && (compared_value = ((record_stack[j - 1]->data) / crop_size) % compare_part_len) > value_to_insert)
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

void del_rec(int index)
{
    struct Node *head_pt = record_stack[index];
    struct Node *next_pt = record_stack[index]->next;

    while (next_pt != NULL)
    {
        free(head_pt);
        head_pt = next_pt;
        next_pt = next_pt->next;
    }

    free(head_pt);

    stack_marker--; // if succesfuly deleted decrement stack length marker

    // rearrange linearly
    for (int i = index; i < stack_marker; i++)
    {
        record_stack[i] = record_stack[i + 1];
    }
    if (index != stack_marker) // if removed element is not the last element
    {                          // remove the last element (index = stack_marker) manually
        head_pt = record_stack[stack_marker];
        next_pt = record_stack[stack_marker]->next;
        while (next_pt != NULL)
        {
            free(head_pt);
            head_pt = next_pt;
            next_pt = next_pt->next;
        }
        free(head_pt);
    }
}

void print_menu()
{
    // prints the main menu
    printf("<============MENU===========>");
    printf("1-Enter record with school number\n");
    printf("2-Display school numbers sorted by ID\n");
    printf("3-Display school numbers sorted by year\n");
    printf("4-Display school numbers sorted by the faculty codes\n");
    printf("5-Delete a record by school number\n");
    printf("6-Exit\n");
    printf("Enter choice: ");
}