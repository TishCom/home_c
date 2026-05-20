#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

        /*функции внешнего интерфейса*/
/*--------------------------------------------*/

/*инициализация стека*/
void InitializeStack(Stack *ps)
{
    ps->top = NULL;
    ps->items = 0;
}

/*проверка, является ли стек полным*/
bool StackIsFull(const Stack *ps)
{
    return ps->items == MAXSTACK;
}

/*проверка, является ли стек пустым*/
bool StackIsEmpty(const Stack *ps)
{
    return ps->items == 0;
}

/*определяет количество элементов в стеке*/
int StackItemCount(const Stack *ps)
{
    return ps->items;
}

/*добовление элемента в верхушку стек*/
bool PushStack(const Item *item, Stack *ps)
{
    Node *new_node;

    if (StackIsFull(ps))
        return false;

    new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        fprintf(stderr, "Unable to allocate memory!\n");
        return false;
    }

    new_node->item = *item;
    new_node->previous = ps->top;
    ps->top = new_node;
    ps->items++;

    return true;
}

/*удаление элемента из верхушки стека*/
bool PopStack(Item *item, Stack *ps)
{
    Node *delete_node;

    if (StackIsEmpty(ps))
        return false;

    *item = ps->top->item;

    delete_node = ps->top;
    ps->top = ps->top->previous;
    free(delete_node);
    ps->items--;

    return true;
}

/*читает элемента из верхушки стека не удаляя его*/
bool PeekStack(Item *item, const Stack *ps)
{
    if (StackIsEmpty(ps))
        return false;

    *item = ps->top->item;

    return true;
}

/*посещает каждый узел и выполняет функцию указанную pfun*/
bool TraverseStack(const Stack *ps, void (*pfun)(Item item))
{
    Node *temp_node;

    if (StackIsEmpty(ps))
        return false;
    
    temp_node = ps->top;
    for (int i = 0; i < ps->items; i++)
    {
        pfun(temp_node->item);
        temp_node = temp_node->previous;
    }

    return true;
}

/*опустошение стека*/
void EmptyTheStack(Stack *ps)
{
    Item temp;

    while (!StackIsEmpty(ps))
        PopStack(&temp, ps);
}