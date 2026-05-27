#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "heap.h"

        /*прототипы локальных функций*/
/*--------------------------------------------*/

static void InOrder(const Node *ph_node, void (*pfun)(ItemHeap item));
static void LevelOrder(const Node *root, void (*pfun)(ItemHeap item));
Node* FindFreeSpaceHeap(const Heap *ph);
int ResetHighBit(int number);

        /*функции внешнего интерфейса*/
/*--------------------------------------------*/

/*инициализация кучи*/
void InitializeHeap(Heap *ph)
{
    ph->root = NULL;
    ph->items = 0;
}

/*проверка, является ли куча полной*/
bool HeapIsFull(const Heap *ph)
{
    return ph->items >= MAXHEAP;
}

/*проверка, является ли куча пустой*/
bool HeapIsEmpty(const Heap *ph)
{
    return ph->items == 0;
}

/*определяет количество элементов в куче*/
int HeapItemCount(const Heap *ph)
{
    return ph->items;
}

/*добовление элемента в кучу*/
bool PushHeap(const ItemHeap *item, Heap *ph)
{
    if (HeapIsFull(ph))
        return false;

    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL)
        return false;

    Node *new_parent = FindFreeSpaceHeap(ph);
    if (new_parent == NULL)
    {
        free(new_node);
        return false;
    }

    new_node->item = *item;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = new_parent;

    if (new_parent->left == NULL)
        new_parent->left = new_node;
    else
        new_parent->right = new_node;

    ph->items++;

    return true;
}

/*удаление элемента из верхушки кучи*/
bool PopHeap(ItemHeap *item, Heap *ph)
{
    if (HeapIsEmpty(ph))
        return false;
}

/*читает элемента из верхушки кучи не удаляя его*/
bool PeekHeap(ItemHeap *item, const Heap *ph)
{
    if (HeapIsEmpty(ph))
        return false;

    *item = ph->root->item;
    
    return true;
}

/*применение функции к каждому элементу кучи*/
void TraverseHeap(const Heap *ph, void (*pfun)(ItemHeap item))
{
    if (!HeapIsEmpty(ph))
        LevelOrder(ph->root, pfun);
}

/*опустошение кучи*/
void EmptyHeap(Heap *ph)
{

}

        /*определения локальных функций*/
/*--------------------------------------------*/

/* Внутренняя: обход лево центр право — стандарт для бинарного дерева поиска */
static void InOrder(const Node *root, void (*pfun)(ItemHeap item))
{
    if (root != NULL)
    {
        InOrder(root->left, pfun);
        pfun(root->item);
        InOrder(root->right, pfun);
    }
}

/* Внутренняя: обход по уровням (BFS) — стандарт для кучи */
static void LevelOrder(const Node *root, void (*pfun)(ItemHeap item))
{
    if (root == NULL) return;
    
    const Node *queue[MAXHEAP];
    const Node *current;
    size_t front = 0, rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear)
    {
        current = queue[front++];
        pfun(current->item);
        
        if (current->left)  queue[rear++] = current->left;
        if (current->right) queue[rear++] = current->right;
    }
}

Node* FindFreeSpaceHeap(const Heap *ph) 
{
    if (!ph || !ph->root || ph->items == 0) 
        return NULL;

    int idx = ph->items + 1;
    int mask = 1;
    Node *curr = ph->root;

    while (mask <= idx / 2) 
        mask <<= 1;
    mask >>= 1; 

    while (curr->right && curr->left && mask > 0) 
    {
        if (idx & mask)
            curr = curr->right;
        else
            curr = curr->left;
        mask >>= 1;
    }
    
    return curr;
}

int ResetHighBit(int number) 
{
    if (number <= 0)
        return number;

    int msb = 1;
    while (msb <= number / 2) 
        msb <<= 1;
    
    return number & ~msb; 
}

void SiftingHeap(const Heap *ph, Node pn)
{
    ItemHeap temp;
    Node my_node = pn;
    while (my_node.item < my_node.parent->item)
    {
        temp = my_node.parent->item;
        my_node.parent->item = my_node.item;
        my_node.item = temp;

    }
}