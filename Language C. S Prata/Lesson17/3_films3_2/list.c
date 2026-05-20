#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

        /*прототип локальной функции*/
/*--------------------------------------------*/
static void CopyToNode(Item item, Node* pnode);

        /*функции внешнего интерфейса*/
/*--------------------------------------------*/

/*устанавливает список в пустое состояние*/
void InitializeList(List* plist)
{
    for (int i = 0; i < MAXSIZE; i++)
    {
        strcpy(plist->entries[i].title, "");
        plist->entries[i].rating = 0;
    }
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
bool AddItem(Item item, List* plist)
{
    if (plist->items >= TSIZE)
        return false;

    plist->entries[plist->items++] = item;

    return true;
}

/*посещает каждый узел и выполняет функцию указанную pfun*/
void Traverse(const List* plist, void (*pfun)(Item item))
{
    for (int i = 0; i < plist->items; i++)
        pfun(plist->entries[i]);
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
static void CopyToNode(Item item, Node* pnode)
{
    pnode->item = item;
}