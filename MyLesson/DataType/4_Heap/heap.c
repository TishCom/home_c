#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "heap.h"

/*--------------------------------------------*
 * Локальные типы данных
 *--------------------------------------------*/


/*--------------------------------------------*
 * Прототипы статических функций
 *--------------------------------------------*/

static void level_order(const NodeHeap *root, void (*pfun)(ItemHeap *item));
static NodeHeap* find_free_space_heap(const Heap *ph);
static NodeHeap* find_last_node_heap(const Heap *ph) ;
static void sifting_heap_push(const Heap *ph, NodeHeap *pn, bool (*pfun)(NodeHeap *pn));
static bool make_node_heap(const Heap *ph, NodeHeap **new_node, ItemHeap item);
static bool to_up(NodeHeap *pn);
static bool to_down(NodeHeap *pn);
static bool need_move(NodeHeap *pn, bool *to_left);
static void sifting_heap_pop(const Heap *ph, NodeHeap *pn);
static int get_mask(int number_node);
static bool less_or_equal_item_heap(ItemHeap item1, ItemHeap item2);
static bool more_item_heap(ItemHeap item1, ItemHeap item2);
static void swap_item_heap(NodeHeap *a, NodeHeap *b);

/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/

/*инициализация кучи*/
void initializeHeap(Heap *ph)
{
    ph->root = NULL;
    ph->items = 0;
}

/*проверка, является ли куча полной*/
bool heapIsFull(const Heap *ph)
{
    return ph->items >= MAXHEAP;
}

/*проверка, является ли куча пустой*/
bool heapIsEmpty(const Heap *ph)
{
    return ph->items == 0;
}

/*определяет количество элементов в куче*/
int heapItemCount(const Heap *ph)
{
    return ph->items;
}

/*добовление элемента в кучу*/
bool pushHeap(const ItemHeap *item, Heap *ph)
{
    if (heapIsFull(ph))
        return false;

    NodeHeap *new_node;
    if (!make_node_heap(ph, &new_node, *item))
        return false;

    if (new_node->parent != NULL)
    {
        if (new_node->parent->left == NULL)
            new_node->parent->left = new_node;
        else
            new_node->parent->right = new_node;
    }
    else
    {
        ph->root = new_node;
    }

    ph->items++;

    sifting_heap_push(ph, new_node, to_up);

    return true;
}

/*удаление элемента из верхушки кучи*/
bool popHeap(ItemHeap *item, Heap *ph)
{
    if (heapIsEmpty(ph))
        return false;

    *item = ph->root->item;
    
    if (ph->items == 1) 
    {
        free(ph->root);
        ph->root = NULL;
        ph->items = 0;
        return true;
    }

    NodeHeap *last_node = find_last_node_heap(ph);
    
    ph->root->item = last_node->item;
    
    if (last_node->parent->left == last_node)
        last_node->parent->left = NULL;
    else
        last_node->parent->right = NULL;

    free(last_node);
    ph->items--;
    sifting_heap_pop(ph, ph->root);
    
    return true;
}

/*читает элемента из верхушки кучи не удаляя его*/
bool peekHeap(ItemHeap *item, const Heap *ph)
{
    if (heapIsEmpty(ph))
        return false;

    *item = ph->root->item;
    
    return true;
}

/*применение функции к каждому элементу кучи*/
void traverseHeap(const Heap *ph, void (*pfun)(ItemHeap *item))
{
    if (!heapIsEmpty(ph) && pfun != NULL)
        level_order(ph->root, pfun);
}

/*опустошение кучи*/
void emptyHeap(Heap *ph)
{
    ItemHeap item;

    while (popHeap(&item, ph))
        continue;
}

/*--------------------------------------------*
 * Вспомогательные публичные функции(изменяемые пользователем)
 *--------------------------------------------*/

static bool to_up(NodeHeap *pn)
{
    return pn->item < pn->parent->item;
}

static bool to_down(NodeHeap *pn)
{
    return pn->item > pn->parent->item;
}

static bool less_or_equal_item_heap(ItemHeap item1, ItemHeap item2)
{
    return item1 <= item2;
}

static bool more_item_heap(ItemHeap item1, ItemHeap item2)
{
    return item1 > item2;
}

/*--------------------------------------------*
 * Статические функции (реализация)
 *--------------------------------------------*/

static bool need_move(NodeHeap *pn, bool *to_left)
{
    if (pn->left == NULL && pn->right == NULL)
        return false;

    *to_left = false;
    
    if (pn->left == NULL && pn->right != NULL)
    {
        *to_left = false;
        return more_item_heap(pn->item, pn->right->item);
    }
    
    if (pn->right == NULL || less_or_equal_item_heap(pn->left->item, pn->right->item))
    {
        *to_left = true;
        return more_item_heap(pn->item, pn->left->item);
    }
    
    return more_item_heap(pn->item, pn->right->item);
}

static void in_order(const NodeHeap *root, void (*pfun)(ItemHeap item))
{
    if (root != NULL)
    {
        in_order(root->left, pfun);
        pfun(root->item);
        in_order(root->right, pfun);
    }
}

static void level_order(const NodeHeap *root, void (*pfun)(ItemHeap *item))
{
    if (root == NULL) return;
    
    const NodeHeap *queue[MAXHEAP];
    const NodeHeap *current;
    size_t front = 0, rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear)
    {
        current = queue[front++];
        
        if (current->left != NULL)
            queue[rear++] = current->left;
        if (current->right != NULL)
            queue[rear++] = current->right;

        pfun(&current->item);
    }
}

static NodeHeap* find_free_space_heap(const Heap *ph) 
{
    if (!ph || !ph->root || ph->items == 0) 
        return NULL;

    int mask = get_mask(ph->items);
    NodeHeap *curr = ph->root;

    while (curr->right && curr->left) 
    {
        if (ph->items & mask)
            curr = curr->right;
        else
            curr = curr->left;
        mask >>= 1;
    }
    
    return curr;
}

static NodeHeap* find_last_node_heap(const Heap *ph) 
{
    if (!ph || !ph->root || ph->items == 0) 
        return NULL;

    int mask = get_mask(ph->items);
    NodeHeap *last_node = ph->root;

    while (mask > 0) 
    {
        if (ph->items & mask) 
            last_node = last_node->right;
        else 
            last_node = last_node->left;
        mask >>= 1;
    }
    
    return last_node;
}

static int get_mask(int number_node)
{
    int mask = 1;

    while (mask <= number_node) 
        mask <<= 1;
    mask >>= 2;

    return mask;
}

static int reset_high_bit(int number) 
{
    if (number <= 0)
        return number;

    int msb = 1;
    while (msb <= number / 2) 
        msb <<= 1;
    
    return number & ~msb; 
}

static void sifting_heap_push(const Heap *ph, NodeHeap *pn, bool (*pfun)(NodeHeap *pn))
{
    if (heapIsEmpty(ph) || pn == NULL)
        return;

    NodeHeap *my_node = pn;

    while ((my_node->parent != NULL) && pfun(my_node))
    {
        swap_item_heap(my_node->parent, my_node);
        my_node = my_node->parent;
    }
}

static void sifting_heap_pop(const Heap *ph, NodeHeap *pn)
{
    if (heapIsEmpty(ph) || pn == NULL)
        return;

    NodeHeap *my_node = pn;
    bool to_left = false;

    while (need_move(my_node, &to_left))
    {
        if (to_left)
        {
            swap_item_heap(my_node, my_node->left);
            my_node = my_node->left;
        }
        else
        {
            swap_item_heap(my_node, my_node->right);
            my_node = my_node->right;
        }
    }
}

static void swap_item_heap(NodeHeap *a, NodeHeap *b)
{
    ItemHeap temp = a->item;
    a->item = b->item;
    b->item = temp;
}

static bool make_node_heap(const Heap *ph, NodeHeap **new_node, ItemHeap item)
{
    *new_node = (NodeHeap*)malloc(sizeof(NodeHeap));
    if (*new_node == NULL)
        return false;

    (*new_node)->item = item;
    (*new_node)->left = NULL;
    (*new_node)->right = NULL;

    NodeHeap *new_parent = find_free_space_heap(ph);
    if (new_parent == NULL)
        (*new_node)->parent = NULL;
    else    
        (*new_node)->parent = new_parent;
        
    return true;
}