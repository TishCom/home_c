#include "FSM.h"

/*--------------------------------------------*
 * Локальные типы данных
 *--------------------------------------------*/


/*--------------------------------------------*
 * Прототипы статических функций
 *--------------------------------------------*/


/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/

/* РЕАЛИЗАЦИЯ ОСНОВНЫХ ФУНКЦИЙ КОНЕЧНОГО АВТОМАТА */

/*инициализация конечного автомата*/
bool initializeFSM(FSM *target_machine, FSMTemplateFill source_machine, uint32_t queue_size)
{
    if (target_machine == NULL
        || source_machine.state_table == NULL
        || source_machine.number_state < 1
        || source_machine.current_state >= source_machine.number_state
        || (source_machine.transition_table == NULL && source_machine.number_transition != 0)
        || (source_machine.transition_table != NULL && source_machine.number_transition == 0))
        return false;

    target_machine->event_queue = NULL;

    if (queue_size > 0)
    {
        target_machine->event_queue = (RingBufferFSM*)malloc(sizeof(RingBufferFSM));

        if (target_machine->event_queue == NULL)
            return false;

        if (!initializeRingFSM(target_machine->event_queue, queue_size))
        {
            free(target_machine->event_queue);
            target_machine->event_queue = NULL;
            return false;
        }
    }

    target_machine->current_state = source_machine.current_state;
    target_machine->state_table = source_machine.state_table;
    target_machine->number_state = source_machine.number_state;
    target_machine->transition_table = source_machine.transition_table;
    target_machine->number_transition = source_machine.number_transition;
    target_machine->context = source_machine.context;

    if (target_machine->state_table[target_machine->current_state].entry != NULL)
        target_machine->state_table[target_machine->current_state].entry(&target_machine->context);

    return true;
}

/*диспетчеризация конечного автомата*/
bool dispatchFSM(FSM *machine, EventFSM event)
{
    if (machine == NULL)
        return false;

    const Transition *kTrans = machine->transition_table;

    for (uint32_t i = 0; i < machine->number_transition; i++)
    {
        if (kTrans[i].current_state == machine->current_state && kTrans[i].event.event == event.event)
        {
            if (machine->state_table[machine->current_state].exit != NULL)
                machine->state_table[machine->current_state].exit(&machine->context);

            if (kTrans[i].action != NULL)
                kTrans[i].action(&machine->context);

            machine->current_state = kTrans[i].next_state;

            if (machine->state_table[machine->current_state].entry != NULL)
                machine->state_table[machine->current_state].entry(&machine->context);

            return true;
        }
    }

    if (machine->state_table[machine->current_state].default_action != NULL)
        machine->state_table[machine->current_state].default_action(&machine->context);

    return false;
}

/*получение текущего состояния конечного автомата*/
bool getStateFSM(const FSM *machine, State *current_state)
{
    if (machine == NULL || current_state == NULL)
        return false;

    *current_state = machine->current_state;

    return true;
}

/*установка нового состояния конечного автомата*/
bool setStateFSM(FSM *machine, State set_state)
{
    if (machine == NULL || set_state >= machine->number_state)
        return false;

    if (machine->state_table[machine->current_state].exit != NULL)
        machine->state_table[machine->current_state].exit(&machine->context);

    machine->current_state = set_state;

    if (machine->state_table[set_state].entry != NULL)
        machine->state_table[set_state].entry(&machine->context);

    return true;
}

/* РЕАЛИЗАЦИЯ ДОПОЛНИТЕЛЬНЫХ ФУНКЦИЙ */

/*освобождение выделенной памяти если она есть*/
void emptyTheFSM(FSM *machine)
{
    if (machine == NULL || machine->event_queue == NULL)
        return;

    emptyTheRingFSM(machine->event_queue);
    free(machine->event_queue);
    machine->event_queue = NULL;
}

/* РЕАЛИЗАЦИЯ ФУНКЦИЙ РАБОТЫ С ОЧЕРЕДЬЮ СОБЫТИЙ */

/*добавить событие в очередь событий автомата*/
bool pushEventQueue(FSM *machine, EventFSM event)
{
    if (machine == NULL || machine->event_queue == NULL)
        return false;

    return addItemRingFSMWithPriority(event, machine->event_queue);
}

/*взять событие из очереди событий автомата*/
bool popEventQueue(FSM *machine, EventFSM *event)
{
    if (machine == NULL || machine->event_queue == NULL || event == NULL)
        return false;

    return getItemRingFSM(event, machine->event_queue);
}

/*проверка, является ли очередь событий пустой*/
bool queueEventIsEmpty(const FSM *machine)
{
    if (machine == NULL || machine->event_queue == NULL)
        return true;

    return ringFSMIsEmpty(machine->event_queue);
}

/*обработать все события из очереди автомата*/
uint32_t fsmProcessQueue(FSM *machine)
{
    if (machine == NULL || machine->event_queue == NULL)
        return 0;

    uint32_t number_event_handled = 0;
    EventFSM event;

    while (!ringFSMIsEmpty(machine->event_queue))
    {
        getItemRingFSM(&event, machine->event_queue);
        dispatchFSM(machine, event);
        number_event_handled++;
    }

    return number_event_handled;
}

/*--------------------------------------------*
 * Вспомогательные публичные функции(изменяемые пользователем)
 *--------------------------------------------*/

/*--------------------------------------------*
 * Статические функции (реализация)
 *--------------------------------------------*/
