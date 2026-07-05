#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "fsm.h"
#include "event_buffer_fsm.h"
#include "fsm_scheduler.h"
#include "fsm_callable.h"
#include "fsm_callable_dispatcher.h"

/* ============================================================
 * ОПРЕДЕЛЕНИЕ СОСТОЯНИЙ ДЛЯ КОФЕМАШИНЫ (РОДИТЕЛЬ)
 * ============================================================ */
typedef enum 
{
    COFFEE_READY = 0,
    COFFEE_WAIT  = 1,
    COFFEE_BREWING = 2,      /* Ожидание завершения дочернего автомата */
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
 * ОПРЕДЕЛЕНИЕ СОСТОЯНИЙ ДЛЯ ПРОЦЕССА ПРИГОТОВЛЕНИЯ КОФЕ (ДОЧЕРНИЙ)
 * ============================================================ */
typedef enum 
{
    BREW_START = 0,
    BREW_HEATING = 1,
    BREW_BREWING = 2,
    BREW_FINISH = 3,         /* Конечное состояние */
} BrewState_t;

typedef enum 
{
    BREW_EVENT_START = 0,
    BREW_EVENT_HEAT_DONE = 1,
    BREW_EVENT_BREW_DONE = 2,
} BrewEvent_t;

/* ============================================================
 * ОПРЕДЕЛЕНИЕ СОСТОЯНИЙ ДЛЯ LED ИНДИКАТОРА
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
 * КОНТЕКСТ ПРИЛОЖЕНИЯ
 * ============================================================ */
typedef struct {
    uint32_t number;
    uint32_t brew_counter;
} AppContext;

/* ============================================================
 * ПРОТОТИПЫ ФУНКЦИЙ (КОФЕМАШИНА)
 * ============================================================ */
static void coffee_ready(void *context);
static void coffee_wait(void *context);
static void coffee_brewing(void *context);
static void coffee_default_action(void *context);

static void coffee_prepare(void *context);
static void coffee_change(void *context);
static void coffee_return_rubl(void *context);
static void coffee_error(void *context);
static void coffee_start_brew(void *context);

static void coffee_print_change(void);
static void coffee_print_prepare(void);
static EventFSM coffee_get_event(void);
static bool coffee_init(FSM *machine);

/* ============================================================
 * ПРОТОТИПЫ ФУНКЦИЙ (ПРОЦЕСС ПРИГОТОВЛЕНИЯ - ВЫЗЫВАЕМЫЙ)
 * ============================================================ */
static void brew_start(void *context);
static void brew_heating(void *context);
static void brew_brewing(void *context);
static void brew_finish(void *context);
static void brew_default_action(void *context);

static void brew_action_heat(void *context);
static void brew_action_brew(void *context);

static bool brew_init(FSM *machine);

/* ============================================================
 * ПРОТОТИПЫ ФУНКЦИЙ (LED ИНДИКАТОР)
 * ============================================================ */
static void led_entry_off(void *context);
static void led_entry_on(void *context);
static void led_entry_blink_slow(void *context);
static void led_entry_blink_fast(void *context);
static void led_exit_blink(void *context);
static void led_default_action(void *context);

static void led_action_tick(void *context);

static bool led_init(FSM *machine);

/* ============================================================
 * ТАБЛИЦЫ СОБЫТИЙ
 * ============================================================ */
const EventFSM coffee_event_table[] = 
{
    [COFFEE_RUBL_1] = {.event = COFFEE_RUBL_1, .priority = 3},
    [COFFEE_RUBL_2] = {.event = COFFEE_RUBL_2, .priority = 3},
    [COFFEE_CANCEL] = {.event = COFFEE_CANCEL, .priority = 5},
};

const EventFSM brew_event_table[] = 
{
    [BREW_EVENT_START]     = {.event = BREW_EVENT_START, .priority = 2},
    [BREW_EVENT_HEAT_DONE] = {.event = BREW_EVENT_HEAT_DONE, .priority = 2},
    [BREW_EVENT_BREW_DONE] = {.event = BREW_EVENT_BREW_DONE, .priority = 2},
};

const EventFSM led_event_table[] = 
{
    [LED_SET_OFF]        = {.event = LED_SET_OFF,        .priority = 1},
    [LED_SET_ON]         = {.event = LED_SET_ON,         .priority = 1},
    [LED_SET_BLINK_SLOW] = {.event = LED_SET_BLINK_SLOW, .priority = 1},
    [LED_SET_BLINK_FAST] = {.event = LED_SET_BLINK_FAST, .priority = 1},
    [LED_TIMER_TICK]     = {.event = LED_TIMER_TICK,     .priority = 2},
};

/* ============================================================
 * ТАБЛИЦА ДЕЙСТВИЙ СОСТОЯНИЙ (КОФЕМАШИНА)
 * ============================================================ */
const StateAction coffee_state_table[] = 
{
    [COFFEE_READY]   = {.exit = NULL, .entry = coffee_ready,   .default_action = coffee_default_action},
    [COFFEE_WAIT]    = {.exit = NULL, .entry = coffee_wait,    .default_action = coffee_default_action},
    [COFFEE_BREWING] = {.exit = NULL, .entry = coffee_brewing, .default_action = coffee_default_action},
};

/* ============================================================
 * ТАБЛИЦА ДЕЙСТВИЙ СОСТОЯНИЙ (ПРОЦЕСС ПРИГОТОВЛЕНИЯ)
 * ============================================================ */
const StateAction brew_state_table[] = 
{
    [BREW_START]    = {.exit = NULL, .entry = brew_start,    .default_action = brew_default_action},
    [BREW_HEATING]  = {.exit = NULL, .entry = brew_heating,  .default_action = brew_default_action},
    [BREW_BREWING]  = {.exit = NULL, .entry = brew_brewing,  .default_action = brew_default_action},
    [BREW_FINISH]   = {.exit = NULL, .entry = brew_finish,   .default_action = brew_default_action},
};

/* ============================================================
 * ТАБЛИЦА ДЕЙСТВИЙ СОСТОЯНИЙ (LED)
 * ============================================================ */
const StateAction led_state_table[] = 
{
    [LED_OFF]        = {.exit = NULL, .entry = led_entry_off,        .default_action = led_default_action},
    [LED_ON]         = {.exit = NULL, .entry = led_entry_on,         .default_action = led_default_action},
    [LED_BLINK_SLOW] = {.exit = led_exit_blink, .entry = led_entry_blink_slow, .default_action = led_default_action},
    [LED_BLINK_FAST] = {.exit = led_exit_blink, .entry = led_entry_blink_fast, .default_action = led_default_action},
};

/* ============================================================
 * ТАБЛИЦА ПЕРЕХОДОВ (КОФЕМАШИНА)
 * ============================================================ */
const Transition coffee_trans_table[] = 
{
    {COFFEE_READY,   coffee_event_table[COFFEE_RUBL_1], COFFEE_WAIT,    NULL},
    {COFFEE_READY,   coffee_event_table[COFFEE_RUBL_2], COFFEE_WAIT,    coffee_prepare},
    {COFFEE_READY,   coffee_event_table[COFFEE_CANCEL], COFFEE_READY,   coffee_error},

    {COFFEE_WAIT,    coffee_event_table[COFFEE_RUBL_1], COFFEE_BREWING, coffee_start_brew},
    {COFFEE_WAIT,    coffee_event_table[COFFEE_RUBL_2], COFFEE_BREWING, coffee_start_brew},
    {COFFEE_WAIT,    coffee_event_table[COFFEE_CANCEL], COFFEE_READY,   coffee_return_rubl},

    {COFFEE_BREWING, coffee_event_table[COFFEE_RUBL_1], COFFEE_BREWING, NULL},
    {COFFEE_BREWING, coffee_event_table[COFFEE_RUBL_2], COFFEE_BREWING, NULL},
    {COFFEE_BREWING, coffee_event_table[COFFEE_CANCEL], COFFEE_BREWING, NULL},
};

/* ============================================================
 * ТАБЛИЦА ПЕРЕХОДОВ (ПРОЦЕСС ПРИГОТОВЛЕНИЯ)
 * ============================================================ */
const Transition brew_trans_table[] = 
{
    {BREW_START,    brew_event_table[BREW_EVENT_START],     BREW_HEATING, brew_action_heat},
    {BREW_HEATING,  brew_event_table[BREW_EVENT_HEAT_DONE], BREW_BREWING, brew_action_brew},
    {BREW_BREWING,  brew_event_table[BREW_EVENT_BREW_DONE], BREW_FINISH,  NULL},
};

/* ============================================================
 * ТАБЛИЦА ПЕРЕХОДОВ (LED)
 * ============================================================ */
const Transition led_trans_table[] = 
{
    {LED_OFF,        led_event_table[LED_SET_OFF],         LED_OFF,        NULL},
    {LED_OFF,        led_event_table[LED_SET_ON],          LED_ON,         NULL},
    {LED_OFF,        led_event_table[LED_SET_BLINK_SLOW],  LED_BLINK_SLOW, NULL},
    {LED_OFF,        led_event_table[LED_SET_BLINK_FAST],  LED_BLINK_FAST, NULL},
    {LED_OFF,        led_event_table[LED_TIMER_TICK],      LED_OFF,        NULL},
    
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
static FSM coffee_machine;
static FSM brew_machine;          
static FSM led_indicator;
static FSMScheduler scheduler;

static AppContext app_context = 
{
    .number = 0,
    .brew_counter = 0
};

/* ============================================================
 * ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ
 * ============================================================ */
static uint32_t led_tick_counter = 0;
static bool led_state = false;
static bool brew_finished = false;

/* ============================================================
 * MAIN
 * ============================================================ */
int main(void)
{
    uint32_t timer_tick_counter = 0;
    EventFSM event;

    printf("\n=== COFFEE MACHINE WITH CALLABLE AUTOMATON ===\n");
    printf("Commands:\n");
    printf("  '1' - Put 1 rubl (start brew process)\n");
    printf("  '2' - Put 2 rubl (start brew process)\n");
    printf("  '0' - Cancel\n");
    printf("================================================\n\n");

    if (!coffee_init(&coffee_machine)) 
    {
        printf("Failed to initialize coffee machine!\n");
        return 1;
    }

    if (!brew_init(&brew_machine)) 
    {
        printf("Failed to initialize brew machine!\n");
        return 1;
    }

    if (!led_init(&led_indicator)) 
    {
        printf("Failed to initialize LED indicator!\n");
        return 1;
    }

    schedulerInit(&scheduler, 10, SCHEDULER_PRIORITY_AND_QUOTA);

    schedulerAdd(&scheduler, &coffee_machine);
    schedulerAdd(&scheduler, &brew_machine);
    schedulerAdd(&scheduler, &led_indicator);

    printf("=== System ready (Aging enabled, max boost: %d) ===\n\n", FSM_AGING_MAX_BOOST);

    while (1)
    {
        event = coffee_get_event();

        if (++timer_tick_counter >= 4) 
        {
            timer_tick_counter = 0;
            pushEventQueue(&led_indicator, led_event_table[LED_TIMER_TICK]);
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
static void coffee_ready(void *context)
{
    (void)context;
    printf("[Coffee] READY - Please insert coins\n");
    pushEventQueue(&led_indicator, led_event_table[LED_SET_ON]);
}

static void coffee_wait(void *context)
{
    (void)context;
    printf("[Coffee] WAIT - Inserted coin. Press 1 or 2 to start brew, 0 to cancel\n");
    pushEventQueue(&led_indicator, led_event_table[LED_SET_BLINK_SLOW]);
}

static void coffee_brewing(void *context)
{
    (void)context;
    printf("[Coffee] BREWING in progress... waiting for child to finish\n");
    pushEventQueue(&led_indicator, led_event_table[LED_SET_BLINK_FAST]);
}

static void coffee_default_action(void *context)
{
    (void)context;
    printf("[Coffee] ERROR: Unknown event!\n");
}

/* ============================================================
 * РЕАЛИЗАЦИЯ ДЕЙСТВИЙ НА ПЕРЕХОДАХ (КОФЕМАШИНА)
 * ============================================================ */
static void coffee_prepare(void *context)
{
    (void)context;
    coffee_print_prepare();
}

static void coffee_change(void *context)
{
    (void)context;
    coffee_print_change();
    coffee_print_prepare();
}

static void coffee_return_rubl(void *context)
{
    (void)context;
    coffee_print_change();
}

static void coffee_error(void *context)
{
    (void)context;
    printf("[Coffee] ERROR: Cancel signal received!\n");
}

static void coffee_start_brew(void *context)
{
    (void)context;
    AppContext *app = (AppContext*)context;
    
    printf("[Coffee] Starting brew process...\n");
    
    /* Вызываем дочерний автомат для приготовления кофе */
    if (fsmCall(&brew_machine, &coffee_machine, BREW_FINISH, COFFEE_READY)) 
    {
        printf("[Coffee] Brew process started successfully\n");
        pushEventQueue(&brew_machine, brew_event_table[BREW_EVENT_START]);
        app->brew_counter++;
    } 
    else 
    {
        printf("[Coffee] Failed to start brew process!\n");
    }
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

        switch (ch) {
            case USER_ENTER_RUBL_1: return coffee_event_table[COFFEE_RUBL_1];
            case USER_ENTER_RUBL_2: return coffee_event_table[COFFEE_RUBL_2];
            case USER_ENTER_CANCEL: return coffee_event_table[COFFEE_CANCEL];
            default:
                printf("Invalid command. Use 1, 2, or 0.\n");
                break;
        }
    }
}

/* ============================================================
 * ИНИЦИАЛИЗАЦИЯ КОФЕМАШИНЫ
 * ============================================================ */
static bool coffee_init(FSM *machine)
{
    static const FSMTemplateFill template_fsm = 
    {
        .current_state = COFFEE_READY,
        .state_table = coffee_state_table,
        .number_state = SIZE_TABLE(coffee_state_table),
        .transition_table = coffee_trans_table,
        .number_transition = SIZE_TABLE(coffee_trans_table),
        .context = &app_context
    };

    if (!initializeFSM(machine, template_fsm))
        return false;

    machine->event_queue = initializeBufferFSM(20);
    if (machine->event_queue == NULL)
        return false;

    machine->scheduler_data = schedulerDataCreate(5, 3);
    if (machine->scheduler_data == NULL)
        return false;

    return true;
}

/* ============================================================
 * РЕАЛИЗАЦИЯ ДЕЙСТВИЙ СОСТОЯНИЙ (ПРОЦЕСС ПРИГОТОВЛЕНИЯ)
 * ============================================================ */
static void brew_start(void *context)
{
    (void)context;
    printf("[Brew] START - Beginning brew process\n");
    // pushEventQueue(&brew_machine, brew_event_table[BREW_EVENT_START]);
}

static void brew_heating(void *context)
{
    (void)context;
    printf("[Brew] HEATING - Heating water...\n");
    pushEventQueue(&brew_machine, brew_event_table[BREW_EVENT_HEAT_DONE]);
}

static void brew_brewing(void *context)
{
    (void)context;
    printf("[Brew] BREWING - Steeping coffee...\n");
    pushEventQueue(&brew_machine, brew_event_table[BREW_EVENT_BREW_DONE]);
}

static void brew_finish(void *context)
{
    (void)context;
    printf("[Brew] FINISH - Coffee is ready!\n");
}

static void brew_default_action(void *context)
{
    (void)context;
    printf("[Brew] ERROR: Unknown event!\n");
}

/* ============================================================
 * РЕАЛИЗАЦИЯ ДЕЙСТВИЙ НА ПЕРЕХОДАХ (ПРОЦЕСС ПРИГОТОВЛЕНИЯ)
 * ============================================================ */
static void brew_action_heat(void *context)
{
    (void)context;
    printf("[Brew] Action: Heating water...\n");
}

static void brew_action_brew(void *context)
{
    (void)context;
    printf("[Brew] Action: Brewing coffee...\n");
}

/* ============================================================
 * ИНИЦИАЛИЗАЦИЯ ПРОЦЕССА ПРИГОТОВЛЕНИЯ (ВЫЗЫВАЕМЫЙ АВТОМАТ)
 * ============================================================ */
static bool brew_init(FSM *machine)
{
    static const FSMTemplateFill template_fsm = 
    {
        .current_state = BREW_START,
        .state_table = brew_state_table,
        .number_state = SIZE_TABLE(brew_state_table),
        .transition_table = brew_trans_table,
        .number_transition = SIZE_TABLE(brew_trans_table),
        .context = NULL
    };

    if (!initializeFSM(machine, template_fsm))
        return false;

    machine->event_queue = initializeBufferFSM(10);
    if (machine->event_queue == NULL)
        return false;

    machine->scheduler_data = schedulerDataCreate(4, 1);
    if (machine->scheduler_data == NULL)
        return false;

    /* Создаём данные для вызываемого автомата */
    FSMCallableData callable_template = 
    {
        .caller = NULL,
        .return_state = COFFEE_READY,
        .finish_state = BREW_FINISH,
        .start_state = BREW_START,
        .is_called = false,
        .is_finished = false
    };

    machine->callable_data = fsmCallableDataCreate(callable_template);
    if (machine->callable_data == NULL)
        return false;

    return true;
}

/* ============================================================
 * РЕАЛИЗАЦИЯ ДЕЙСТВИЙ СОСТОЯНИЙ (LED)
 * ============================================================ */
static void led_entry_off(void *context)
{
    (void)context;
    led_state = false;
    printf("[LED] OFF\n");
}

static void led_entry_on(void *context)
{
    (void)context;
    led_state = true;
    printf("[LED] ON\n");
}

static void led_entry_blink_slow(void *context)
{
    (void)context;
    led_tick_counter = 0;
    printf("[LED] BLINK SLOW (period: 4 ticks)\n");
}

static void led_entry_blink_fast(void *context)
{
    (void)context;
    led_tick_counter = 0;
    printf("[LED] BLINK FAST (period: 2 ticks)\n");
}

static void led_exit_blink(void *context)
{
    (void)context;
    led_tick_counter = 0;
}

static void led_default_action(void *context)
{
    (void)context;
    printf("[LED] Unknown event received!\n");
}

static void led_action_tick(void *context)
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

/* ============================================================
 * ИНИЦИАЛИЗАЦИЯ LED
 * ============================================================ */
static bool led_init(FSM *machine)
{
    static const FSMTemplateFill template_fsm = 
    {
        .current_state = LED_OFF,
        .state_table = led_state_table,
        .number_state = SIZE_TABLE(led_state_table),
        .transition_table = led_trans_table,
        .number_transition = SIZE_TABLE(led_trans_table),
        .context = NULL
    };

    if (!initializeFSM(machine, template_fsm))
        return false;

    machine->event_queue = initializeBufferFSM(10);
    if (machine->event_queue == NULL)
        return false;

    machine->scheduler_data = schedulerDataCreate(2, 2);
    if (machine->scheduler_data == NULL)
        return false;

    return true;
}