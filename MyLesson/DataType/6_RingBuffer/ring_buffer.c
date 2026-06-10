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
    
}

/*добавление элемента в кольцевой буфер*/
bool addItemRing(ItemRing item, RingBuffer *prb)
{
    
}

/*удаление элемента кольцевого буфера*/
bool deleteItemRing(ItemRing *item, RingBuffer *prb)
{
    
}

/*получить следующий элемент без извлечения(удаления)*/
bool peekRing(ItemRing *item, const RingBuffer *prb)
{
    
}

/*применение функции к каждому элементу кольцевого буфера*/
bool traverseRing(const RingBuffer *prb, void (*pfun)(ItemRing item))
{
    
}

/*освобождение выделенной памяти если она есть*/
void emptyTheRing(RingBuffer *prb)
{
    
}

/*очистка буфера без освобождения памяти*/
void resetRing(RingBuffer *prb)
{
    
}

/*активировать режим перезаписи старых элементов буфера новыми*/
void setOverwriteModeRing(RingBuffer *prb)
{
    
}

/*деактивировать режим перезаписи старых элементов буфера новыми*/
void resetOverwriteModeRing(RingBuffer *prb)
{

}

/*--------------------------------------------*
 * Вспомогательные публичные функции(изменяемые пользователем)
 *--------------------------------------------*/

/*--------------------------------------------*
 * Статические функции (реализация)
 *--------------------------------------------*/
