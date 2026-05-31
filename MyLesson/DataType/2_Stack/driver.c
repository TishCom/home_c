#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include "stack.h"

void myFunc(ItemStack item);

int main(void)
{
    Stack my_stack;
    ItemStack my_item = 'a';
    uint32_t index = 5;

    initializeStack(&my_stack);

    if (stackIsEmpty(&my_stack))
        printf("Empty\n");

    for (size_t i = 0; i < 26; i++)
    {
        pushStack(&my_item, &my_stack);
        my_item++;
    }

    if (stackIsFull(&my_stack))
        printf("full\n");

    printf("%d - items\n", stackItemCount(&my_stack));
    
    traverseStack(&my_stack, myFunc);
    printf("\n");
    popStack(&my_item, &my_stack);
    printf("%c - pop\n", my_item);
    traverseStack(&my_stack, myFunc);
    printf("\n");
    peekStack(&my_item, &my_stack);
    printf("%c - peek\n", my_item);
    traverseStack(&my_stack, myFunc);
    printf("\n");

    emptyTheStack(&my_stack);

    return 0;
}

void myFunc(ItemStack item)
{
    printf("%c ", item);
}