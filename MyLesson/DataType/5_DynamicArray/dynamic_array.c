#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_array.h"

/*--------------------------------------------*
 * Локальные типы данных
 *--------------------------------------------*/

/*--------------------------------------------*
 * Прототипы статических функций
 *--------------------------------------------*/

static void shift_left_array(ItemArray *arr, uint32_t elements_to_shift);
static void shift_right_array(ItemArray *arr, uint32_t elements_to_shift);
static bool extend_array_capacity(DynamicArray *parr);
static bool is_data_allocated(DynamicArray *parr);

static bool item_equals_array(ItemArray a, ItemArray b);
static bool item_greater_array(ItemArray a, ItemArray b);
static bool item_less_array(ItemArray a, ItemArray b);
static bool less_or_equal_item_array(ItemArray a, ItemArray b);
static bool more_or_equal_item_array(ItemArray a, ItemArray b);
static int item_compare_descending(const void *a, const void *b);
static int item_compare_ascending(const void *a, const void *b);

/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/
 
/*инициализация динамического массива*/
void initializeArray(DynamicArray *parr)
{
    parr->capacity = INITIAL_CAPACITY;
    parr->items = 0;
    parr->data = (ItemArray*)malloc(parr->capacity * sizeof(ItemArray));
}

/*проверка, является ли динамический массив пустым*/
bool arrayIsEmpty(const DynamicArray *parr)
{
    return (parr->items == 0) || (parr->data == NULL);
}

/*проверка, является ли динамический массив полным*/
bool arrayIsFull(const DynamicArray *parr)
{
    return parr->items >= MAXSIZE_ARRAY;
}

/*определяет количество элементов в динамическом массиве*/
uint32_t arrayItemCount(const DynamicArray *parr)
{
    return parr->items;
}

/*получить элемент по индексу (позиции)*/
bool getItemAtIndexArray(ItemArray *item, const DynamicArray *parr, uint32_t index)
{
    if (parr->items < index + 1 || item == NULL || parr == NULL || !is_data_allocated(parr))
        return false;

    *item = parr->data[index];

    return true;
}

/*добавить элемент по индексу (позиции)*/
bool addItemAtIndexArray(ItemArray item, DynamicArray *parr, uint32_t index)
{
    if (parr == NULL || index > parr->items || arrayIsFull(parr) || !is_data_allocated(parr))
        return false;

    if (parr->items == parr->capacity)
    {
        if (!extend_array_capacity(parr))
            return false;
    }

    shift_right_array(parr->data + index, parr->items - index);
    parr->data[index] = item;
    parr->items++;

    return true;
}

/*найти элемент по значению*/
bool findItemArray(ItemArray item, const DynamicArray *parr, uint32_t *index)
{
    if (parr == NULL || arrayIsEmpty(parr) || index == NULL || !is_data_allocated(parr))
        return false;

    for (uint32_t i = 0; i < parr->items; i++)
    {
        if (item_equals_array(item, parr->data[i]))
        {
            *index = i;
            return true;
        }
    }
    
    return false;
}

/*изменение элемента по индексу*/
bool setItemAtIndexArray(ItemArray item, DynamicArray *parr, uint32_t index)
{
    if (parr == NULL || index >= parr->items || !is_data_allocated(parr))
        return false;

    parr->data[index] = item;

    return true;
}

/*добавление элемента в конец динамического массива*/
bool addItemArray(ItemArray item, DynamicArray *parr)
{
    return addItemAtIndexArray(item, parr, parr->items);
}

/*удаление элемента по индексу*/
bool deleteItemArray(ItemArray *item, DynamicArray *parr, uint32_t index)
{
    if (parr == NULL || arrayIsEmpty(parr) || index >= parr->items || !is_data_allocated(parr))
        return false;

    *item = parr->data[index];
    shift_left_array(parr->data + index, parr->items - index - 1);
    parr->items--;

    return true;
}

/*применение функции к каждому элементу динамического массива*/
bool traverseArray(const DynamicArray *parr, void (*pfun)(ItemArray item))
{
    if (parr == NULL || arrayIsEmpty(parr) || pfun == NULL)
        return false;

    for (uint32_t i = 0; i < parr->items; i++)
        pfun(parr->data[i]);
    
    return true;
}

/*освобождение выделенной памяти если она есть*/
void emptyTheArray(DynamicArray *parr)
{
    if (parr == NULL || arrayIsEmpty(parr))
        return;

    free(parr->data);
    parr->data = NULL;
    parr->items = 0;
    parr->capacity = 0;
}

/*сортирует массив*/
void sortArray(DynamicArray *parr, int (*compar)(const void *, const void *))
{
    if (parr == NULL || arrayIsEmpty(parr) || compar == NULL)
        return;

    qsort(parr->data, parr->items, sizeof(ItemArray), compar);
}

/*сортирует массив по возрастанию*/
void sortAscendingArray(DynamicArray *parr)
{
    sortArray(parr, item_compare_ascending);
}

/*сортирует массив по убыванию*/
void sortDescendingArray(DynamicArray *parr)
{
    sortArray(parr, item_compare_descending);
}

/*--------------------------------------------*
 * Вспомогательные публичные функции(изменяемые пользователем)
 *--------------------------------------------*/

static bool item_equals_array(ItemArray a, ItemArray b)
{
    return a == b;
}

static bool item_greater_array(ItemArray a, ItemArray b)
{
    return a > b;
}

static bool item_less_array(ItemArray a, ItemArray b)
{
    return a < b;
}

static bool less_or_equal_item_array(ItemArray a, ItemArray b)
{
    return a <= b;
}

static bool more_or_equal_item_array(ItemArray a, ItemArray b)
{
    return a >= b;
}

/*--------------------------------------------*
 * Статические функции (реализация)
 *--------------------------------------------*/

static int item_compare_ascending(const void *a, const void *b)
{
    ItemArray *a_loc = (ItemArray*)a;
    ItemArray *b_loc = (ItemArray*)b;

    if (item_less_array(*a_loc, *b_loc))
        return -1;
    else if (item_equals_array(*a_loc, *b_loc))
        return 0;
    
    return 1;
}

static int item_compare_descending(const void *a, const void *b)
{
    ItemArray *a_loc = (ItemArray*)a;
    ItemArray *b_loc = (ItemArray*)b;

    if (item_less_array(*a_loc, *b_loc))
        return 1;
    else if (item_equals_array(*a_loc, *b_loc))
        return 0;
    
    return -1;
}

static void shift_right_array(ItemArray *arr, uint32_t elements_to_shift)
{
    if (arr == NULL)
        return;

    for (uint32_t i = elements_to_shift; i > 0; i--)
        arr[i] = arr[i - 1];
}

static void shift_left_array(ItemArray *arr, uint32_t elements_to_shift)
{
    if (arr == NULL)
        return;

    for (uint32_t i = 0; i < elements_to_shift; i++)
        arr[i] = arr[i + 1];
}

static bool extend_array_capacity(DynamicArray *parr)
{
    if (arrayIsEmpty(parr))
        return false;

    ItemArray *temp_array = (ItemArray*)realloc(parr->data,
        (parr->capacity + INCREMENT_CAPACITY) * sizeof(*parr->data));

    if (temp_array == NULL)
        return false;

    parr->capacity += INCREMENT_CAPACITY;
    parr->data = temp_array;
    return true;
}

static bool is_data_allocated(DynamicArray *parr)
{
    return parr->data != NULL;
}