#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*
 * Verifica expressoes matemáticas,
 * isto é , se os parênteses
 * estão corretos nas operações
 */


typedef struct stack{
    // pilha para armazenar os parentesis na ordem que aparecem
    char parentesis;
    struct stack *next;
    int length;
}Stack;


Stack* push(Stack *st, char parentesis)
{
    // empilha itens a pilha
    Stack *pointer_to_top_of_stack;

    pointer_to_top_of_stack = malloc(sizeof (Stack));
    if(pointer_to_top_of_stack)
    {
           pointer_to_top_of_stack->parentesis = parentesis;
           pointer_to_top_of_stack->next = st;
           pointer_to_top_of_stack->length++;
        return pointer_to_top_of_stack;
    }
    else
    {
        printf("Insuficient memory");
    }
    return NULL;
}


void print(Stack *st)
{
    // exibe os itens da stack
    printf("\n###[ CONTENT OF STACK ]###\n");
    while(st)
    {
        printf(" %c ", st->parentesis);
        st = st->next;
    }
    printf("\n");
}


Stack* pop(Stack **st)
{
    // desempilha (ponteiro para ponteiro, pois desejo alterar o valor da pilha,
    // então, quero passagem por referencia
    if(*st != NULL)
    {
        Stack *top = *st;
        *st = top->next;
        top->length--;
        return top;
    }
    printf("Empty stack");
    return NULL;
}


char* trim(char *str)
{
    //remove espaços do inicio da string
    int count = 0;
    for(int i = 0; i < strlen(str); i++)
    {
        if(isspace(str[i]))
            continue;
        else
            count++;
    }
    //nova string para copia
    char *new_string = (char *) malloc(count);
    int i = 0, z = 0, x = 0;
    while(str[i] != '\0')
    {
        if(str[i + 1] == '\0')
            new_string[z + 1] = '\0';

        if(isspace(str[i]))
        {
           i++;
           continue;
        }else
        {
            new_string[z] = str[i];
            z++;
        }i++;
    }
    return new_string;
}


int read_expression(char *express)
{
    //lê expressao e analisa se os parêntesis estão corretos
    Stack *st = NULL, *st1, *st2;
    if(express[0] == '(' || express[0] == ')'){
        if(!isspace(express[0])){
            st = push(st, express[0]);
        }
    }
    for(int i = 1; i <= strlen(express); i++){
        if(express[i] == '(' || express[i] == ')'){
            if(!isspace(express[i])){
                st = push(st, express[i]);
            }
        }
    }

    int aux;
    if(st->length % 2 == 0){
        while(st)
        {
            st1 = pop(&st);
            aux = (int) st1->parentesis;
            st2 = pop(&st);
            if(aux <= (int) st2->parentesis){
                printf("Incorrect");
              return 0;
            }
        }
    }else{
        printf("\nIncorrect");
        return 0;
    }
    printf("\nCorrect");
    return 1;
}


int main() {
    Stack *st = NULL;
    char input[100];
    printf("Set your expression:");
    gets(input);
    puts(trim(input));
    read_expression(input);
    return 0;
}
