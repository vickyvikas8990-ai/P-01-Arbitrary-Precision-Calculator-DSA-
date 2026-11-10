#ifndef HEAD_H
#define HEAD_H
// #include"cal.h"
#include "head.h"
typedef struct node
{
    int data;
    struct node*next;
    struct node*prev;
}Dlist;
#define NEGATIVE -1
#define POSITIVE 2
#define SWAP 1
#define NOSWAP 0
typedef enum
{
    e_success,
    e_failure
} STATUS;

typedef struct {
    Dlist*head;
    Dlist*tail;
}Node;


/* To create the list for numbers */
STATUS create_list(Node* list, char* str);

/* Insert the element in the last pos */
STATUS insert_at_last(Node* list,int digit);

/* Insert the element in the first pos */
STATUS insert_at_first(Node* list,int digit);

/* Print the list */
void print_list(Dlist*head);

/* To decide which operation to be performed */
STATUS perform_operation(Node*list, Node*list2, Node* result, char* operator);

/* Addition operation */
STATUS addition(Node*list, Node*list2, Node*result);

/* Substraction operation */
STATUS subtraction( Node*list,Node*list2, Node* result);

/* Compare 2 numbers to tell which one is greater */
int list_compare(Node*list,Node*list2);

/* Multiplication operation */
STATUS multiplication(Node*list, Node*list2, Node* result);

/* Removes leading zeroes of number */
void remove_leading_zeroes(Node* list);

/* Delete all nodes of the list */
void clear_list(Node* list);

/* Division operation */
STATUS division(Node*list, Node*list2 , Node* result);
#endif

