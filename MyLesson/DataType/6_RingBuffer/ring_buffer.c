#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ring_buffer.h"

/*--------------------------------------------*
 * Локальные типы данных
 *--------------------------------------------*/

/*--------------------------------------------*
 * Прототипы статических функций
 *--------------------------------------------*/

static ItemRing zeroing(void);
static void increment_head(RingBuffer *prb);
static void increment_tail(RingBuffer *prb);
static void increment_items(RingBuffer *prb);
static void increment_counter(uint32_t *counter, RingBuffer *prb);

/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/
 
/*инициализация кольцевого буфера*/
bool initializeRing(RingBuffer *prb, uint32_t size)
{
    if (prb == NULL || size == 0)
        return false;

    prb->capacity = size;
    prb->head = prb->tail = 0;
    prb->items = 0;
    prb->overwrite_mode = false;
    prb->data = (ItemRing*)malloc(prb->capacity * sizeof(ItemRing));

    if (prb->data == NULL)
        return false;

    return true;
}

/*проверка, является ли кольцевой буфер пустым*/
bool ringIsEmpty(const RingBuffer *prb)
{
    if (prb == NULL)
        return false;

    return prb->items == 0;
}

/*проверка, является ли кольцевой буфер полным*/
bool ringIsFull(const RingBuffer *prb)
{
    if (prb == NULL || prb->overwrite_mode)
        return false;

    return prb->items == prb->capacity;
}

/*определяет количество элементов в кольцевом буфере*/
uint32_t ringItemCount(const RingBuffer *prb)
{
    if (prb == NULL)
        return 0;

    return prb->items;
}

/*определяет обьем памяти зарезервированный кольцевым буфером*/
uint32_t ringCapacity(const RingBuffer *prb)
{
    if (prb == NULL)
        return 0;

    return prb->capacity; 
}

/*добавление элемента в кольцевой буфер*/
bool addItemRing(ItemRing item, RingBuffer *prb)
{
    if (prb == NULL || prb->data == NULL || ringIsFull(prb))
        return false;

    prb->data[prb->head] = item;
    increment_head(prb);
    increment_items(prb);

    if (prb->items == prb->capacity && prb->overwrite_mode)
        increment_tail(prb);

    return true;
}

/*удаление элемента кольцевого буфера*/
bool getItemRing(ItemRing *item, RingBuffer *prb)
{
    if (prb == NULL || item == NULL || prb->data == NULL || ringIsEmpty(prb))
        return false;

    *item = prb->data[prb->tail];
    increment_tail(prb);
    prb->items--;

    return true;
}

/*получить следующий элемент без извлечения(удаления)*/
bool peekRing(ItemRing *item, const RingBuffer *prb)
{
    if (prb == NULL || item == NULL || ringIsEmpty(prb))
        return false;

    *item = prb->data[prb->tail];

    return true;
}

/*применение функции к каждому элементу кольцевого буфера*/
bool traverseRing(const RingBuffer *prb, void (*pfun)(ItemRing item))
{
    if (prb == NULL || pfun == NULL)
        return false;

    for (uint32_t i = prb->tail, y = 0; y < prb->items; increment_counter(&i, prb), y++)
        pfun(prb->data[i]);
    
    return true;
}

/*освобождение выделенной памяти если она есть*/
void emptyTheRing(RingBuffer *prb)
{
    if (prb == NULL)
        return;

    free(prb->data);
    prb->data = NULL;
    prb->capacity = 0;
    prb->items = 0;
    prb->head = 0;
    prb->tail = 0;
    prb->overwrite_mode = false;
}

/*очистка буфера без освобождения памяти*/
void resetRing(RingBuffer *prb)
{
    if (prb == NULL)
        return;

    ItemRing res = zeroing();

    for (uint32_t i = 0; i < prb->capacity; i++)
        prb->data[i] = res;

    prb->items = 0;
    prb->head = 0;
    prb->tail = 0;
}

/*активировать режим перезаписи старых элементов буфера новыми*/
void setOverwriteModeRing(RingBuffer *prb)
{
    if (prb == NULL)
        return;

    prb->overwrite_mode = true;
}

/*деактивировать режим перезаписи старых элементов буфера новыми*/
void resetOverwriteModeRing(RingBuffer *prb)
{
    if (prb == NULL)
        return;

    prb->overwrite_mode = false;
}

/*--------------------------------------------*
 * Вспомогательные публичные функции(изменяемые пользователем)
 *--------------------------------------------*/

static ItemRing zeroing(void)
{
    ItemRing zero = 0;

    return zero;
}

/*--------------------------------------------*
 * Статические функции (реализация)
 *--------------------------------------------*/

static void increment_tail(RingBuffer *prb)
{
    uint32_t tail = prb->tail + 1;

    prb->tail = tail == prb->capacity ? 0 : tail;
}

static void increment_head(RingBuffer *prb)
{
    uint32_t head = prb->head + 1;

    prb->head = head == prb->capacity ? 0 : head;
}

static void increment_items(RingBuffer *prb)
{
    if (prb->items < prb->capacity)
        prb->items++;
}

static void increment_counter(uint32_t *counter, RingBuffer *prb)
{
    uint32_t count = *counter + 1;

    *counter = count == prb->capacity ? 0 : count;
}