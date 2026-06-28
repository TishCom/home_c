#include "ring_buffer_fsm.h"

/*--------------------------------------------*
 * Локальные типы данных
 *--------------------------------------------*/

/*--------------------------------------------*
 * Прототипы статических функций
 *--------------------------------------------*/

static EventFSM zeroing_item_fsm(void);
static void increment_head_fsm(RingBufferFSM *prb);
static void decrement_head_fsm(RingBufferFSM *prb);
static void increment_tail_fsm(RingBufferFSM *prb);
static void increment_items_fsm(RingBufferFSM *prb);
static void increment_counter_fsm(uint32_t *counter, RingBufferFSM *prb);
static void decrement_counter_fsm(uint32_t *counter, RingBufferFSM *prb);
static void shift_right_event_buffer_fsm(uint32_t position, RingBufferFSM *prb);
static uint32_t find_location_buffer_fsm(EventFSM item, RingBufferFSM *prb);

/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/
 
/*инициализация кольцевого буфера*/
bool initializeRingFSM(RingBufferFSM *prb, uint32_t size)
{
    if (prb == NULL || size == 0)
        return false;

    prb->capacity = size;
    prb->head = prb->tail = 0;
    prb->items = 0;
    prb->overwrite_mode = false;
    prb->data = (EventFSM*)calloc(prb->capacity, sizeof(EventFSM));

    if (prb->data == NULL)
        return false;

    return true;
}

/*проверка, является ли кольцевой буфер пустым*/
bool ringFSMIsEmpty(const RingBufferFSM *prb)
{
    if (prb == NULL)
        return false;

    return prb->items == 0;
}

/*проверка, является ли кольцевой буфер полным*/
bool ringFSMIsFull(const RingBufferFSM *prb)
{
    if (prb == NULL || prb->overwrite_mode)
        return false;

    return prb->items == prb->capacity;
}

/*определяет количество элементов в кольцевом буфере*/
uint32_t ringFSMItemCount(const RingBufferFSM *prb)
{
    if (prb == NULL)
        return 0;

    return prb->items;
}

/*определяет обьем памяти зарезервированный кольцевым буфером*/
uint32_t ringFSMCapacity(const RingBufferFSM *prb)
{
    if (prb == NULL)
        return 0;

    return prb->capacity; 
}

/*добавление элемента в кольцевой буфер*/
bool addItemRingFSM(EventFSM item, RingBufferFSM *prb)
{
    if (prb == NULL || prb->data == NULL || ringFSMIsFull(prb))
        return false;

    prb->data[prb->head] = item;
    increment_head_fsm(prb);
    increment_items_fsm(prb);

    if (prb->items == prb->capacity && prb->overwrite_mode)
        increment_tail_fsm(prb);

    return true;
}

/*удаление элемента кольцевого буфера*/
bool getItemRingFSM(EventFSM *item, RingBufferFSM *prb)
{
    if (prb == NULL || item == NULL || prb->data == NULL || ringFSMIsEmpty(prb))
        return false;

    *item = prb->data[prb->tail];
    increment_tail_fsm(prb);
    prb->items--;

    return true;
}

/*добавление элемента в кольцевой буфер в соответствии с его приоритетом*/
bool addItemRingFSMWithPriority(EventFSM item, RingBufferFSM *prb)
{
    if (prb == NULL || prb->data == NULL)
        return false;

    if (ringFSMIsEmpty(prb))
        return addItemRingFSM(item, prb);

    uint32_t position_for_item = find_location_buffer_fsm(item, prb);

    if (ringFSMIsFull(prb))
    {
        if (position_for_item == prb->head)
            return false;

        decrement_head_fsm(prb);
        prb->items--;
    }

    shift_right_event_buffer_fsm(position_for_item, prb);
    prb->data[position_for_item] = item;
    increment_head_fsm(prb);
    increment_items_fsm(prb);

    return true;
}

/*очистка буфера без освобождения памяти*/
void resetRingFSM(RingBufferFSM *prb)
{
    if (prb == NULL)
        return;

    EventFSM res = zeroing_item_fsm();

    for (uint32_t i = 0; i < prb->capacity; i++)
        prb->data[i] = res;

    prb->items = 0;
    prb->head = 0;
    prb->tail = 0;
}

/*активировать режим перезаписи старых элементов буфера новыми*/
void setOverwriteModeRingFSM(RingBufferFSM *prb)
{
    if (prb == NULL)
        return;

    prb->overwrite_mode = true;
}

/*деактивировать режим перезаписи старых элементов буфера новыми*/
void resetOverwriteModeRingFSM(RingBufferFSM *prb)
{
    if (prb == NULL)
        return;

    prb->overwrite_mode = false;
}

/*освобождение выделенной памяти если она есть*/
void emptyTheRingFSM(RingBufferFSM *prb)
{
    if (prb == NULL || prb->data == NULL)
        return;

    free(prb->data);
    prb->data = NULL;
    prb->capacity = 0;
    prb->items = 0;
    prb->head = 0;
    prb->tail = 0;
    prb->overwrite_mode = false;
}

/*--------------------------------------------*
 * Вспомогательные публичные функции(изменяемые пользователем)
 *--------------------------------------------*/

static EventFSM zeroing_item_fsm(void)
{
    EventFSM zero = {.event = 0, .priority = 0};

    return zero;
}

/*--------------------------------------------*
 * Статические функции (реализация)
 *--------------------------------------------*/

static void increment_tail_fsm(RingBufferFSM *prb)
{
    uint32_t tail = prb->tail + 1;

    prb->tail = tail == prb->capacity ? 0 : tail;
}

static void increment_head_fsm(RingBufferFSM *prb)
{
    uint32_t head = prb->head + 1;

    prb->head = head == prb->capacity ? 0 : head;
}

static void decrement_head_fsm(RingBufferFSM *prb)
{
    prb->head = prb->head == 0 ? prb->capacity - 1 : prb->head - 1;
}

static void increment_items_fsm(RingBufferFSM *prb)
{
    if (prb->items < prb->capacity)
        prb->items++;
}

static void increment_counter_fsm(uint32_t *counter, RingBufferFSM *prb)
{
    uint32_t count = *counter + 1;

    *counter = count == prb->capacity ? 0 : count;
}

static void decrement_counter_fsm(uint32_t *counter, RingBufferFSM *prb)
{
    *counter = *counter == 0 ? prb->capacity - 1 : *counter - 1;
}

static void shift_right_event_buffer_fsm(uint32_t position, RingBufferFSM *prb)
{
    if (position == prb->head)
        return;

    uint32_t counter1 = prb->head, counter2 = 0;

    decrement_counter_fsm(&counter1, prb);
    counter2 = counter1;
    decrement_counter_fsm(&counter2, prb);

    while (counter1 != position)
    {
        prb->data[counter1] = prb->data[counter2];
        decrement_counter_fsm(&counter1, prb);
        decrement_counter_fsm(&counter2, prb);
    }
}

static uint32_t find_location_buffer_fsm(EventFSM item, RingBufferFSM *prb)
{
    uint32_t position_for_item = prb->tail;

    for (uint32_t i = 0; i < prb->items; i++)
    {
        if (prb->data[position_for_item].priority < item.priority)
            break;
            
        increment_counter_fsm(&position_for_item, prb);
    }

    return position_for_item;
}