#include "DYNAMIC_ARRAY.h"

void initDynamicArr(dynamicArr *da)
{
    da->size = 4;
    da->sp = 0;
    da->item = malloc((size_t)da->size * sizeof(datatypeDA));
}

void deleteDynamicArr(dynamicArr *da)
{
    free(da->item);
}

void pushDynamicArr(dynamicArr *da, datatypeDA value) 
{
    if (da->sp == da->size - 1) 
    {
        da->size = da->size * 2;
        if ((da->item = realloc(da->item, (size_t)da->size * sizeof(datatypeDA))) == NULL)
        {
            printf("fail realloc\n");
            return;
        }
    }
    da->item[da->sp++] = value;
}

datatypeDA popDynamicArr(dynamicArr *da)
{
    if (emptyDynamicArr(da))
    {
        printf("array empty");
        exit(1);
    }

    return da->item[--(da->sp)];
}

bool emptyDynamicArr(dynamicArr *da)
{
    return (da->sp < 1);
}

/*Пример
int main()
{
    dynamicArr da;
    int a, i;

    initDynamicArr(&da);
    do
    {
        scanf("%d", &a);
        pushDynamicArr(&da, a);
    }while (a != 0);

    for (i = 0; i < da.sp; i++)
        printf("%d ", da.item[i]);

    while (!empty_stack(&da))
    {
        a = popDynamicArr(&da);
        printf("%d ", a);
    }
    
    return 0;
}
*/