#include "fsm_timeout.h"

/*--------------------------------------------*
 * Локальные переменные
 *--------------------------------------------*/

/*указатель на пользовательскую функцию для получения текущего времени в миллисекундах*/
static fsmTimerGetTickFunc tick_func = NULL;

/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/

/* РЕАЛИЗАЦИЯ ФУНКЦИЙ УПРАВЛЕНИЕ ЖИЗНЕННЫМ ЦИКЛОМ ТАЙМАУТА */

/*оформление данных таймаута для автомата*/
FSMLocalTimer* fsmTimerCreate(FSMLocalTimer timer)
{
    if (timer.on_timeout == NULL)
        return NULL;

    FSMLocalTimer* timer_data = (FSMLocalTimer*)malloc(sizeof(FSMLocalTimer));
    if (timer_data == NULL)
        return NULL;

    timer_data->timeout_ms = timer.timeout_ms;
    timer_data->start_tick = timer.start_tick;
    timer_data->timeout_occurred = timer.timeout_occurred;
    timer_data->timeout_enabled = timer.timeout_enabled;
    timer_data->on_timeout = timer.on_timeout;

    if (timer_data->timeout_ms == 0)
        timer_data->timeout_enabled = false;

    return timer_data;
}

/*освобождение памяти выделенной для данных таймаута автомату*/
void fsmTimerDestroy(FSM *machine)
{
    if (machine == NULL || machine->timer_data == NULL)
        return;

    free(machine->timer_data);
    machine->timer_data = NULL;
}

/*сброс данных таймаута в начальное состояние*/
void fsmTimerReset(FSM *machine)
{
    if (machine == NULL || machine->timer_data == NULL)
        return;

    FSMLocalTimer *timer = (FSMLocalTimer*)machine->timer_data;

    timer->timeout_ms = 0;
    timer->start_tick = 0;
    timer->timeout_occurred = false;
    timer->timeout_enabled = false;
}

/*проверка, являются ли данные необходимые таймауту автомата инициализироваными*/
bool fsmTimerIsInitialise(const FSMLocalTimer *timer)
{
    return timer != NULL && timer->on_timeout != NULL;
}

/*проверка, инициализирован ли таймаут автомата*/
bool fsmTimerIsReady(const FSM *machine)
{
    if (machine == NULL)
        return false;
        
    return fsmTimerIsInitialise((FSMLocalTimer*)machine->timer_data);
}

/* РЕАЛИЗАЦИЯ ФУНКЦИЙ УСТАНОВКИ И УПРАВЛЕНИЕМ ТАЙМАУТОМ */

/*установить таймаут для автомата*/
bool fsmTimerSetTimeout(FSM *machine, uint32_t timeout_ms, void (*on_timeout)(void *context))
{
    if (!fsmTimerIsReady(machine) || on_timeout == NULL  || tick_func == NULL)
        return false;

    FSMLocalTimer *timer = (FSMLocalTimer*)machine->timer_data;

    timer->timeout_ms = timeout_ms;
    timer->on_timeout = on_timeout;
    timer->timeout_occurred = false;
    timer->start_tick = tick_func();
    timer->timeout_enabled = (timeout_ms > 0);

    return true;
}

/*сбросить таймаут для автомата*/
void fsmTimerClearTimeout(FSM *machine)
{
    if (!fsmTimerIsReady(machine))
        return;

    FSMLocalTimer *timer = (FSMLocalTimer*)machine->timer_data;

    timer->timeout_occurred = false;
    timer->timeout_enabled = false;
}

/*обновить время старта таймаута (продлить таймаут)*/
void fsmTimerRefreshTimeout(FSM *machine)
{
    if (!fsmTimerIsReady(machine) || tick_func == NULL)
        return;

    FSMLocalTimer *timer = (FSMLocalTimer*)machine->timer_data;

    timer->start_tick = tick_func();
}

/*установка значения таймаута автомата*/
void fsmTimerSetTimeoutValue(FSM *machine, uint32_t timeout_ms)
{
    if (!fsmTimerIsReady(machine))
        return;

    FSMLocalTimer *timer = (FSMLocalTimer*)machine->timer_data;

    timer->timeout_ms = timeout_ms;

    if (timeout_ms == 0)
        timer->timeout_enabled = false;
}

/*получение значения таймаута автомата*/
bool fsmTimerGetTimeout(const FSM *machine, uint32_t *timeout_ms)
{
    if (!fsmTimerIsReady(machine) || timeout_ms == NULL)
        return false;

    FSMLocalTimer *timer = (FSMLocalTimer*)machine->timer_data;

    *timeout_ms = timer->timeout_ms;

    return true;
}

/*установка значения времени старта автомата*/
void fsmTimerSetStart(FSM *machine, uint32_t start_tick)
{
    if (!fsmTimerIsReady(machine))
        return;

    FSMLocalTimer *timer = (FSMLocalTimer*)machine->timer_data;

    timer->start_tick = start_tick;
}

/*получение значения времени старта автомата*/
bool fsmTimerGetStart(const FSM *machine, uint32_t *start_tick)
{
    if (!fsmTimerIsReady(machine) || start_tick == NULL)
        return false;

    FSMLocalTimer *timer = (FSMLocalTimer*)machine->timer_data;

    *start_tick = timer->start_tick;

    return true;
}

/*установка таймера автомата как сработавшего*/
void fsmTimerSetOccurred(FSM *machine)
{
    if (!fsmTimerIsReady(machine))
        return;

    FSMLocalTimer *timer = (FSMLocalTimer*)machine->timer_data;

    timer->timeout_occurred = true;
}

/*установка таймера автомата как не сработавшего*/
void fsmTimerResetOccurred(FSM *machine)
{
    if (!fsmTimerIsReady(machine))
        return;

    FSMLocalTimer *timer = (FSMLocalTimer*)machine->timer_data;

    timer->timeout_occurred = false;
}

/*установка таймера автомата как активного*/
void fsmTimerSetEnable(FSM *machine)
{
    if (!fsmTimerIsReady(machine))
        return;

    FSMLocalTimer *timer = (FSMLocalTimer*)machine->timer_data;

    timer->timeout_enabled = true;
}

/*установка таймера автомата как не активного*/
void fsmTimerResetEnable(FSM *machine)
{
    if (!fsmTimerIsReady(machine))
        return;

    FSMLocalTimer *timer = (FSMLocalTimer*)machine->timer_data;

    timer->timeout_enabled = false;
}

/* РЕАЛИЗАЦИЯ ФУНКЦИЙ ПРОВЕРКИ ТАЙМАУТА */

/*проверить, не истек ли таймаут*/
bool fsmTimerIsExpired(const FSM *machine)
{
    if (!fsmTimerIsReady(machine)  || tick_func == NULL)
        return false;

    FSMLocalTimer *timer = (FSMLocalTimer*)machine->timer_data;

    if (!timer->timeout_enabled || timer->timeout_occurred)
        return false;

    return (timer->timeout_ms <= tick_func() - timer->start_tick);
}

/*проверка, является ли автомат активным*/
bool fsmTimerIsEnable(const FSM *machine)
{
    if (!fsmTimerIsReady(machine))
        return false;

    FSMLocalTimer *timer = (FSMLocalTimer*)machine->timer_data;

    return timer->timeout_enabled;
}

/*проверка, является ли автомат выполненным*/
bool fsmTimerIsOccurred(const FSM *machine)
{
    if (!fsmTimerIsReady(machine))
        return false;

    FSMLocalTimer *timer = (FSMLocalTimer*)machine->timer_data;

    return timer->timeout_occurred;
}

/* РЕАЛИЗАЦИЯ ФУНКЦИЙ ОБРАБОТКИ ТАЙМАУТА В ПЛАНИРОВЩИКЕ */

/*проверить таймауты всех автоматов в планировщике*/
void fsmTimerCheckAllTimeouts(void *sched_prt)
{
    if (sched_prt == NULL)
        return;

    FSMScheduler *sched = (FSMScheduler*)sched_prt;
    FSM *machine;
    FSMLocalTimer *timer;

    for (uint32_t i = 0; i < sched->count; i++)
    {
        machine = sched->automata[i];
        timer = (FSMLocalTimer*)machine->timer_data;

        if (fsmTimerIsExpired(machine))
        {
            timer->timeout_occurred = true;
            
            if (timer->on_timeout != NULL)
                timer->on_timeout(&machine->context);

            if (fsmIsCalled(machine))
                fsmReturnWithTimeout(machine);
        }
    }
}

/* РЕАЛИЗАЦИЯ ФУНКЦИЙ ПОЛУЧЕНИЯ ТЕКУЩЕГО ВРЕМЕНИ (УКАЗАТЕЛЬ НА ФУНКЦИЮ) */

/*установка пользовательской функции получения времени*/
void fsmTimerSetTickFunction(fsmTimerGetTickFunc func)
{
    if (func == NULL)
        return;

    tick_func = func;
}

/*получить текущее время в миллисекундах*/
uint32_t fsmTimerGetCurrentTick(void)
{
    if (tick_func == NULL)
        return 0;

    return tick_func();
}