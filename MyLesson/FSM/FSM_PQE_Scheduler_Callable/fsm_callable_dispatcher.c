#include "fsm_callable_dispatcher.h"

/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/

/* РЕАЛИЗАЦИЯ ФУНКЦИЙ ДИСПЕТЧЕРИЗАЦИИ С ПОДДЕРЖКОЙ ВЫЗЫВАЕМЫХ АВТОМАТОВ */

/*обработка одного события с автоматической проверкой завершения вызываемого автомата*/
bool fsmCallableDispatch(FSM *machine, EventFSM event)
{
    if (machine == NULL)
        return false;

    bool result = dispatchFSM(machine, event);
    FSMCallableData *data = (FSMCallableData*)machine->callable_data;

    if (result && fsmCallableDataIsInitialise(data)
        && machine->current_state == data->finish_state)
        fsmReturn(machine);

    return result;
}

/*обработка всех событий из очереди автомата с поддержкой вызываемых автоматов*/
uint32_t fsmProcessCallable(FSM *machine)
{
    if (machine == NULL)
        return 0;

    EventFSM event;
    uint32_t handling_event = 0;
    FSMCallableData *data = (FSMCallableData*)machine->callable_data;

    while (!queueEventIsEmpty(machine))
    {
        if (machine->scheduler_data != NULL
            && schedulerDataIsWaiting((FSMSchedulerData*)machine->scheduler_data))
            break;
        
        popEventQueue(machine, &event);
        fsmCallableDispatch(machine, event);
        handling_event++;
    }

    return handling_event;
}