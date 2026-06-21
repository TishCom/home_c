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

/*инициализация конечного автомата*/
bool initializeFSM(FSM *machine, State start_state,
                    const StateAction *state_table, uint32_t number_state,
                    const Transition *transition_table, uint32_t number_transition, 
                    FSMContext context)
{
    if (machine == NULL || state_table == NULL || number_state < 1
        || (transition_table == NULL && number_transition != 0) || start_state >= number_state
        || (transition_table != NULL && number_transition == 0))
        return false;

    machine->current_state = start_state;
    machine->state_table = state_table;
    machine->number_state = number_state;
    machine->transition_table = transition_table;
    machine->number_transition = number_transition;
    machine->context = context;

    if (machine->state_table[start_state].entry != NULL)
        machine->state_table[start_state].entry(&machine->context);

    return true;
}

/*диспетчеризация конечного автомата*/
bool dispatchFSM(FSM *machine, Event event)
{
    if (machine == NULL)
        return false;

    const Transition *kTrans = machine->transition_table;

    for (uint32_t i = 0; i < machine->number_transition; i++)
    {
        if (kTrans[i].current_state == machine->current_state && kTrans[i].event == event)
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

/*--------------------------------------------*
 * Вспомогательные публичные функции(изменяемые пользователем)
 *--------------------------------------------*/

/*--------------------------------------------*
 * Статические функции (реализация)
 *--------------------------------------------*/
