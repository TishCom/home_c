#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*--------------------------------------------*
 * Локальные типы данных
 *--------------------------------------------*/


/*--------------------------------------------*
 * Прототипы статических функций
 *--------------------------------------------*/

static bool makeNodeList(NodeList **new_node);

/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/

/*инициализация списка*/
void initializeList(List* plist)
{
    plist->head = NULL;
    plist->items = 0;
}

/*проверка, является ли список пустым*/
bool listIsEmpty(List* plist)
{
    return plist->items == 0;
}

/*проверка, является ли список полным*/
bool listIsFull(List* plist)
{
    return plist->items == MAXSIZE_LIST;
}

/*определяет количество элементов в списке*/
unsigned int listItemCount(const List* plist)
{
    return plist->items;
}

/*добовление элемента в конец списка*/
bool addItemList(ItemList item, List* plist)
{
    if (listIsFull(plist))
        return false;

    NodeList *new_node, *current_node = plist->head;

    makeNodeList(&new_node);
    new_node->item = item;
    new_node->next = NULL;

    if (current_node != NULL)
    {
        while (current_node->next)
            current_node = current_node->next;
    }
        
    current_node = new_node;
    plist->items++;

    return true;
}

/*применение функции к каждому элементу списка*/
void traverseList(const List* plist, void (*pfun)(ItemList item))
{
    
}

/*освобождение выделенной памяти если она есть*/
void emptyTheList(List* plist)
{
    
}

 
/*--------------------------------------------*
 * Вспомогательные публичные функции
 *--------------------------------------------*/


/*--------------------------------------------*
 * Статические функции (реализация)
 *--------------------------------------------*/

static bool makeNodeList(NodeList **new_node)
{
    *new_node = (NodeList*)malloc(sizeof(NodeList));

    if (*new_node == NULL)
        return false;
    
    return true;
}