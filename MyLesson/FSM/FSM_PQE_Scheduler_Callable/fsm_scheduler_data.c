#include "fsm_scheduler_data.h"

/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/

/* РЕАЛИЗАЦИЯ ФУНКЦИЙ УПРАВЛЕНИЯ ЖИЗНЕННЫМ ЦИКЛОМ */

/*оформление данных для автомата под управлением планировщика */
FSMSchedulerData* schedulerDataCreate(uint32_t priority, uint32_t quota)
{
    FSMSchedulerData* data = (FSMSchedulerData*)malloc(sizeof(FSMSchedulerData));

    if (data == NULL)
        return NULL;

    data->priority = priority == 0 ? 1 : priority;
    data->quota = quota == 0 ? 1 : quota;
    data->tick_counter = 0;
    data->is_active = true;

    /* Инициализация старения */
    data->starvation_counter = 0;
    data->boosted_priority = data->priority;

    return data;
}

/*освобождение памяти выделенной для данных необходимых автомату под управлением планировщика */
void schedulerDataDestroy(FSMSchedulerData *data)
{
    if (schedulerDataIsInitialise(data))
        free(data);
}

/*сброс данных необходимых автомату под управлением планировщика */
void schedulerDataReset(FSMSchedulerData *data)
{
    if (!schedulerDataIsInitialise(data))
        return;

    data->priority = 1;
    data->quota = 1;
    data->tick_counter = 0;
    data->is_active = true;
}

/*проверка, являются ли данные необходимых автомату под управлением планировщика инициализироваными */
bool schedulerDataIsInitialise(const FSMSchedulerData *data)
{
    return data != NULL;
}

/* РЕАЛИЗАЦИЯ ФУНКЦИЙ ДОСТУПА К ПОЛЯМ */

/*установка значения приоритета автомата для планировщика */
void schedulerDataSetPriority(FSMSchedulerData *data, uint32_t priority)
{
    if (!schedulerDataIsInitialise(data))
        return;

    data->priority = priority == 0 ? 1 : priority;
}

/*получение значения приоритета автомата */
uint32_t schedulerDataGetPriority(const FSMSchedulerData *data)
{
    if (!schedulerDataIsInitialise(data))
        return 0;

    return data->priority;
}

/*установка значения временной квоты автомата для планировщика */
void schedulerDataSetQuota(FSMSchedulerData *data, uint32_t quota)
{
    if (!schedulerDataIsInitialise(data))
        return;

    data->quota = quota == 0 ? 1 : quota;
}

/*получение значения временной квоты автомата */
uint32_t schedulerDataGetQuota(const FSMSchedulerData *data)
{
    if (!schedulerDataIsInitialise(data))
        return 1;

    return data->quota;
}

/*установка флага активности автомата */
void schedulerDataSetActive(FSMSchedulerData *data)
{
    if (!schedulerDataIsInitialise(data))
        return;

    data->is_active = true;
}

/*сброс флага активности автомата */
void schedulerDataResetActive(FSMSchedulerData *data)
{
    if (!schedulerDataIsInitialise(data))
        return;

    data->is_active = false;
}

/*проверка флага активности автомата */
bool schedulerDataIsActive(const FSMSchedulerData *data)
{
    if (!schedulerDataIsInitialise(data))
        return false;

    return data->is_active;
}

/*сброс текущего счетчика автомата */
void schedulerDataResetTickCounter(FSMSchedulerData *data)
{
    if (!schedulerDataIsInitialise(data))
        return;

    data->tick_counter = 0;
}

/*получение значения текущего счетчика автомата */
uint32_t schedulerDataGetTickCounter(const FSMSchedulerData *data)
{
    if (!schedulerDataIsInitialise(data))
        return 0;

    return data->tick_counter;
}

/*увеличение значения текущего счетчика автомата на единицу */
void schedulerDataIncrementTickCounter(FSMSchedulerData *data)
{
    if (!schedulerDataIsInitialise(data))
        return;

    data->tick_counter++;
}

/* РЕАЛИЗАЦИЯ ФУНКЦИЙ СТАРЕНИЯ */

/*сброс старения*/
void schedulerDataResetStarvation(FSMSchedulerData *data)
{
    if (!schedulerDataIsInitialise(data))
        return;
        
    data->starvation_counter = 0;
    data->boosted_priority = data->priority;
}

/*повышение старения*/
void schedulerDataIncrementStarvation(FSMSchedulerData *data)
{
    if (!schedulerDataIsInitialise(data))
        return;

    if (data->starvation_counter < FSM_AGING_MAX_BOOST) 
    {
        data->starvation_counter++;
        data->boosted_priority = data->priority + data->starvation_counter;
    }
}

/*получение актуального приоритета*/
uint32_t schedulerDataGetEffectivePriority(const FSMSchedulerData *data)
{
    if (!schedulerDataIsInitialise(data))
        return 0;

    return data->boosted_priority;
}