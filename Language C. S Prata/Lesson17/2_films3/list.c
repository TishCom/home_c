#include <stdio.h>
#include <stdlib.h>
#include "list.h"

        /*прототип локальной функции*/
/*--------------------------------------------*/
static void CopyToNode(Item item, Node* pnode);

        /*функции внешнего интерфейса*/
/*--------------------------------------------*/

/*устанавливает список в пустое состояние*/
void InitializeList(List* plist)
{
    plist->head = (Node*)NULL;
    plist->end = (Node*)NULL;
}

/*возвращает true если список пуст*/
bool ListIsEmpty(List* plist)
{
    if (plist->head == NULL)
        return true;
    else
        return false;
}

/*возвращает true если список полон*/
bool ListIsFull(List* plist)
{
    Node* pt;
    bool full;

    pt = (Node*)malloc(sizeof(Node));
    if (pt == NULL)
        full = true;
    else    
        full = false;
    free(pt);

    return full;
}

/*возвращает количество узлов*/
unsigned int ListItemCount(const List* plist)
{
    unsigned int count = 0;
    Node* pnode = plist->head;

    while (pnode != NULL)
    {
        count++;
        pnode = pnode->next;
    }
    
    return count;
}

/*создает узел для хранения элемента и добавляет его в конец*/
/*списка, указанного переменной plist(медленная реализация)*/
bool AddItem(Item item, List* plist)
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
        plist->end = scan->next = pnew;
    }

    return true;
}

/*посещает каждый узел и выполняет функцию указанную pfun*/
void Traverse(const List* plist, void (*pfun)(Item item))
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
    Node* psave;

    while (plist->head != NULL)
    {
        psave = plist->head->next;
        free(plist->head);
        plist->head = psave;
    }
}

        /*определение локальной функции*/
/*--------------------------------------------*/

/*копирует элемент в узел*/
static void CopyToNode(Item item, Node* pnode)
{
    pnode->item = item;
}