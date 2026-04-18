#include "LIFO_STECK.h"

void pushStack(stack **p, datatypeStack data)
{
    stack *ptmp = malloc(sizeof(stack));

    ptmp->value = data;
    ptmp->next = *p;
    *p = ptmp;
}

bool emptyStack(stack *p)
{
    return p == NULL;
}

datatypeStack popStack(stack **p)
{
    stack *ptmp = *p;
    datatypeStack c;

    if(emptyStack(*p))
        exit(1); 

    c = ptmp->value;
    *p = ptmp->next;

    free(ptmp);
    return c;
}

/* Пример
int main()
{
    stack *p = NULL; // Важно для корректной работы присвоить NULL
    for(int i = 1; i <= 5; i++)
        pushStack(&p,i);
    for(int i = 1; i <= 5; i++)
        printf("%d\n",popStack(&p)); // 5 4 3 2 1
    return 0;
}
*/