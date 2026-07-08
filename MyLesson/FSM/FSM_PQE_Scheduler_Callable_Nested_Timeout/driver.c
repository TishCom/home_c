/* ============================================================
 * timeout_test.c - ТЕСТ ТАЙМАУТОВ (С ПРАВИЛЬНЫМИ ШАГАМИ)
 * ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include "fsm.h"
#include "event_buffer_fsm.h"
#include "fsm_scheduler.h"
#include "fsm_callable.h"
#include "fsm_timeout.h"
#include "fsm_callable_dispatcher.h"

/* ============================================================
 * СОСТОЯНИЯ (РОДИТЕЛЬ)
 * ============================================================ */
typedef enum 
{
    IDLE = 0,
    RUN = 1,
    DONE = 2,
    ERROR1 = 3,
} State_t;

typedef enum 
{
    EVT_START = 0,
    EVT_RESET = 1,
} Event_t;

/* ============================================================
 * СОСТОЯНИЯ (ДОЧЕРНИЙ)
 * ============================================================ */
typedef enum 
{
    C_IDLE = 0,
    C_WORK = 1,
    C_DONE = 2,
} CState_t;

typedef enum 
{
    CEVT_GO = 0,
    CEVT_STEP = 1,
    CEVT_STOP = 2,
} CEvent_t;

/* ============================================================
 * ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ
 * ============================================================ */
static uint32_t fake_tick = 0;
static uint32_t step_count = 0;
static int timeout_triggered = 0;

static FSM parent_machine;
static FSM child_machine;
static FSMScheduler scheduler;

/* ============================================================
 * ТАБЛИЦЫ СОБЫТИЙ
 * ============================================================ */
const EventFSM parent_events[] = 
{
    [EVT_START] = {.event = EVT_START, .priority = 1},
    [EVT_RESET] = {.event = EVT_RESET, .priority = 1},
};

const EventFSM child_events[] = 
{
    [CEVT_GO]   = {.event = CEVT_GO, .priority = 1},
    [CEVT_STEP] = {.event = CEVT_STEP, .priority = 1},
    [CEVT_STOP] = {.event = CEVT_STOP, .priority = 1},
};

/* ============================================================
 * ПРОТОТИПЫ
 * ============================================================ */
static void parent_idle(void *ctx);
static void parent_run(void *ctx);
static void parent_done(void *ctx);
static void parent_error1(void *ctx);
static void parent_default(void *ctx);

static void on_start(void *ctx);
static void on_reset(void *ctx);
static void timeout_handler(void *ctx);

static void child_idle(void *ctx);
static void child_work(void *ctx);
static void child_done(void *ctx);
static void child_default(void *ctx);

static void on_child_go(void *ctx);
static void on_child_step(void *ctx);

static uint32_t get_tick(void);
static void init(void);
static void run_test(const char *name, uint32_t timeout_ticks, uint32_t steps_to_do);

/* ============================================================
 * ФУНКЦИЯ ВРЕМЕНИ
 * ============================================================ */
static uint32_t get_tick(void)
{
    return fake_tick;
}

/* ============================================================
 * ТАБЛИЦЫ ДЕЙСТВИЙ
 * ============================================================ */
const StateAction parent_actions[] = 
{
    [IDLE]   = {.entry = parent_idle,   .exit = NULL, .default_action = parent_default},
    [RUN]    = {.entry = parent_run,    .exit = NULL, .default_action = parent_default},
    [DONE]   = {.entry = parent_done,   .exit = NULL, .default_action = parent_default},
    [ERROR1] = {.entry = parent_error1, .exit = NULL, .default_action = parent_default},
};

const StateAction child_actions[] = 
{
    [C_IDLE] = {.entry = child_idle, .exit = NULL, .default_action = child_default},
    [C_WORK] = {.entry = child_work, .exit = NULL, .default_action = child_default},
    [C_DONE] = {.entry = child_done, .exit = NULL, .default_action = child_default},
};

/* ============================================================
 * ТАБЛИЦЫ ПЕРЕХОДОВ
 * ============================================================ */
const Transition parent_trans[] = 
{
    {IDLE,   parent_events[EVT_START], RUN,    on_start},
    {RUN,    parent_events[EVT_RESET], IDLE,   on_reset},
    {DONE,   parent_events[EVT_RESET], IDLE,   on_reset},
    {ERROR1, parent_events[EVT_RESET], IDLE,   on_reset},
};

const Transition child_trans[] = 
{
    {C_IDLE, child_events[CEVT_GO],   C_WORK, on_child_go},
    {C_WORK, child_events[CEVT_STEP], C_WORK, on_child_step},
    {C_WORK, child_events[CEVT_STOP], C_DONE, NULL},
};

/* ============================================================
 * ИНИЦИАЛИЗАЦИЯ
 * ============================================================ */
static void init(void)
{
    fsmTimerSetTickFunction(get_tick);

    FSMTemplateFill tpl_parent = {
        .current_state = IDLE,
        .state_table = parent_actions,
        .number_state = 4,
        .transition_table = parent_trans,
        .number_transition = 4,
        .context = NULL
    };
    initializeFSM(&parent_machine, tpl_parent);
    parent_machine.event_queue = initializeBufferFSM(10);
    parent_machine.scheduler_data = schedulerDataCreate(5, 3);

    FSMTemplateFill tpl_child = {
        .current_state = C_IDLE,
        .state_table = child_actions,
        .number_state = 3,
        .transition_table = child_trans,
        .number_transition = 3,
        .context = NULL
    };
    initializeFSM(&child_machine, tpl_child);
    child_machine.event_queue = initializeBufferFSM(10);
    child_machine.scheduler_data = schedulerDataCreate(3, 1);

    /* Создаём таймаут С ОБРАБОТЧИКОМ */
    FSMLocalTimer timer_template = {
        .on_timeout = timeout_handler
    };
    child_machine.timer_data = fsmTimerCreate(timer_template);
    if (child_machine.timer_data == NULL) {
        printf("Failed to create timer for child!\n");
        return;
    }

    FSMCallableData callable = {
        .caller = &parent_machine,
        .return_state = DONE,
        .finish_state = C_DONE,
        .start_state = C_IDLE,
        .is_called = false,
        .is_finished = false
    };
    child_machine.callable_data = fsmCallableDataCreate(callable);

    schedulerInit(&scheduler, 10, SCHEDULER_ROUND_ROBIN);
    schedulerAdd(&scheduler, &parent_machine);
    schedulerAdd(&scheduler, &child_machine);
}

/* ============================================================
 * РЕАЛИЗАЦИЯ
 * ============================================================ */
static void parent_idle(void *ctx)
{
    (void)ctx;
    printf("[P] IDLE\n");
}

static void parent_run(void *ctx)
{
    printf("[P] RUN\n");
}

static void parent_done(void *ctx)
{
    printf("[P] DONE\n");
}

static void parent_error1(void *ctx)
{
    printf("[P] ERROR1\n");
}

static void parent_default(void *ctx)
{
    (void)ctx;
    printf("[P] UNKNOWN\n");
}

static void on_start(void *ctx)
{
    (void)ctx;
    printf("[P] START\n");
    pushEventQueue(&child_machine, child_events[CEVT_GO]);
}

static void on_reset(void *ctx)
{
    (void)ctx;
    printf("[P] RESET\n");
    EventFSM dummy;
    while (!queueEventIsEmpty(&child_machine))
        popEventQueue(&child_machine, &dummy);
    setStateFSM(&child_machine, C_IDLE);
}

static void timeout_handler(void *ctx)
{
    (void)ctx;
    timeout_triggered = 1;
    printf("[P] TIMEOUT! (tick=%d)\n", fake_tick);
    setStateFSM(&parent_machine, ERROR1);
}

static void child_idle(void *ctx)
{
    (void)ctx;
    printf("[C] IDLE\n");
}

static void child_work(void *ctx)
{
    step_count++;
    printf("[C] WORK %d/3\n", step_count);
    
    if (step_count >= 3)
    {
        printf("[C] Sending CEVT_STOP\n");
        pushEventQueue(&child_machine, child_events[CEVT_STOP]);
    }
}

static void child_done(void *ctx)
{
    printf("[C] DONE\n");
    fsmReturn(&child_machine);
}

static void child_default(void *ctx)
{
    (void)ctx;
    printf("[C] UNKNOWN\n");
}

static void on_child_go(void *ctx)
{
    (void)ctx;
    printf("[C] GO\n");
}

static void on_child_step(void *ctx)
{
    (void)ctx;
    printf("[C] STEP\n");
}

/* ============================================================
 * ТЕСТ
 * ============================================================ */
static void run_test(const char *name, uint32_t timeout_ticks, uint32_t steps_to_do)
{
    printf("\n=== TEST: %s ===\n", name);
    printf("Timeout: %d ticks, Steps to do: %d\n", timeout_ticks, steps_to_do);
    
    fake_tick = 0;
    step_count = 0;
    timeout_triggered = 0;
    
    setStateFSM(&parent_machine, IDLE);
    setStateFSM(&child_machine, C_IDLE);

    EventFSM dummy;
    while (!queueEventIsEmpty(&parent_machine))
        popEventQueue(&parent_machine, &dummy);
    while (!queueEventIsEmpty(&child_machine))
        popEventQueue(&child_machine, &dummy);

    fsmTimerSetTimeout(&child_machine, timeout_ticks, timeout_handler);
    printf("[SETUP] timeout=%d, start_tick=%d\n", timeout_ticks, fake_tick);
    
    pushEventQueue(&parent_machine, parent_events[EVT_START]);

    while (1)
    {
        fake_tick++;
        printf("[TICK] %d\n", fake_tick);
        schedulerStep(&scheduler);
        
        State parent_state;
        getStateFSM(&parent_machine, &parent_state);
        
        if (parent_state == DONE || parent_state == ERROR1)
        {
            printf("[RESULT] %s at tick %d!\n", 
                   parent_state == DONE ? "DONE" : "TIMEOUT", fake_tick);
            return;
        }
        
        /* Отправляем STEP, если есть шаги */
        if (step_count < steps_to_do)
        {
            pushEventQueue(&child_machine, child_events[CEVT_STEP]);
        }
        
        if (fake_tick > 50)
        {
            printf("[RESULT] PROTECTION at tick %d!\n", fake_tick);
            return;
        }
    }
}

/* ============================================================
 * MAIN
 * ============================================================ */
int main(void)
{
    printf("\n=== TIMEOUT TESTS ===\n\n");

    init();

    run_test("Normal (timeout 10, 3 steps)", 10, 3);
    run_test("Timeout (timeout 2, 1 step)", 2, 1);
    run_test("Timeout (timeout 5, 2 steps)", 5, 2);
    run_test("Normal (timeout 20, 3 steps)", 20, 3);

    return 0;
}