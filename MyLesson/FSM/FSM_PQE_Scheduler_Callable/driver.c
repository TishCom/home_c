#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "fsm.h"
#include "fsm_scheduler.h"

/* ============================================================
 * ОПРЕДЕЛЕНИЕ СОСТОЯНИЙ И СОБЫТИЙ ДЛЯ КОФЕМАШИНЫ
 * ============================================================ */
typedef enum 
{
    COFFEE_READY = 0,
    COFFEE_WAIT  = 1,
} CoffeeState_t;

typedef enum 
{
    COFFEE_RUBL_1 = 0,
    COFFEE_RUBL_2 = 1,
    COFFEE_CANCEL = 2,
} CoffeeEvent_t;

enum User_Event
{
    USER_ENTER_RUBL_1 = '1',
    USER_ENTER_RUBL_2 = '2',
    USER_ENTER_CANCEL = '0',
};

/* ============================================================
 * ОПРЕДЕЛЕНИЕ СОСТОЯНИЙ И СОБЫТИЙ ДЛЯ ИНДИКАТОРА
 * ============================================================ */
typedef enum 
{
    LED_OFF = 0,
    LED_ON  = 1,
    LED_BLINK_SLOW = 2,
    LED_BLINK_FAST = 3,
} LedState_t;

typedef enum 
{
    LED_SET_OFF = 0,
    LED_SET_ON = 1,
    LED_SET_BLINK_SLOW = 2,
    LED_SET_BLINK_FAST = 3,
    LED_TIMER_TICK = 4,
} LedEvent_t;

/* ============================================================
 * ПРОТОТИПЫ ФУНКЦИЙ (КОФЕМАШИНА)
 * ============================================================ */
static void coffee_ready(FSMContext *context);
static void coffee_wait(FSMContext *context);
static void coffee_default_action(FSMContext *context);

static void coffee_prepare(FSMContext *context);
static void coffee_change(FSMContext *context);
static void coffee_return_rubl(FSMContext *context);
static void coffee_error(FSMContext *context);

static void coffee_print_change(void);
static void coffee_print_prepare(void);
static EventFSM coffee_get_event(void);
static bool coffee_init(FSM *machine);

/* ============================================================
 * ПРОТОТИПЫ ФУНКЦИЙ (ИНДИКАТОР)
 * ============================================================ */
static void led_entry_off(FSMContext *context);
static void led_entry_on(FSMContext *context);
static void led_entry_blink_slow(FSMContext *context);
static void led_entry_blink_fast(FSMContext *context);
static void led_exit_blink(FSMContext *context);
static void led_default_action(FSMContext *context);

static void led_action_tick(FSMContext *context);

static bool led_init(FSM *machine);

/* ============================================================
 * ТАБЛИЦА СОБЫТИЙ С ПРИОРИТЕТАМИ (КОФЕМАШИНА)
 * ============================================================ */
const EventFSM coffee_event_table[] = 
{
    [COFFEE_RUBL_1] = {.event = COFFEE_RUBL_1, .priority = 3},
    [COFFEE_RUBL_2] = {.event = COFFEE_RUBL_2, .priority = 3},
    [COFFEE_CANCEL] = {.event = COFFEE_CANCEL, .priority = 5},
};

/* ============================================================
 * ТАБЛИЦА СОБЫТИЙ С ПРИОРИТЕТАМИ (ИНДИКАТОР)
 * ============================================================ */
const EventFSM led_event_table[] = 
{
    [LED_SET_OFF]        = {.event = LED_SET_OFF,         .priority = 1},
    [LED_SET_ON]         = {.event = LED_SET_ON,          .priority = 1},
    [LED_SET_BLINK_SLOW] = {.event = LED_SET_BLINK_SLOW,  .priority = 1},
    [LED_SET_BLINK_FAST] = {.event = LED_SET_BLINK_FAST,  .priority = 1},
    [LED_TIMER_TICK]     = {.event = LED_TIMER_TICK,      .priority = 2},
};

/* ============================================================
 * ТАБЛИЦА ДЕЙСТВИЙ СОСТОЯНИЙ (КОФЕМАШИНА)
 * ============================================================ */
const StateAction coffee_state_table[] = 
{
    [COFFEE_READY] = {.exit = NULL, .entry = coffee_ready,   .default_action = coffee_default_action},
    [COFFEE_WAIT]  = {.exit = NULL, .entry = coffee_wait,    .default_action = coffee_default_action}
};

/* ============================================================
 * ТАБЛИЦА ДЕЙСТВИЙ СОСТОЯНИЙ (ИНДИКАТОР)
 * ============================================================ */
const StateAction led_state_table[] = 
{
    [LED_OFF]        = {.exit = NULL, .entry = led_entry_off,        .default_action = led_default_action},
    [LED_ON]         = {.exit = NULL, .entry = led_entry_on,         .default_action = led_default_action},
    [LED_BLINK_SLOW] = {.exit = led_exit_blink, .entry = led_entry_blink_slow, .default_action = led_default_action},
    [LED_BLINK_FAST] = {.exit = led_exit_blink, .entry = led_entry_blink_fast, .default_action = led_default_action}
};

/* ============================================================
 * ТАБЛИЦА ПЕРЕХОДОВ (КОФЕМАШИНА)
 * ============================================================ */
const Transition coffee_trans_table[] = 
{
    {COFFEE_READY, coffee_event_table[COFFEE_RUBL_1], COFFEE_WAIT,  NULL},
    {COFFEE_READY, coffee_event_table[COFFEE_RUBL_2], COFFEE_READY, coffee_prepare},
    {COFFEE_READY, coffee_event_table[COFFEE_CANCEL], COFFEE_READY, coffee_error},
    {COFFEE_WAIT,  coffee_event_table[COFFEE_RUBL_1], COFFEE_READY, coffee_prepare},
    {COFFEE_WAIT,  coffee_event_table[COFFEE_RUBL_2], COFFEE_READY, coffee_change},
    {COFFEE_WAIT,  coffee_event_table[COFFEE_CANCEL], COFFEE_READY, coffee_return_rubl}
};

/* ============================================================
 * ТАБЛИЦА ПЕРЕХОДОВ (ИНДИКАТОР)
 * ============================================================ */
const Transition led_trans_table[] = 
{
    {LED_OFF,        led_event_table[LED_SET_OFF],         LED_OFF,        NULL},
    {LED_OFF,        led_event_table[LED_SET_ON],          LED_ON,         NULL},
    {LED_OFF,        led_event_table[LED_SET_BLINK_SLOW],  LED_BLINK_SLOW, NULL},
    {LED_OFF,        led_event_table[LED_SET_BLINK_FAST],  LED_BLINK_FAST, NULL},
    
    {LED_ON,         led_event_table[LED_SET_OFF],         LED_OFF,        NULL},
    {LED_ON,         led_event_table[LED_SET_ON],          LED_ON,         NULL},
    {LED_ON,         led_event_table[LED_SET_BLINK_SLOW],  LED_BLINK_SLOW, NULL},
    {LED_ON,         led_event_table[LED_SET_BLINK_FAST],  LED_BLINK_FAST, NULL},
    {LED_ON,         led_event_table[LED_TIMER_TICK],      LED_ON,         NULL},
    
    {LED_BLINK_SLOW, led_event_table[LED_SET_OFF],         LED_OFF,        NULL},
    {LED_BLINK_SLOW, led_event_table[LED_SET_ON],          LED_ON,         NULL},
    {LED_BLINK_SLOW, led_event_table[LED_SET_BLINK_SLOW],  LED_BLINK_SLOW, NULL},
    {LED_BLINK_SLOW, led_event_table[LED_SET_BLINK_FAST],  LED_BLINK_FAST, NULL},
    {LED_BLINK_SLOW, led_event_table[LED_TIMER_TICK],      LED_BLINK_SLOW, led_action_tick},
    
    {LED_BLINK_FAST, led_event_table[LED_SET_OFF],         LED_OFF,        NULL},
    {LED_BLINK_FAST, led_event_table[LED_SET_ON],          LED_ON,         NULL},
    {LED_BLINK_FAST, led_event_table[LED_SET_BLINK_SLOW],  LED_BLINK_SLOW, NULL},
    {LED_BLINK_FAST, led_event_table[LED_SET_BLINK_FAST],  LED_BLINK_FAST, NULL},
    {LED_BLINK_FAST, led_event_table[LED_TIMER_TICK],      LED_BLINK_FAST, led_action_tick},
};

/* ============================================================
 * ОПРЕДЕЛЕНИЕ АВТОМАТОВ СИСТЕМЫ
 * ============================================================ */
FSM coffee_machine;
FSM led_indicator;
FSMScheduler scheduler;

/* ============================================================
 * ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ ДЛЯ ИНДИКАТОРА
 * ============================================================ */
static uint32_t led_tick_counter = 0;
static bool led_state = false;

/* ============================================================
 * MAIN
 * ============================================================ */
int main(void)
{
    uint32_t timer_tick_counter = 0;
    EventFSM event;

    printf("\n=== COFFEE MACHINE + LED INDICATOR (with AGING) ===\n");
    printf("Commands:\n");
    printf("  '1' - Put 1 rubl\n");
    printf("  '2' - Put 2 rubl\n");
    printf("  '0' - Cancel\n");
    printf("===================================================\n\n");

    if (!coffee_init(&coffee_machine)) 
    {
        printf("Failed to initialize coffee machine!\n");
        return 1;
    }

    if (!led_init(&led_indicator)) 
    {
        printf("Failed to initialize LED indicator!\n");
        return 1;
    }

    schedulerInit(&scheduler, 10, SCHEDULER_PRIORITY_AND_QUOTA);

    schedulerAdd(&scheduler, &coffee_machine);
    schedulerAdd(&scheduler, &led_indicator);

    printf("=== System ready (Aging enabled, max boost: %d) ===\n\n", FSM_AGING_MAX_BOOST);

    while (1)
    {
        event = coffee_get_event();

        if (++timer_tick_counter >= 4)
        {
            timer_tick_counter = 0;
            pushEventQueue(&led_indicator, led_event_table[LED_TIMER_TICK]);
            printf("[TIMER] JOB\n");
        }

        if (!pushEventQueue(&coffee_machine, event))
            printf("Event NOT pushed to queue!\n");

        schedulerStep(&scheduler);

        printf("\n");
    }

    return 0;
}

/* ============================================================
 * РЕАЛИЗАЦИЯ ДЕЙСТВИЙ СОСТОЯНИЙ (КОФЕМАШИНА)
 * ============================================================ */
static void coffee_ready(FSMContext *context)
{
    (void)context;
    printf("[Coffee] READY - Please insert coins\n");
    pushEventQueue(&led_indicator, led_event_table[LED_SET_ON]);
}

static void coffee_wait(FSMContext *context)
{
    (void)context;
    printf("[Coffee] WAIT - Processing...\n");
    pushEventQueue(&led_indicator, led_event_table[LED_SET_BLINK_SLOW]);
}

static void coffee_default_action(FSMContext *context)
{
    (void)context;
    printf("[Coffee] ERROR: Unknown event!\n");
}

/* ============================================================
 * РЕАЛИЗАЦИЯ ДЕЙСТВИЙ НА ПЕРЕХОДАХ (КОФЕМАШИНА)
 * ============================================================ */
static void coffee_prepare(FSMContext *context)
{
    (void)context;
    coffee_print_prepare();
}

static void coffee_change(FSMContext *context)
{
    (void)context;
    coffee_print_change();
    coffee_print_prepare();
}

static void coffee_return_rubl(FSMContext *context)
{
    (void)context;
    coffee_print_change();
}

static void coffee_error(FSMContext *context)
{
    (void)context;
    printf("[Coffee] ERROR: Cancel signal received!\n");
}

/* ============================================================
 * ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ (КОФЕМАШИНА)
 * ============================================================ */
static void coffee_print_change(void)
{
    printf("[Coffee] Change 1 Rubl\n");
}

static void coffee_print_prepare(void)
{
    printf("[Coffee] Preparing coffee...\n");
    printf("[Coffee] Coffee is ready! Bon appetit!\n");
}

static EventFSM coffee_get_event(void)
{
    while (1)
    {
        printf("Enter command (1, 2, 0): ");
        int ch = _getch();
        printf("%c\n", ch);

        switch (ch)
        {
            case USER_ENTER_RUBL_1: return coffee_event_table[COFFEE_RUBL_1];
            case USER_ENTER_RUBL_2: return coffee_event_table[COFFEE_RUBL_2];
            case USER_ENTER_CANCEL: return coffee_event_table[COFFEE_CANCEL];
            default:
                printf("Invalid command. Use 1, 2, or 0.\n");
                break;
        }
    }
}

static bool coffee_init(FSM *machine)
{
    bool is_initialize = false;
    static const FSMTemplateFill template_fsm =
    {
        .current_state = COFFEE_READY,
        .state_table = coffee_state_table,
        .number_state = SIZE_TABLE(coffee_state_table),
        .transition_table = coffee_trans_table,
        .number_transition = SIZE_TABLE(coffee_trans_table),
        .context = (FSMContext){.number = 0}
    };

    is_initialize = initializeFSM(machine, template_fsm, 20);

    if (is_initialize)
        coffee_machine.scheduler_data = schedulerDataCreate(5, 3);

    return is_initialize;
}

/* ============================================================
 * РЕАЛИЗАЦИЯ ДЕЙСТВИЙ СОСТОЯНИЙ (ИНДИКАТОР)
 * ============================================================ */
static void led_entry_off(FSMContext *context)
{
    (void)context;
    led_state = false;
    printf("[LED] OFF\n");
}

static void led_entry_on(FSMContext *context)
{
    (void)context;
    led_state = true;
    printf("[LED] ON\n");
}

static void led_entry_blink_slow(FSMContext *context)
{
    (void)context;
    led_tick_counter = 0;
    printf("[LED] BLINK SLOW (period: 4 ticks)\n");
}

static void led_entry_blink_fast(FSMContext *context)
{
    (void)context;
    led_tick_counter = 0;
    printf("[LED] BLINK FAST (period: 2 ticks)\n");
}

static void led_exit_blink(FSMContext *context)
{
    (void)context;
    led_tick_counter = 0;
}

static void led_default_action(FSMContext *context)
{
    (void)context;
    printf("[LED] Unknown event received!\n");
}

/* ============================================================
 * РЕАЛИЗАЦИЯ ДЕЙСТВИЙ НА ПЕРЕХОДАХ (ИНДИКАТОР)
 * ============================================================ */
static void led_action_tick(FSMContext *context)
{
    (void)context;
    led_tick_counter++;

    State current_state;
    getStateFSM(&led_indicator, &current_state);

    if (current_state == LED_BLINK_SLOW && led_tick_counter >= 4) 
    {
        led_tick_counter = 0;
        led_state = !led_state;
        printf("[LED] Toggle: %s\n", led_state ? "ON" : "OFF");
    } 
    else if (current_state == LED_BLINK_FAST && led_tick_counter >= 2) 
    {
        led_tick_counter = 0;
        led_state = !led_state;
        printf("[LED] Toggle: %s\n", led_state ? "ON" : "OFF");
    }
}

static bool led_init(FSM *machine)
{
    bool is_initialize = false;
    static const FSMTemplateFill template_fsm =
    {
        .current_state = LED_OFF,
        .state_table = led_state_table,
        .number_state = SIZE_TABLE(led_state_table),
        .transition_table = led_trans_table,
        .number_transition = SIZE_TABLE(led_trans_table),
        .context = (FSMContext){.number = 0}
    };

    is_initialize = initializeFSM(machine, template_fsm, 10);

    if (is_initialize)
        led_indicator.scheduler_data = schedulerDataCreate(3, 1);

    return is_initialize;
}