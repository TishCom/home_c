#include "fsm_callable.h"

/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/

/* РЕАЛИЗАЦИЯ ФУНКЦИЙ УПРАВЛЕНИЯ ЖИЗНЕННЫМ ЦИКЛОМ */

/*оформление данных для вызываемого автомта*/
FSMCallableData* fsmCallableDataCreate(FSMCallableData template_callable_fsm)
{
    FSMCallableData* data = (FSMCallableData*)malloc(sizeof(FSMCallableData));
    if (data == NULL)
        return NULL;

    data->caller = template_callable_fsm.caller;
    data->return_state = template_callable_fsm.return_state;
    data->finish_state = template_callable_fsm.finish_state;
    data->start_state = template_callable_fsm.start_state;
    data->is_called = template_callable_fsm.is_called;
    data->is_finished = template_callable_fsm.is_finished;

    return data;
}

/*освобождение памяти выделенной для данных необходимых для вызываемого автомта*/
void fsmCallableDataDestroy(FSMCallableData *data)
{
    if (!fsmCallableDataIsInitialise(data))
        return;

    data->caller->callable_data = NULL;
    free(data);
}

/*проверка, являются ли данные необходимые для вызываемого автомта инициализироваными*/
bool fsmCallableDataIsInitialise(const FSMCallableData *data)
{
    return data != NULL && data->caller != NULL;
}

/* РЕАЛИЗАЦИЯ ФУНКЦИЙ ДОСТУПА К ПОЛЯМ */

/*установка адреса вызывающего автомата*/
void fsmCallableDataSetCaller(FSMCallableData *data, FSM *caller)
{
    if (data == NULL)
        return;

    data->caller = caller;
}

/*получение адреса вызывающего автомата*/
FSM* fsmCallableDataGetCaller(const FSMCallableData *data)
{
    if (!fsmCallableDataIsInitialise(data))
        return NULL;

    return data->caller;
}

/*установка значения состояния в которое нужно перейти в родительском автомате после завершения дочернего*/
void fsmCallableDataSetReturnState(FSMCallableData *data, State return_state)
{
    if (data == NULL)
        return;

    data->return_state = return_state;
}

/*получение значения состояния в которое нужно перейти в родительском автомате после завершения дочернего*/
bool fsmCallableDataGetReturnState(const FSMCallableData *data, State *state)
{
    if (!fsmCallableDataIsInitialise(data))
        return false;

    *state = data->return_state;

    return true;
}

/*установка значения конечного состояния дочернего автомата*/
void fsmCallableDataSetFinishState(FSMCallableData *data, State finish_state)
{
    if (data == NULL)
        return;

    data->finish_state = finish_state;
}

/*получение значения конечного состояния дочернего автомата*/
bool fsmCallableDataGetFinishState(const FSMCallableData *data, State *state)
{
    if (!fsmCallableDataIsInitialise(data))
        return false;

    *state = data->finish_state;

    return true;
}

/*установка значения ночального состояния дочернего автомата*/
void fsmCallableDataSetStartState(FSMCallableData *data, State start_state)
{
    if (data == NULL)
        return;

    data->start_state = start_state;
}

/*получение значения ночального состояния дочернего автомата*/
bool fsmCallableDataGetStartState(const FSMCallableData *data, State *state)
{
    if (!fsmCallableDataIsInitialise(data))
        return false;

    *state = data->start_state;

    return true;
}

/*устанавка указанного автомат как вызыванный*/
void fsmCallableDataSetCalled(FSMCallableData *data)
{
    if (data == NULL)
        return;

    data->is_called = true;
}

/*устанавка указанного автомат как не вызыванный*/
void fsmCallableDataResetCalled(FSMCallableData *data)
{
    if (data == NULL)
        return;

    data->is_called = false;
}

/*проверка, является ли автомат вызванным*/
bool fsmCallableDataIsCalled(const FSMCallableData *data)
{
    if (!fsmCallableDataIsInitialise(data))
        return false;

    return data->is_called;
}

/*устанавка указанного автомат как завершившего работу*/
void fsmCallableDataSetFinished(FSMCallableData *data)
{
    if (data == NULL)
        return;

    data->is_finished = true;
}

/*устанавка указанного автомат как работайющий*/
void fsmCallableDataResetFinished(FSMCallableData *data)
{
    if (data == NULL)
        return;

    data->is_finished = false;
}

/*проверка, является ли автомат работающим*/
bool fsmCallableDataIsFinished(const FSMCallableData *data)
{
    if (!fsmCallableDataIsInitialise(data))
        return false;

    return data->is_finished;
}

/* РЕАЛИЗАЦИЯ ОСНОВНЫХ ФУНКЦИЙ */

/*проверка, является ли автомат работающим*/
bool fsmIsFinished(const FSM *machine)
{
    if (machine == NULL)
        return false;

    return fsmCallableDataIsFinished((FSMCallableData*)machine->callable_data);
}

/*проверка, является ли автомат вызванным*/
bool fsmIsCalled(const FSM *machine)
{
    if (machine == NULL)
        return false;
        
    return fsmCallableDataIsCalled((FSMCallableData*)machine->callable_data);
}

/*вызвать автомат как подпрограмму*/
bool fsmCall(FSM *callee, FSM *caller, State finish_state, State return_state)
{
    if (callee == NULL || caller == NULL || callee->callable_data == NULL
        || caller->scheduler_data == NULL)
        return false;

    FSMCallableData *data = (FSMCallableData*)callee->callable_data;

    if (fsmCallableDataIsCalled(data))
        return false;

    fsmCallableDataSetCaller(data, caller);
    fsmCallableDataSetReturnState(data, return_state);
    fsmCallableDataSetFinishState(data, finish_state);
    fsmCallableDataSetCalled(data);
    fsmCallableDataResetFinished(data);
    schedulerDataSetWaiting((FSMSchedulerData*)caller->scheduler_data);

    return fsmReset(callee);
}

/*принудительно завершить вызываемый автомат и вернуть управление вызывающему*/
void fsmReturn(FSM *machine)
{
    if (machine == NULL || !fsmCallableDataIsInitialise((FSMCallableData*)machine->callable_data))
        return;

    FSMCallableData *data = (FSMCallableData*)machine->callable_data;
    EventFSM dummy;

    fsmCallableDataResetCalled(data);
    fsmCallableDataSetFinished(data);

    schedulerDataResetWaiting((FSMSchedulerData*)(data->caller->scheduler_data));
    setStateFSM(data->caller, data->return_state);

    while (!queueEventIsEmpty(machine))
        popEventQueue(machine, &dummy);
}

/*сбросить вызываемый автомат в начальное состояние (с вызовом exit/entry)*/
bool fsmReset(FSM *machine)
{
    if (machine == NULL || !fsmCallableDataIsInitialise((FSMCallableData*)machine->callable_data))
        return false;

    FSMCallableData *data = (FSMCallableData*)machine->callable_data;
    State start_state;

    if (!fsmCallableDataGetStartState(data, &start_state))
        return false;

    if (machine->state_table[machine->current_state].exit != NULL)
        machine->state_table[machine->current_state].exit(machine->context);

    machine->current_state = start_state;

    if (machine->state_table[machine->current_state].entry != NULL)
        machine->state_table[machine->current_state].entry(machine->context);

    return true;
}

/* РЕАЛИЗАЦИЯ ФУНКЦИЙ ДЛЯ ВЛОЖЕННЫХ АВТОМАТОВ */

/*выполнить один шаг вложенного автомата*/
bool fsmNestedStep(FSM *machine)
{
    if (machine == NULL)
        return false;
    
    EventFSM event;

    if (!queueEventIsEmpty(machine))
    {
        popEventQueue(machine, &event);
        dispatchFSM(machine, event);
        return true;
    }
    
    return false;
}