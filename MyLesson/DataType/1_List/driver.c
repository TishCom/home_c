#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

void myFunc(ItemList item);

int main(void)
{
    List my_list;
    ItemList my_item = {.rating = 34};
    uint32_t index = 5;

    initializeList(&my_list);

    if (listIsEmpty(&my_list))
        printf("empty\n");

    for (size_t i = 0; i < 25; i++)
    {
        addItemList(my_item, &my_list);
        my_item.rating++;
    }

    if (listIsFull(&my_list))
        printf("full\n");
    
    printf("%d - items\n", listItemCount(&my_list));
    peekHeadList(&my_item, &my_list);
    printf("%d - peek\n", my_item.rating);
    peekTailList(&my_item, &my_list);
    printf("%d - tail\n", my_item.rating);
    getItemAtIndexList(&my_item, &my_list, index);
    printf("%d - %d item\n", my_item.rating, index);
    my_item.rating = 48;
    findItemList(my_item, &my_list, &index);
    printf("%d - %d item\n", my_item.rating, index);

    traverseList(&my_list, myFunc);

    emptyTheList(&my_list);

    return 0;
}

void myFunc(ItemList item)
{
    printf("%d ", item.rating);
}