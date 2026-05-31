#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include "queue.h"

void myFunc(ItemQueue item);

int main(void)
{
    Queue my_queue;
    ItemQueue my_item = {.rating = 23};

    initializeQueue(&my_queue);

    if (queueIsEmpty(&my_queue))
        printf("empty\n");

    for (size_t i = 0; i < 40; i++)
    {
        enqueue(&my_item, &my_queue);
        my_item.rating++;
    }

    traverseQueue(&my_queue, myFunc);
    printf("\n");

    if (queueIsFull(&my_queue))
        printf("full\n");

    printf("%d - items\n", queueItemCount(&my_queue));
    peekFrontQueue(&my_item, &my_queue);
    printf("%d - peek front\n", my_item.rating);
    peekRearQueue(&my_item, &my_queue);
    printf("%d - peek rear\n", my_item.rating);
    my_item.rating = 43;
    printf("%d - find\n", findItemQueue(&my_item, &my_queue));
    dequeue(&my_item, &my_queue);
    printf("%d - dequeue\n", my_item.rating);

    traverseQueue(&my_queue, myFunc);

    emptyTheQueue(&my_queue);

    return 0;
}

void myFunc(ItemQueue item)
{
    printf("%d ", item.rating);
}