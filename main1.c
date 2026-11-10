#include<stdio.h>
#include "head.h"
int main(int argc,char*argv[])
{
     Node list ={NULL,NULL};
     Node list2 ={ NULL,NULL};
     Node result ={ NULL,NULL};
    //  Node head;
    //  Dlist head=list;
   if (argc != 4)
{
    printf("Error: Invalid number of arguments.\n");
    printf("Usage: ./a.out <operand1> <operator> <operand2>\n");
    printf("Example: ./a.out 123 + 456\n");
    return e_failure;
}

  if(create_list(&list,argv[1]) == e_failure){
        printf("Error: Unable to create List 1\n");
        return e_failure;
    }

    /* Create List 2 */
    if(create_list(&list2,argv[3]) == e_failure){
        printf("Error: Unable to create List 2\n");
        return e_failure;
    }

    // print_list(num1.head);
    // print_list(num2.head);

    if(perform_operation(&list,&list2,&result,argv[2]) == e_success){
        print_list(result.head);
    }
    else{
        printf("Error: Unable to perform operation\n");
        return e_failure;
    }

}