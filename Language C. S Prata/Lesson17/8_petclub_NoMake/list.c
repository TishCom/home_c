#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

        /*прототип локальной функции*/
/*--------------------------------------------*/
static void CopyToNode(ItemList item, Node* pnode);

        /*функции внешнего интерфейса*/
/*--------------------------------------------*/

/*устанавливает список в пустое состояние*/
void InitializeList(List* plist)
{
    plist->head = NULL;
    plist->items = 0;
}

/*возвращает true если список пуст*/
bool ListIsEmpty(List* plist)
{
    if (plist->items == 0)
        return true;
    else
        return false;
}

/*возвращает true если список полон*/
bool ListIsFull(List* plist)
{
    if (plist->items >= TSIZE)
        return true;
    else    
        return false;
}

/*возвращает количество узлов*/
unsigned int ListItemCount(const List* plist)
{
    return plist->items;
}

/*создает узел для хранения элемента и добавляет его в конец*/
/*списка, указанного переменной plist(медленная реализация)*/
bool AddItemList(ItemList item, List* plist)
{
    Node* pnew;
    Node* scan = plist->head;

    pnew = (Node*)malloc(sizeof(Node));
    if (pnew == NULL)
        return false;

    CopyToNode(item, pnew);
    pnew->next = NULL;
    if (scan == NULL)
        plist->head = pnew;
    else
    {
        while (scan->next != NULL)
            scan = scan->next;
        scan->next = pnew;
    }

    return true;
}

/*посещает каждый узел и выполняет функцию указанную pfun*/
void TraverseList(const List* plist, void (*pfun)(ItemList item))
{
    Node* pnode = plist->head;

    while (pnode != NULL)
    {
        pfun(pnode->item);
        pnode = pnode->next;
    }
}

/*освобождает память выделенную функцией malloc()*/
/*и устанавливает указатель списка в NULL*/
void EmptyTheList(List* plist)
{
    InitializeList(plist);
}

        /*определение локальной функции*/
/*--------------------------------------------*/

/*копирует элемент в узел*/
static void CopyToNode(ItemList item, Node* pnode)
{
    pnode->item = item;
}