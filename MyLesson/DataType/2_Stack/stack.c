#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

        /*функции внешнего интерфейса*/
/*--------------------------------------------*/

/*инициализация стека*/
void initializeStack(Stack *ps)
{
    ps->top = NULL;
    ps->items = 0;
}

/*проверка, является ли стек полным*/
bool stackIsFull(const Stack *ps)
{
    return ps->items == MAXSTACK;
}

/*проверка, является ли стек пустым*/
bool stackIsEmpty(const Stack *ps)
{
    return ps->items == 0;
}

/*определяет количество элементов в стеке*/
int stackItemCount(const Stack *ps)
{
    return ps->items;
}

/*добовление элемента в верхушку стек*/
bool pushStack(const ItemStack *item, Stack *ps)
{
    NodeStack *new_node;

    if (stackIsFull(ps))
        return false;

    new_node = (NodeStack*)malloc(sizeof(NodeStack));
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
bool popStack(ItemStack *item, Stack *ps)
{
    NodeStack *delete_node;

    if (stackIsEmpty(ps))
        return false;

    *item = ps->top->item;

    delete_node = ps->top;
    ps->top = ps->top->previous;
    free(delete_node);
    ps->items--;

    return true;
}

/*читает элемента из верхушки стека не удаляя его*/
bool peekStack(ItemStack *item, const Stack *ps)
{
    if (stackIsEmpty(ps))
        return false;

    *item = ps->top->item;

    return true;
}

/*посещает каждый узел и выполняет функцию указанную pfun*/
bool traverseStack(const Stack *ps, void (*pfun)(ItemStack item))
{
    NodeStack *temp_node;

    if (stackIsEmpty(ps))
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
void emptyTheStack(Stack *ps)
{
    ItemStack temp;

    while (!stackIsEmpty(ps))
        popStack(&temp, ps);
}