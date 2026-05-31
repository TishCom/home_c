#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/*--------------------------------------------*
 * Локальные типы данных
 *--------------------------------------------*/


/*--------------------------------------------*
 * Прототипы статических функций
 *--------------------------------------------*/

static bool makeNodeList(NodeList **new_node, ItemList item);
static bool isEqualItemList(ItemList verifiable, ItemList verification);

/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/

/*инициализация списка*/
void initializeList(List *plist)
{
    plist->head = NULL;
    plist->items = 0;
}

/*проверка, является ли список пустым*/
bool listIsEmpty(const List *plist)
{
    return plist->items == 0;
}

/*проверка, является ли список полным*/
bool listIsFull(const List *plist)
{
    return plist->items == MAXSIZE_LIST;
}

/*определяет количество элементов в списке*/
uint32_t listItemCount(const List *plist)
{
    return plist->items;
}

/*добовление элемента в конец списка*/
bool addItemList(ItemList item, List *plist)
{
    if (listIsFull(plist))
        return false;

    NodeList *new_node = NULL, *current_node = NULL;

    if (!makeNodeList(&new_node, item))
        return false;

    if (plist->head == NULL)
    {
        plist->head = new_node;
    }
    else
    {
        current_node = plist->head;
        while (current_node->next != NULL)
            current_node = current_node->next;

        current_node->next = new_node;
    }
        
    plist->items++;

    return true;
}

/*применение функции к каждому элементу списка*/
bool traverseList(const List *plist, void (*pfun)(ItemList item))
{
    if (listIsEmpty(plist))
        return false;

    NodeList *current_node = plist->head;

    while (current_node != NULL)
    {
        pfun(current_node->item);

        current_node = current_node->next;
    }
    
    return true;
}

/*освобождение выделенной памяти если она есть*/
void emptyTheList(List *plist)
{
    if (listIsEmpty(plist))
        return;

    NodeList *current_node = plist->head;
    NodeList *next_node = NULL;

    while (current_node != NULL)
    {
        next_node = current_node->next;

        free(current_node);

        current_node = next_node;
    }

    plist->head = NULL;
    plist->items = 0;
}

/*посмотреть первый элемент без удаления*/
bool peekHeadList(ItemList *item, const List *plist)
{
    if (listIsEmpty(plist) || item == NULL)
        return false;

    *item = plist->head->item;

    return true;
}

/*посмотреть последний элемент без удаления*/
bool peekTailList(ItemList *item, const List *plist)
{
    if (listIsEmpty(plist) || item == NULL)
        return false;

    NodeList *current_node = plist->head;

    while (current_node->next != NULL)
        current_node = current_node->next;
    
    *item = current_node->item;
    
    return true;
}

/*получить элемент по индексу (позиции)*/
bool getItemAtIndexList(ItemList *item, const List *plist, uint32_t index)
{
    if (listIsEmpty(plist) || item == NULL || index >= plist->items)
        return false;

    NodeList *current_node = plist->head;

    for (uint32_t i = 0; i < index; i++)
        current_node = current_node->next;
    
    *item = current_node->item;
    
    return true;
}

/*найти элемент по значению*/
bool findItemList(ItemList item, const List *plist, uint32_t *index)
{
    if (listIsEmpty(plist) || index == NULL)
        return false;

    NodeList *current_node = plist->head;
    *index = 0;

    while (current_node != NULL)
    {
        if (isEqualItemList(current_node->item, item))
            return true;

        current_node = current_node->next;
        (*index)++;
    }
        
    
    return false;
}

 
/*--------------------------------------------*
 * Вспомогательные публичные функции(изменяемые пользователем)
 *--------------------------------------------*/

static bool isEqualItemList(ItemList verifiable, ItemList verification)
{
    // return (verifiable.rating == verification.rating 
    //     && strncmp(verifiable.title, verification.title, TSIZE_LIST) == 0);
    return (verifiable.rating == verification.rating);
}

/*--------------------------------------------*
 * Статические функции (реализация)
 *--------------------------------------------*/

static bool makeNodeList(NodeList **new_node, ItemList item)
{
    *new_node = (NodeList*)malloc(sizeof(NodeList));

    if (*new_node == NULL)
        return false;
    
    (*new_node)->next = NULL;
    (*new_node)->item = item;
    
    return true;
}