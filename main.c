#include<stdio.h>
// #include<string.h>
#include<stdlib.h>
#include "head.h"
//  #include "cal.h"
int sign= POSITIVE;
int sign1 = POSITIVE;
int sign2 = POSITIVE;

int operand_count=0;

STATUS create_list(Node* list, char* str)
{
    int i=0;
    int num_sign = POSITIVE;

    // checking '+' or '-' as 1st character
    if(*str == '+')
        i++;
    else if(*str == '-'){
        num_sign = NEGATIVE;
        i++;
    }

    // assigning sign to specific operand
    if(operand_count == 0)
        sign1 = num_sign;
    else
        sign2 = num_sign;


    operand_count++;


    while(str[i] != '\0')
    {
        if(str[i] < '0' || str[i] > '9'){       // Validate that character is from 0-9
            printf("Error: Invalid number, Only digits 0-9 are allowed.\n\n");
            return e_failure;
        }

        int digit = str[i] - '0';       // Char to int conversion

        if(insert_at_last(list,digit) == e_failure){
            printf("Error: Unable to insert num1 in list 1\n");
            return e_failure;
        }

        i++;
    }

    return e_success;
}

void print_list(Dlist*head)
{
   if(head == NULL){
        printf("Info: List is empty\n");
        // return;
    }

    if(sign == NEGATIVE)
        printf("-");

    while(head)
    {
        printf("%d",head->data);

        head = head->next;
    }
    printf("\n");
}
STATUS perform_operation(Node*num1, Node*num2, Node* result, char* operator)
{
 switch(operator[0])
    {
        case '+':   if(sign1 == sign2){
                        sign = sign1;
                        return addition(num1,num2,result);
                    }
                    else if(sign1 != sign2){
                        // num1 > num2
                        if(list_compare(num1,num2) == NOSWAP){
                            sign = sign1;
                            return subtraction(num1,num2,result);
                        }
                        // num2 > num1
                        else{
                            sign = sign2;
                            return subtraction(num2,num1,result);
                        }
                    }

        

        case '-':   if(sign1 != sign2){
                        sign = sign1;
                        return addition(num1,num2,result);
                    }
                    // Both operand have same sign
                    else{
                        // num1 > num2 
                        if(list_compare(num1,num2) == NOSWAP){
                            sign = sign1;
                            return subtraction(num1,num2,result);
                        }
                        // num2 > num1
                        else{
                            sign = (sign1 == NEGATIVE) ? POSITIVE : NEGATIVE;
                            return subtraction(num2,num1,result);
                        }
                    }
                    
                    
        
        case 'x':   sign = (sign1 != sign2) ? NEGATIVE : POSITIVE;

                    // is num1 or num is 0 then sign = POSITIVE
                    if(num1->head->data == 0 && num1->head==num1->tail ||
                       num2->head->data == 0 && num2->head==num2->tail)
                    {
                        sign = POSITIVE;
                    }

                    return multiplication(num1,num2,result);


        case '/':   if(division(num1,num2,result) == e_failure)
                        return e_failure;

                    sign = (sign1 != sign2) ? NEGATIVE : POSITIVE;

                    if(result->head->data == 0 && result->head == result->tail)
                        sign = POSITIVE;

                    return e_success;
                    

        default : printf("Error: Invalid operator\n");
                  return e_failure;
    }
}
STATUS insert_at_last(Node* list,int digit)
{
    Dlist*newnode=malloc(sizeof(Dlist));
    if(newnode==NULL)
    {
        printf("memory allocation failed hear");
        return e_failure;
    }
    newnode->data=digit;
    newnode->next=NULL;
   if(list->head == NULL){
        list->head = newnode;
        list->tail = newnode;

        return e_success;
    }

    newnode->prev = list->tail;
    list->tail->next = newnode;
    list->tail = newnode;

    return e_success;
}
STATUS insert_at_first(Node*list,int digit)
{
    Dlist*Newnode=malloc(sizeof(Dlist));
    if(Newnode==NULL)
    {
        printf("memory alloction failef here:");
        return e_failure;
    }
    Newnode->data = digit;
    Newnode->prev = NULL;
    Newnode->next = NULL;

    if(list->head == NULL){
        list->head = Newnode;
        list->tail = Newnode;

        return e_success;
    }

    Newnode->next = list->head;
    list->head->prev = Newnode;
    list->head = Newnode;

    return e_success;
    
}
 STATUS addition(Node*list,Node*list2,Node*result)
 {
    // Node result;
    int digit,sum=0,carry=0;
    Dlist*temp1=list->tail;
    Dlist*temp2=list2->tail;
    while(temp1||temp2)
    {
        if(temp1 && temp2)
        {
         sum = temp1->data + temp2->data + carry;
         carry=sum/10;
         digit=sum%10;
        //  printf("%d",sum);
         insert_at_first(result,digit);
         temp1=temp1->prev;
         temp2=temp2->prev;
        }
        else if(temp1 && (temp2==NULL))
        {
        sum= temp1->data+carry;
         carry=sum/10;
         digit=sum%10;
         insert_at_first(result,digit);
         temp1=temp1->prev;
        }
        else if((temp1==NULL)&&temp2)
        {
            sum = temp2->data+carry;
         carry=sum/10;
         digit=sum%10;
         insert_at_first(result,digit);
         temp2=temp2->prev;
        }
    }
    if(carry)
    {
        insert_at_first(result,carry);
        carry=0;
    }
    return e_success;
 }
STATUS multiplication(Node*num1, Node*num2, Node* result)
 {
    Node result1 = {NULL,NULL};
    Node result2 = {NULL,NULL};

    Dlist* temp1;
    Dlist* temp2 = num2->tail;

    int carry = 0;
    int count = 0;
    int product;
    int digit;

    while(temp2)
    {
        temp1 = num1->tail;
        carry = 0;

        // Multiply every digit of num1 by one digit of num2
        while(temp1)
        {
            product = temp2->data * temp1->data + carry;

            carry = product / 10;
            digit = product % 10;

            if(count == 0){
                if(insert_at_first(&result1,digit) == e_failure){
                    printf("Error: Failed to insert digit into result1\n");
                    return e_failure;
                }
            }
            else{
                if(insert_at_first(&result2,digit) == e_failure){
                    printf("Error: Failed to insert digit into result2\n");
                    return e_failure;
                }
            }

            temp1 = temp1->prev;
        }

        // Store leftover carry
        if(carry){
            if(count == 0){
                if(insert_at_first(&result1,digit) == e_failure){
                    printf("Error: Failed to insert carry into result1\n");
                    return e_failure;
                }
            }
            else{
                if(insert_at_first(&result2,digit) == e_failure){
                    printf("Error: Failed to insert carry into result2\n");
                    return e_failure;
                }
            }
        }

        if(count == 0){
            temp2 = temp2->prev;
            count++;
            continue;
        }

        // Adding 0s in the last of the current partial product
        for(int i=0;i<count;i++){
            if(insert_at_last(&result2,0) == e_failure){
                printf("Error: Failed to insert 0 to result2\n");
                return e_failure;
            }
        }

        // Add result1 and result2 into result
        if(addition(&result1,&result2,result) == e_failure){
            printf("Error: Failed to add partial products\n");
            return e_failure;
        }

        // Free the nodes of result1 
        while(result1.head)
        {
            Dlist* temp = result1.head;
            result1.head = result1.head->next;
            free(temp);
        }
        result1.tail = NULL;

        //Free the nodes of result2
        while(result2.head)
        {
            Dlist* temp = result2.head;
            result2.head = result2.head->next;
            free(temp);
        }
        result2.tail = NULL;


        result1.head = result->head;
        result1.tail = result->tail;

        result->head = NULL;
        result->tail = NULL;

        temp2 = temp2->prev;
        count++;
    }

    // Copying the answer to result from result1
    result->head = result1.head;
    result->tail = result1.tail;

    result1.head = NULL;
    result1.tail = NULL;

    // remove leadin zeroes from result
    remove_leading_zeroes(result);

    return e_success;
}
void remove_leading_zeroes(Node* list)
{
    while(list->head && 
          list->head != list->tail &&       // False if only 1 node is present
          list->head->data == 0)
    {
        Dlist* temp = list->head;

        list->head = list->head->next;
        list->head->prev = NULL;

        free(temp);
    }
}

void clear_list(Node* list)
{
    // Deleting all nodes of list
    while(list->head)
    {
        Dlist* temp = list->head;

        list->head = list->head->next;

        free(temp);
    }

    list->tail = NULL;
}
int list_compare(Node*list,Node*list2)
 {
    Dlist* temp1 = list->head;
    Dlist* temp2 = list2->head;

    int count1 = 0;
    int count2 = 0;

    // Counting digits of num1
    while(temp1)
    {
        count1++;
        temp1 = temp1->next;
    }

    // Counting digits of num2
    while(temp2)
    {
        count2++;
        temp2 = temp2->next;
    }


    temp1 = list->head;
    temp2 = list2->head;

    // Checking which num is greater
    if(count1 < count2){
        sign = NEGATIVE;
        return SWAP;
    }

    else if(count1 > count2){
        sign = POSITIVE;
        return NOSWAP;
    }

    else if(count1 == count2)
    {
        /* Digit comparison */
        while(temp1 && temp2)
        {
            if(temp1->data < temp2->data){
                sign = NEGATIVE;
                return SWAP;
            }
            
            temp1 = temp1->next;
            temp2 = temp2->next;
        }

        sign = POSITIVE;
        return NOSWAP;
    }

    return NOSWAP;
}

 STATUS subtraction(Node*list,Node*list2,Node*result)
 {
    Dlist* temp1 = list->tail;
    Dlist* temp2 = list2->tail;

    int borrow = 0;
    int diff = 0;

    while(temp1 || temp2)
    {
        // When both num1 and num2 are valid
        if(temp1 && temp2)
        {
            diff = temp1->data - temp2->data - borrow;
            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }

        // When num2 have less digits
        else if(temp1 && (temp2 == NULL))
        {
            diff = temp1->data - borrow;
            temp1 = temp1->prev;
        }

        if(diff < 0){
            diff += 10;
            borrow = 1;
        }
        else
            borrow = 0;

        if(insert_at_first(result,diff) == e_failure){
            printf("Error: Failed to insert digit during subtraction\n");
            return e_failure;
        }
    }

    return e_success;
}

STATUS division(Node* num1, Node* num2, Node* result)
{
    Node current = {NULL,NULL};       
    Node sub_result = {NULL,NULL};    

    Dlist* temp1 = num1->head;
    Dlist* temp2 = num2->head;

    int count = 0;

    //Validating division by 0
    while(temp2 && temp2->data == 0)
        temp2 = temp2->next;
    

    if(temp2 == NULL){
        printf("Error: Division by zero is not allowed\n");
        return e_failure;
    }

    /* Take digits from num1 one by one */
    while(temp1)
    {
        if(insert_at_last(&current,temp1->data) == e_failure){
            printf("Error: Failed to insert digit into current\n");
            return e_failure;
        }

        // Removing leading zeroes from current
        remove_leading_zeroes(&current);        

        count = 0;

        // Repeating subtraction while current >= num2
        while(list_compare(&current,num2) == NOSWAP)
        {
            if(subtraction(&current,num2,&sub_result) == e_failure){
                printf("Error: Failed to do the subtraction in division\n");
                return e_failure;
            }

            clear_list(&current);               // to do

            // Update current with sub_result
            current.head = sub_result.head;
            current.tail = sub_result.tail;

            remove_leading_zeroes(&current);

            // Reset sub_result
            sub_result.head = NULL;
            sub_result.tail = NULL;

            count++;
        }

        // Store quotient(count) to result
        if(insert_at_last(result,count) == e_failure){
            printf("Error: Failed to insert quotient in division\n");
            return e_failure;
        }

        temp1 = temp1->next;
    }


    // Removing leading zeroes from quotient
    remove_leading_zeroes(result);

    clear_list(&current);
    clear_list(&sub_result);

    // sign = POSITIVE;
    return e_success;
}