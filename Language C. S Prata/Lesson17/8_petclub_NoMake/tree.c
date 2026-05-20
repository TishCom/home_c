#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

           /*Локальные типы данных*/
/*--------------------------------------------*/
typedef struct pair
{
    Trnode *parent;
    Trnode *child;
} Pair;

        /*прототипы локальных функций*/
/*--------------------------------------------*/
static Trnode *MakeNode(const Item *pi);
static bool ToLeft(const Item *i1, const Item *i2);
static bool ToRight(const Item *i1, const Item *i2);
static void AddNode(Trnode *new_node, Trnode *root);
static void InOrder(const Trnode *root, void (*pfun)(Item item));
static Pair SeekItem(const Item *pi, const Tree *ptree);
static void DeleteNode(Trnode **ptr);
static void DeleteAllNodes(Trnode *ptr);

        /*функции внешнего интерфейса*/
/*--------------------------------------------*/

/*инициализация дерева пустым содержимым*/
void InitializeTree(Tree *ptree)
{
    ptree->root = NULL;
    ptree->size = 0;
}

/*проверка, является ли дерево пустым*/
bool TreeIsEmpty(const Tree *ptree)
{
    if (ptree->root == NULL)
        return true;
    else
        return false;
}

/*проверка, является ли дерево полным*/
bool TreeIsFull(const Tree *ptree)
{
    if (ptree->size == MAXITEMS)
        return true;
    else
        return false;
}

/*определяет количество элементов в дереве*/
int TreeItemCount(const Tree *ptree)
{
    return ptree->size;
}

/*добавление элемента к дереву*/
bool AddItem(const Item *pi, Tree *ptree)
{
    Trnode *new_node;

    if (TreeIsFull(ptree))
    {
        fprintf(stderr, "Дерево заполнено\n");
        return false;               // преждевременный возврат
    }
    if (SeekItem(pi, ptree).child != NULL)
    {
        fprintf(stderr, "Попытка добавить дублированный элемент\n");
        return false;               // преждевременный возврат
    }
    new_node = MakeNode(pi);        // указатель на новый узел
    if (new_node == NULL)
    {
        fprintf(stderr, "Не удалось создать узел\n");
        return false;               // преждевременный возврат
    }
    // успешное создание нового узла
    ptree->size++;

    if (ptree->root == NULL)        // случай 1: дерево пустое
    {
        ptree->root = new_node;     // новый узел становится корнем
    }
    else                            // случай 2: дерево не пустое
        AddNode(new_node, ptree->root); // добавление узла в дерево

    return true;                    // успешный возврат
}

/*поиск элемента в дереве*/
bool InTree(const Item *pi, const Tree *ptree)
{
    return (SeekItem(pi, ptree).child == NULL) ? false : true;
}

/*удаление элемента из дерева*/
bool DeleteItem(const Item *pi, Tree *ptree)
{
    Pair look;

    look = SeekItem(pi, ptree);
    if (look.child == NULL)
        return false;               // элемент не найден, удаление невозможно

    if (look.parent == NULL)        // удаление корневого узла
        DeleteNode(&ptree->root);
    else if (look.parent->left == look.child)
        DeleteNode(&look.parent->left);
    else
        DeleteNode(&look.parent->right);
    ptree->size--;

    return true;
}

/*применение функции pfun к каждому элементу дерева*/
void Traverse(const Tree *ptree, void (*pfun)(Item item))
{
    if (ptree != NULL)
        InOrder(ptree->root, pfun);
}

/*удаление всех элементов из дерева*/
void DeleteAll(Tree *ptree)
{
    if (ptree != NULL)
        DeleteAllNodes(ptree->root);
    ptree->root = NULL;
    ptree->size = 0;
}

    /*функции которые делает пользователь*/
/*--------------------------------------------*/

/*отсутствуют*/

  /*функции которые пользователь будет менять*/
/*--------------------------------------------*/

static bool ToLeft(const Item *i1, const Item *i2)
{
    if (strcmp(i1->petname, i2->petname) < 0)
        return true;
    else
        return false;
}

static bool ToRight(const Item *i1, const Item *i2)
{
    if (strcmp(i1->petname, i2->petname) > 0)
        return true;
    else
        return false;
}

        /*определения локальных функций*/
/*--------------------------------------------*/

static void InOrder(const Trnode *root, void (*pfun)(Item item))
{
    if (root != NULL)
    {
        InOrder(root->left, pfun);
        (*pfun)(root->item);
        InOrder(root->right, pfun);
    }
}

static void DeleteAllNodes(Trnode *root)
{
    Trnode *pright;

    if (root != NULL)
    {
        pright = root->right;
        DeleteAllNodes(root->left);
        free(root);
        DeleteAllNodes(pright);
    }
}

static void AddNode(Trnode *new_node, Trnode *root)
{
    if (ToLeft(&new_node->item, &root->item))
    {
        if (root->left == NULL)             // пустая левая ветвь
            root->left = new_node;          // сюда и помещается узел
        else
            AddNode(new_node, root->left);  // иначе обрабатывается левая ветвь
    }
    else if (ToRight(&new_node->item, &root->item))
    {
        if (root->right == NULL)            // пустая правая ветвь
            root->right = new_node;         // сюда и помещается узел
        else
            AddNode(new_node, root->right); // иначе обрабатывается правая ветвь
    }
    else                                    // дублированные элементы не должны
    {                                       // попадать сюда
        fprintf(stderr, "Ошибка в функции AddNode(): попытка добавить "
                        "дублированный элемент\n");
        exit(1);
    }
}

static Trnode *MakeNode(const Item *pi)
{
    Trnode *new_node;

    new_node = (Trnode *) malloc(sizeof(Trnode));
    if (new_node != NULL)
    {
        new_node->item = *pi;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

Pair SeekItem(const Item *pi, const Tree *ptree)
{
    Pair look;
    look.parent = NULL;
    look.child = ptree->root;

    if (look.child == NULL)
        return look;                        // преждевременный возврат

    while (look.child != NULL)
    {
        if (ToLeft(pi, &(look.child->item)))
        {
            look.parent = look.child;
            look.child = look.child->left;
        }
        else if (ToRight(pi, &(look.child->item)))
        {
            look.parent = look.child;
            look.child = look.child->right;
        }
        else        // если не левее и не правее, значит, совпадает
            break;  // look.child указывает на узел с искомым элементом
    }
    return look;    // возврат структуры
}

static void DeleteNode(Trnode **ptr)    // ptr — указатель на родительский
{                                       // указатель на удаляемый узел
    Trnode *temp;

    if ((*ptr)->left == NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->right;
        free(temp);
    }
    else if ((*ptr)->right == NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }
    else    // удаляемый узел имеет две дочерние ветви
    {
        // поиск правой ветви левой части дерева для присоединения
        for (temp = (*ptr)->left; temp->right != NULL; temp = temp->right)
            continue;
        temp->right = (*ptr)->right;
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }
}