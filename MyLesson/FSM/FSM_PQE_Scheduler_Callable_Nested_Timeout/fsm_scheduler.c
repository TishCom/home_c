#include "fsm_scheduler.h"
#include "fsm_timeout.h"

/*--------------------------------------------*
 * Локальные типы данных
 *--------------------------------------------*/


/*--------------------------------------------*
 * Прототипы статических функций
 *--------------------------------------------*/

static bool find_machine(const FSMScheduler *sched, const FSM *machine);
static int32_t find_index_machine(const FSMScheduler *sched, const FSM *machine);
static void shift_left_array(FSM *automata[], uint32_t size);
static uint32_t sum_counter(uint32_t counter, uint32_t base);
static uint32_t max_priority_active_machine(FSMScheduler *sched);
static uint32_t max_priority_quota_active_machine(FSMScheduler *sched);

static uint32_t handler_scheduler_round_robin(FSMScheduler *sched);
static uint32_t handler_scheduler_priority(FSMScheduler *sched);
static uint32_t handler_scheduler_quota(FSMScheduler *sched);
static uint32_t handler_scheduler_priority_quota(FSMScheduler *sched);

/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/

/* УПРАВЛЕНИЕ ЖИЗНЕННЫМ ЦИКЛОМ ПЛАНИРОВЩИКА */

/*инициализация планировщика*/
bool schedulerInit(FSMScheduler *sched, uint32_t max_automata, SchedulerMode mode)
{
    if (sched == NULL || max_automata == 0
        || mode > SCHEDULER_PRIORITY_AND_QUOTA || mode < SCHEDULER_ROUND_ROBIN)
        return false;

    sched->automata = (FSM**)malloc(max_automata * sizeof(FSM*));
    if (sched->automata == NULL)
        return false;

    sched->capacity = max_automata;
    sched->count = 0;
    sched->current_index = 0;
    sched->mode = mode;
    sched->process_only_if_events = true;

    return true;
}

/*освобождение памяти выделенной для планировщика*/
void schedulerDestroy(FSMScheduler *sched)
{
    if (!schedulerIsInitialise(sched))
        return;

    free(sched->automata);

    sched->automata = NULL;
    sched->capacity = 0;
    sched->count = 0;
    sched->current_index = 0;
    sched->mode = SCHEDULER_ROUND_ROBIN;
    sched->process_only_if_events = true;
}

/* ПРОВЕРКА ПАРАМЕТРОВ ПЛАНИРОВЩИКА */

/*проверка, является ли планировщик инициализированным*/
bool schedulerIsInitialise(const FSMScheduler *sched)
{
    return sched != NULL && sched->automata != NULL;
}

/*получения значения колличества автоматов обрабатываемых планировщиком*/
uint32_t schedulerCount(const FSMScheduler *sched)
{
    if (!schedulerIsInitialise(sched))
        return 0;

    return sched->count;
}

/*получения значения максимального колличества автоматов которе может обработать планировщик*/
uint32_t schedulerCapacity(const FSMScheduler *sched)
{
    if (!schedulerIsInitialise(sched))
        return 0;

    return sched->capacity;
}

/*проверка, добавлен ли в планировщик хотябы один автомат*/
bool schedulerIsEmpty(const FSMScheduler *sched)
{
    if (!schedulerIsInitialise(sched))
        return true;

    return sched->count == 0;
}

/*проверка, можно ли добавить ли в планировщик хотябы один автомат*/
bool schedulerIsFull(const FSMScheduler *sched)
{
    if (!schedulerIsInitialise(sched))
        return false;

    return sched->count == sched->capacity;
}

/* РАБОТА С ПАРАМЕТРАМИ АВТОМАТОВ ПЛАНИРОВЩИКА */

/*установка значения приоритета автомата для планировщика*/
bool schedulerSetPriority(FSMScheduler *sched, FSM *machine, uint32_t priority)
{
    if (!schedulerIsInitialise(sched) || machine == NULL
        || !find_machine(sched, machine) || machine->scheduler_data == NULL)
        return false;

    schedulerDataSetPriority(((FSMSchedulerData*)machine->scheduler_data), priority);
    
    return true;
}

/*получение значения приоритета автомата*/
uint32_t schedulerGetPriority(const FSMScheduler *sched, const FSM *machine)
{
    if (!schedulerIsInitialise(sched) || machine == NULL
        || !find_machine(sched, machine) || machine->scheduler_data == NULL)
        return 0;
    
    return schedulerDataGetPriority((FSMSchedulerData*)machine->scheduler_data);
}

/*установка значения временной квоты автомата для планировщика*/
bool schedulerSetQuota(FSMScheduler *sched, FSM *machine, uint32_t quota)
{
    if (!schedulerIsInitialise(sched) || machine == NULL
        || !find_machine(sched, machine) || machine->scheduler_data == NULL)
        return false;

    schedulerDataSetQuota(((FSMSchedulerData*)machine->scheduler_data), quota);
    
    return true;
}

/*получение значения временной квоты автомата*/
uint32_t schedulerGetQuota(const FSMScheduler *sched, const FSM *machine)
{
    if (!schedulerIsInitialise(sched) || machine == NULL
        || !find_machine(sched, machine) || machine->scheduler_data == NULL)
        return 0;
    
    return schedulerDataGetQuota((FSMSchedulerData*)machine->scheduler_data);
}

/* УСТАНОВКА ПАРАМЕТРОВ ПЛАНИРОВЩИКА */

/*установка режима работы для планировщика*/
void schedulerSetMode(FSMScheduler *sched, SchedulerMode mode)
{
    if (!schedulerIsInitialise(sched)
        || mode > SCHEDULER_PRIORITY_AND_QUOTA || mode < SCHEDULER_ROUND_ROBIN)
        return;

    sched->mode = mode;
}

/*установка флага обработки автомата только при появлении события этого автомата*/
void schedulerSetProcessOnlyIfEvents(FSMScheduler *sched, bool enable)
{
    if (!schedulerIsInitialise(sched))
        return;

    sched->process_only_if_events = enable;
}

/* ДОБАВЛЕНИЕ И УДАЛЕНИЕ АВТОМАТОВ ПЛАНИРОВЩИКА */

/*добавление автомата в планировщик*/
bool schedulerAdd(FSMScheduler *sched, FSM *machine)
{
    if (!schedulerIsInitialise(sched) || machine == NULL
        || machine->scheduler_data == NULL || schedulerIsFull(sched)
        || find_machine(sched, machine))
        return false;

    sched->automata[sched->count] = machine;
    sched->count++;

    return true;
}

/*добавление автомата в планировщик с приоритетом*/
bool schedulerAddWithPriority(FSMScheduler *sched, FSM *machine, uint32_t priority)
{
    if (!schedulerIsInitialise(sched) || machine == NULL
        || machine->scheduler_data == NULL || schedulerIsFull(sched)
        || find_machine(sched, machine))
        return false;

    schedulerDataSetPriority(((FSMSchedulerData*)machine->scheduler_data), priority);

    sched->automata[sched->count] = machine;
    sched->count++;

    return true;
}

/*добавление автомата в планировщик с квотой*/
bool schedulerAddWithQuota(FSMScheduler *sched, FSM *machine, uint32_t quota)
{
    if (!schedulerIsInitialise(sched) || machine == NULL
        || machine->scheduler_data == NULL || schedulerIsFull(sched)
        || find_machine(sched, machine))
        return false;

    schedulerDataSetQuota(((FSMSchedulerData*)machine->scheduler_data), quota);

    sched->automata[sched->count] = machine;
    sched->count++;

    return true;
}

/*добавление автомата в планировщик с приоритетом и квотой*/
bool schedulerAddWithPriorityAndQuota(FSMScheduler *sched, FSM *machine, 
                                           uint32_t priority, uint32_t quota)
{
    if (!schedulerIsInitialise(sched) || machine == NULL
        || machine->scheduler_data == NULL || schedulerIsFull(sched)
        || find_machine(sched, machine))
        return false;

    schedulerDataSetPriority(((FSMSchedulerData*)machine->scheduler_data), priority);
    schedulerDataSetQuota(((FSMSchedulerData*)machine->scheduler_data), quota);

    sched->automata[sched->count] = machine;
    sched->count++;

    return true;
}

/*удаление автомата из планировщика*/
bool schedulerRemove(FSMScheduler *sched, FSM *machine)
{
    if (!schedulerIsInitialise(sched) || machine == NULL || machine->scheduler_data == NULL)
        return false;

    int32_t index = find_index_machine(sched, machine);
    if (index < 0)
        return false;

    shift_left_array(&sched->automata[index], sched->count - (uint32_t)index);
    sched->count--;

    return true;
}

/* ЗАПУСК ПЛАНИРОВЩИКА */

/*запуск одного шага работы планировщика*/
uint32_t schedulerStep(FSMScheduler *sched)
{
    if (!schedulerIsInitialise(sched))
        return 0;

    uint32_t count_process_events = 0;

    /* Проверка таймаутов*/
    fsmTimerCheckAllTimeouts(sched);

    switch (sched->mode)
    {
        case SCHEDULER_ROUND_ROBIN:
            count_process_events = handler_scheduler_round_robin(sched);
            break;

        case SCHEDULER_PRIORITY:
            count_process_events = handler_scheduler_priority(sched);
            break;

        case SCHEDULER_QUOTA:
            count_process_events = handler_scheduler_quota(sched);
            break;

        case SCHEDULER_PRIORITY_AND_QUOTA:
            count_process_events = handler_scheduler_priority_quota(sched);
            break;
            
        default:
            break;
    }

    return count_process_events;
}

/*запуск работы планировщика в бесколечном цикле*/
void schedulerRun(FSMScheduler *sched)
{
    if (!schedulerIsInitialise(sched))
        return;

    while (1)
        schedulerStep(sched);
}

/*--------------------------------------------*
 * Вспомогательные публичные функции(изменяемые пользователем)
 *--------------------------------------------*/

/*--------------------------------------------*
 * Статические функции (реализация)
 *--------------------------------------------*/

static bool find_machine(const FSMScheduler *sched, const FSM *machine)
{
    for (uint32_t i = 0; i < sched->count; i++)
    {
        if (sched->automata[i] == machine)
            return true;
    }
    
    return false;
}

static int32_t find_index_machine(const FSMScheduler *sched, const FSM *machine)
{
    for (uint32_t i = 0; i < sched->count; i++)
    {
        if (sched->automata[i] == machine)
            return i;
    }
    
    return -1;
}

static void shift_left_array(FSM *automata[], uint32_t size)
{
    if (size == 0)
        return;

    for (uint32_t i = 0; i < size - 1; i++)
        automata[i] = automata[i + 1];
}

static uint32_t sum_counter(uint32_t counter, uint32_t base)
{
    if (counter == base)
        return 0;

    return counter > base ? counter - base : counter;
}

static uint32_t max_priority_active_machine(FSMScheduler *sched)
{
    uint32_t max_priority = 0, current_prioroty = 0;

    for (uint32_t i = 0; i < sched->count; i++)
    {
        if (sched->process_only_if_events && queueEventIsEmpty(sched->automata[i])
            || !schedulerDataIsActive(sched->automata[i]->scheduler_data)
            || schedulerDataIsWaiting(sched->automata[i]->scheduler_data))
            continue;

        current_prioroty = schedulerDataGetEffectivePriority(sched->automata[i]->scheduler_data);
        if (max_priority < current_prioroty)
            max_priority = current_prioroty;
    }

    return max_priority;
}

static uint32_t max_priority_quota_active_machine(FSMScheduler *sched)
{
    uint32_t max_priority = 0, current_prioroty = 0;

    for (uint32_t i = 0; i < sched->count; i++)
    {
        if (sched->process_only_if_events && queueEventIsEmpty(sched->automata[i])
            || !schedulerDataIsActive(sched->automata[i]->scheduler_data)
            || schedulerDataIsWaiting(sched->automata[i]->scheduler_data))
            continue;

        current_prioroty = schedulerDataGetEffectivePriority(sched->automata[i]->scheduler_data);
        if (max_priority < current_prioroty && (schedulerDataGetQuota(sched->automata[i]->scheduler_data)
            <= schedulerDataGetTickCounter(sched->automata[i]->scheduler_data)))
            max_priority = current_prioroty;
    }

    return max_priority;
}

static uint32_t handler_scheduler_round_robin(FSMScheduler *sched)
{
    uint32_t count_process_events = 0;
    uint32_t index = 0;

    for (uint32_t i = 0; i < sched->count; i++)
    {
        index = sum_counter(sched->current_index + i, sched->count);
        
        if ((!sched->process_only_if_events || !queueEventIsEmpty(sched->automata[index]))
            && schedulerDataIsActive(sched->automata[index]->scheduler_data)
            && !schedulerDataIsWaiting(sched->automata[index]->scheduler_data))
        {
            count_process_events = fsmProcessCallable(sched->automata[index]);
            sched->current_index = sum_counter(index + 1, sched->count);
            break;
        }
    }
        
    return count_process_events;
}

static uint32_t handler_scheduler_priority(FSMScheduler *sched)
{
    uint32_t count_process_events = 0;
    uint32_t max_priority = 0;

    for (uint32_t i = 0; i < sched->count; i++)
    {
        if (schedulerDataIsActive(sched->automata[i]->scheduler_data)
            && !queueEventIsEmpty(sched->automata[i])
            && !schedulerDataIsWaiting(sched->automata[i]->scheduler_data))
            schedulerDataIncrementStarvation(sched->automata[i]->scheduler_data);
    }

    max_priority = max_priority_active_machine(sched);

    if (max_priority != 0)
    {
        for (uint32_t i = 0; i < sched->count; i++)
        {
            if (sched->process_only_if_events && queueEventIsEmpty(sched->automata[i])
                || !schedulerDataIsActive(sched->automata[i]->scheduler_data)
                || schedulerDataIsWaiting(sched->automata[i]->scheduler_data))
                continue;

            if (max_priority == schedulerDataGetEffectivePriority(sched->automata[i]->scheduler_data))
            {
                schedulerDataResetStarvation(sched->automata[i]->scheduler_data);
                count_process_events += fsmProcessCallable(sched->automata[i]);
            }
        }
    }
        
    return count_process_events;
}

static uint32_t handler_scheduler_quota(FSMScheduler *sched)
{
    uint32_t count_process_events = 0;

    for (uint32_t i = 0; i < sched->count; i++)
    {
        if (schedulerDataIsActive(sched->automata[i]->scheduler_data)
            && (!sched->process_only_if_events || !queueEventIsEmpty(sched->automata[i]))
            && !schedulerDataIsWaiting(sched->automata[i]->scheduler_data))
            schedulerDataIncrementTickCounter((FSMSchedulerData*)sched->automata[i]->scheduler_data);
    }
    
    for (uint32_t i = 0; i < sched->count; i++)
    {
         if (sched->process_only_if_events && queueEventIsEmpty(sched->automata[i])
            || !schedulerDataIsActive(sched->automata[i]->scheduler_data)
            || schedulerDataIsWaiting(sched->automata[i]->scheduler_data))
            continue;

        if ((schedulerDataGetQuota(sched->automata[i]->scheduler_data)
            == schedulerDataGetTickCounter(sched->automata[i]->scheduler_data)))
        {
            schedulerDataResetTickCounter(sched->automata[i]->scheduler_data);
            count_process_events += fsmProcessCallable(sched->automata[i]);
        }
    }
        
    return count_process_events;
}

static uint32_t handler_scheduler_priority_quota(FSMScheduler *sched)
{
    uint32_t count_process_events = 0;
    uint32_t max_priority = 0;

    for (uint32_t i = 0; i < sched->count; i++)
    {
        if (schedulerDataIsActive(sched->automata[i]->scheduler_data)
            && (!sched->process_only_if_events || !queueEventIsEmpty(sched->automata[i]))
            && !schedulerDataIsWaiting(sched->automata[i]->scheduler_data))
        {
            schedulerDataIncrementStarvation(sched->automata[i]->scheduler_data);
            schedulerDataIncrementTickCounter((FSMSchedulerData*)sched->automata[i]->scheduler_data);
        }
    }

    max_priority = max_priority_quota_active_machine(sched);
    
    if (max_priority != 0)
    {
        for (uint32_t i = 0; i < sched->count; i++)
        {
            if ((sched->process_only_if_events && queueEventIsEmpty(sched->automata[i]))
                || schedulerDataIsWaiting(sched->automata[i]->scheduler_data)
                || !schedulerDataIsActive(sched->automata[i]->scheduler_data))
                continue;

            if ((max_priority == schedulerDataGetEffectivePriority(sched->automata[i]->scheduler_data))
                && (schedulerDataGetQuota(sched->automata[i]->scheduler_data)
                <= schedulerDataGetTickCounter(sched->automata[i]->scheduler_data)))
            {
                schedulerDataResetStarvation(sched->automata[i]->scheduler_data);
                schedulerDataResetTickCounter(sched->automata[i]->scheduler_data);
                count_process_events += fsmProcessCallable(sched->automata[i]);
            }
        }
    }
        
    return count_process_events;
}