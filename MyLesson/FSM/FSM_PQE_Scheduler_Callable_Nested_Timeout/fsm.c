#include "fsm.h"

/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/

/*инициализация конечного автомата*/
bool initializeFSM(FSM *target_machine, FSMTemplateFill source_machine)
{
    if (target_machine == NULL
        || source_machine.state_table == NULL
        || source_machine.number_state < 1
        || source_machine.current_state >= source_machine.number_state
        || (source_machine.transition_table == NULL && source_machine.number_transition != 0)
        || (source_machine.transition_table != NULL && source_machine.number_transition == 0))
        return false;

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