#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

/*--------------------------------------------*
 * Локальные типы данных
 *--------------------------------------------*/


/*--------------------------------------------*
 * Прототипы статических функций
 *--------------------------------------------*/

static bool isEqualItemQueue(ItemQueue verifiable, ItemQueue verification);
static bool makeNodeQueue(NodeQueue **node, ItemQueue *item);

/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/

/*инициализация очереди*/
void initializeQueue(Queue *pq)
{
    pq->front = NULL;
    pq->rear = NULL;
    pq->items = 0;
}

/*проверка, является ли очередь пустой*/
bool queueIsEmpty(const Queue *pq)
{
    return pq->items == 0;
}

/*проверка, является ли очередь полной*/
bool queueIsFull(const Queue *pq)
{
    return pq->items == MAXSIZE_QUEUE;
}

/*определяет количество элементов в очереди*/
uint32_t queueItemCount(const Queue *pq)
{
    return pq->items;
}

/*посмотреть первый элемент без удаления*/
bool peekFrontQueue(ItemQueue *item, const Queue *pq)
{
    if (queueIsEmpty(pq) || item == NULL)
        return false;

    *item = pq->front->item;

    return true;
}

/*посмотреть последний элемент без удаления*/
bool peekRearQueue(ItemQueue *item, const Queue *pq)
{
    if (queueIsEmpty(pq) || item == NULL)
        return false;

    *item = pq->rear->item;

    return true;
}

/*найти элемент по значению*/
bool findItemQueue(ItemQueue *item, const Queue *pq)
{
    if (queueIsEmpty(pq) || item == NULL)
        return false;

    NodeQueue *current_node = pq->front;

    while (current_node != NULL)
    {
        if (isEqualItemQueue(*item, current_node->item))
            return true;

        current_node = current_node->next;
    }
    
    return false;
}

/*добовление элемента в конец очереди*/
bool enqueue(ItemQueue *item, Queue *pq)
{
    if (queueIsFull(pq) || item == NULL)
        return false;

    NodeQueue *new_node;

    if (!makeNodeQueue(&new_node, item))
        return false;

    if (queueIsEmpty(pq))
    {
        pq->rear = pq->front = new_node;
    }
    else
    {
        pq->rear->next = new_node;
        pq->rear = new_node;
    }

    pq->items++;

    return true;
}

/*удаление элемента из начала очереди*/
bool dequeue(ItemQueue *item, Queue *pq)
{
    if (queueIsEmpty(pq) || item == NULL)
        return false;

    NodeQueue *front_node = pq->front;

    *item = pq->front->item;

    if (front_node->next == NULL)
        pq->front = pq->rear = NULL;
    else
        pq->front = pq->front->next;

    free(front_node);
    pq->items--;

    return true;
}

/*применение функции к каждому элементу очереди*/
bool traverseQueue(const Queue *pq, void (*pfun)(ItemQueue item))
{
    if (queueIsEmpty(pq) || pfun == NULL)
        return false;

    NodeQueue *current_node = pq->front;

    while (current_node != NULL)
    {
        pfun(current_node->item);

        current_node = current_node->next;
    }
    
    return true;
}

/*освобождение выделенной памяти если она есть*/
void emptyTheQueue(Queue *pq)
{
    if (queueIsEmpty(pq))
        return;

    ItemQueue my_item;

    while (!queueIsEmpty(pq))
        dequeue(&my_item, pq);

    pq->front = NULL;
    pq->rear = NULL;
    pq->items = 0;
}
 
/*--------------------------------------------*
 * Вспомогательные публичные функции(изменяемые пользователем)
 *--------------------------------------------*/

static bool isEqualItemQueue(ItemQueue verifiable, ItemQueue verification)
{
    return (verifiable.rating == verification.rating);
}

/*--------------------------------------------*
 * Статические функции (реализация)
 *--------------------------------------------*/

static bool makeNodeQueue(NodeQueue **node, ItemQueue *item)
{
    *node = (NodeQueue*)malloc(sizeof(NodeQueue));

    if (*node == NULL)
        return false;
    
    (*node)->next = NULL;
    (*node)->item = *item;

    return true;
}