#include "event_buffer_fsm.h"

/*--------------------------------------------*
 * Локальные типы данных
 *--------------------------------------------*/

/*--------------------------------------------*
 * Прототипы статических функций
 *--------------------------------------------*/

static bool initializeRingFSM(EventBufferFSM *prb, uint32_t size);
static bool ringFSMIsEmpty(const EventBufferFSM *prb);
static bool ringFSMIsFull(const EventBufferFSM *prb);
static uint32_t ringFSMItemCount(const EventBufferFSM *prb);
static uint32_t ringFSMCapacity(const EventBufferFSM *prb);
static bool addItemRingFSM(EventFSM item, EventBufferFSM *prb);
static bool getItemRingFSM(EventFSM *item, EventBufferFSM *prb);
static bool addItemRingFSMWithPriority(EventFSM item, EventBufferFSM *prb);
static void resetRingFSM(EventBufferFSM *prb);
static void setOverwriteModeRingFSM(EventBufferFSM *prb);
static void resetOverwriteModeRingFSM(EventBufferFSM *prb);
static void emptyTheRingFSM(EventBufferFSM *prb);
static EventFSM zeroing_item_fsm(void);
static void increment_head_fsm(EventBufferFSM *prb);
static void decrement_head_fsm(EventBufferFSM *prb);
static void increment_tail_fsm(EventBufferFSM *prb);
static void increment_items_fsm(EventBufferFSM *prb);
static void increment_counter_fsm(uint32_t *counter, EventBufferFSM *prb);
static void decrement_counter_fsm(uint32_t *counter, EventBufferFSM *prb);
static void shift_right_event_buffer_fsm(uint32_t position, EventBufferFSM *prb);
static uint32_t find_location_buffer_fsm(EventFSM item, EventBufferFSM *prb);

/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/

/*инициализация буфера событий*/
EventBufferFSM* initializeBufferFSM(uint32_t size)
{
    EventBufferFSM *buffer = (EventBufferFSM*)malloc(sizeof(EventBufferFSM));

    if (buffer == NULL)
        return NULL;

    if (initializeRingFSM(buffer, size))
        return buffer;

    return NULL;
}

/*освобождение выделенной памяти если она есть*/
void emptyBufferFSM(FSM *machine)
{
    if (machine == NULL || machine->event_queue == NULL)
        return;

    emptyTheRingFSM((EventBufferFSM*)machine->event_queue);
    free(machine->event_queue);
    machine->event_queue = NULL;
}

/*добавить событие в очередь событий автомата*/
bool pushEventQueue(FSM *machine, EventFSM event)
{
    if (machine == NULL || machine->event_queue == NULL)
        return false;

    if (event.priority == 0)
         return addItemRingFSM(event, (EventBufferFSM*)machine->event_queue);
         
    return addItemRingFSMWithPriority(event, (EventBufferFSM*)machine->event_queue);
}

/*взять событие из очереди событий автомата*/
bool popEventQueue(FSM *machine, EventFSM *event)
{
    if (machine == NULL || machine->event_queue == NULL || event == NULL)
        return false;

    return getItemRingFSM(event, (EventBufferFSM*)machine->event_queue);
}

/*проверка, является ли очередь событий пустой*/
bool queueEventIsEmpty(const FSM *machine)
{
    if (machine == NULL || machine->event_queue == NULL)
        return true;

    return ringFSMIsEmpty((EventBufferFSM*)machine->event_queue);
}

/*обработать все события из очереди автомата*/
uint32_t fsmProcessQueue(FSM *machine)
{
    if (machine == NULL || machine->event_queue == NULL)
        return 0;

    uint32_t number_event_handled = 0;
    EventFSM event;

    while (!queueEventIsEmpty(machine))
    {
        getItemRingFSM(&event, (EventBufferFSM*)machine->event_queue);
        dispatchFSM(machine, event);
        number_event_handled++;
    }

    return number_event_handled;
}

/*--------------------------------------------*
 * Статические функции (реализация)
 *--------------------------------------------*/

static bool initializeRingFSM(EventBufferFSM *prb, uint32_t size)
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

static bool ringFSMIsEmpty(const EventBufferFSM *prb)
{
    if (prb == NULL)
        return false;

    return prb->items == 0;
}

static bool ringFSMIsFull(const EventBufferFSM *prb)
{
    if (prb == NULL || prb->overwrite_mode)
        return false;

    return prb->items == prb->capacity;
}

static uint32_t ringFSMItemCount(const EventBufferFSM *prb)
{
    if (prb == NULL)
        return 0;

    return prb->items;
}

static uint32_t ringFSMCapacity(const EventBufferFSM *prb)
{
    if (prb == NULL)
        return 0;

    return prb->capacity; 
}

static bool addItemRingFSM(EventFSM item, EventBufferFSM *prb)
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

static bool getItemRingFSM(EventFSM *item, EventBufferFSM *prb)
{
    if (prb == NULL || item == NULL || prb->data == NULL || ringFSMIsEmpty(prb))
        return false;

    *item = prb->data[prb->tail];
    increment_tail_fsm(prb);
    prb->items--;

    return true;
}

static bool addItemRingFSMWithPriority(EventFSM item, EventBufferFSM *prb)
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

static void resetRingFSM(EventBufferFSM *prb)
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

static void setOverwriteModeRingFSM(EventBufferFSM *prb)
{
    if (prb == NULL)
        return;

    prb->overwrite_mode = true;
}

static void resetOverwriteModeRingFSM(EventBufferFSM *prb)
{
    if (prb == NULL)
        return;

    prb->overwrite_mode = false;
}

static void emptyTheRingFSM(EventBufferFSM *prb)
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

static EventFSM zeroing_item_fsm(void)
{
    EventFSM zero = {.event = 0, .priority = 0};

    return zero;
}

static void increment_tail_fsm(EventBufferFSM *prb)
{
    uint32_t tail = prb->tail + 1;

    prb->tail = tail == prb->capacity ? 0 : tail;
}

static void increment_head_fsm(EventBufferFSM *prb)
{
    uint32_t head = prb->head + 1;

    prb->head = head == prb->capacity ? 0 : head;
}

static void decrement_head_fsm(EventBufferFSM *prb)
{
    prb->head = prb->head == 0 ? prb->capacity - 1 : prb->head - 1;
}

static void increment_items_fsm(EventBufferFSM *prb)
{
    if (prb->items < prb->capacity)
        prb->items++;
}

static void increment_counter_fsm(uint32_t *counter, EventBufferFSM *prb)
{
    uint32_t count = *counter + 1;

    *counter = count == prb->capacity ? 0 : count;
}

static void decrement_counter_fsm(uint32_t *counter, EventBufferFSM *prb)
{
    *counter = *counter == 0 ? prb->capacity - 1 : *counter - 1;
}

static void shift_right_event_buffer_fsm(uint32_t position, EventBufferFSM *prb)
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

static uint32_t find_location_buffer_fsm(EventFSM item, EventBufferFSM *prb)
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