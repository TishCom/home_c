#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "fsm.h"
#include "event_buffer_fsm.h"

/* ============================================================
 * ОПРЕДЕЛЕНИЕ СОСТОЯНИЙ И СОБЫТИЙ
 * ============================================================ */
typedef enum 
{
	READY = 0,
	WAIT  = 1,
} STATE_t;

typedef enum 
{
	RUBL_1 = 0,
	RUBL_2 = 1,
	CANCEL = 2,
} EVENT_t;

enum User_Event
{
	USER_ENTER_RUBL_1 = '1',
	USER_ENTER_RUBL_2 = '2',
	USER_ENTER_CANCEL = '0',
};

/* ============================================================
 * ПРОТОТИПЫ ФУНКЦИЙ
 * ============================================================ */
/* Действия состояний */
static void ready(FSMContext *context);
static void wait(FSMContext *context);
static void default_action(FSMContext *context);

/* Действия на переходах */
static void prepare(FSMContext *context);
static void change(FSMContext *context);
static void return_rubl(FSMContext *context);
static void error(FSMContext *context);

/* Вспомогательные функции */
static void print_change(void);
static void print_prepare(void);
static EventFSM get_event(void);
static bool init_coffee_machine(void);

/* ============================================================
 * ТАБЛИЦА СОБЫТИЙ С ПРИОРИТЕТАМИ
 * ============================================================ */
const EventFSM event_table[] = 
{
    [RUBL_1] = {.event = RUBL_1, .priority = 3},
    [RUBL_2] = {.event = RUBL_2, .priority = 3},
	[CANCEL] = {.event = CANCEL, .priority = 3}
};

/* ============================================================
 * ТАБЛИЦА ДЕЙСТВИЙ СОСТОЯНИЙ
 * ============================================================ */
const StateAction state_table[] = 
{
    [READY] = {.exit = NULL, .entry = ready, .default_action = default_action},
    [WAIT] = {.exit = NULL, .entry = wait, .default_action = default_action}
};

/* ============================================================
 * ТАБЛИЦА ПЕРЕХОДОВ
 * ============================================================ */
const Transition trans_table[] = 
{
    {.current_state = READY, .event = event_table[RUBL_1], .next_state = WAIT, .action = NULL},
    {.current_state = READY, .event = event_table[RUBL_2], .next_state = READY, .action = prepare},
    {.current_state = READY, .event = event_table[CANCEL], .next_state = READY, .action = error},
    {.current_state = WAIT, .event = event_table[RUBL_1], .next_state = READY, .action = prepare},
    {.current_state = WAIT, .event = event_table[RUBL_2], .next_state = READY, .action = change},
    {.current_state = WAIT, .event = event_table[CANCEL], .next_state = READY, .action = return_rubl}
};

/* ============================================================
 * ОПРЕДЕЛЕНИЕ АВТОМАТОВ СИСТЕМЫ
 * ============================================================ */

/* Автомат кофемашины */
FSM coffee_machine;

/* ============================================================
 * MAIN
 * ============================================================ */
int main(void)
{
    printf("\n=== COFFEE MACHINE ===\n");
    printf("Commands:\n");
    printf("  '1' - Put 1 rubl\n");
    printf("  '2' - Put 2 rubl\n");
    printf("  '0' - Cancel\n");
    printf("======================\n\n");

	if (!init_coffee_machine()) 
	{
        printf("Failed to initialize coffee machine!\n");
        return 1;
    }

	pushEventQueue(&coffee_machine, event_table[RUBL_1]);
	pushEventQueue(&coffee_machine, event_table[RUBL_1]);

	pushEventQueue(&coffee_machine, event_table[RUBL_2]);

	pushEventQueue(&coffee_machine, event_table[CANCEL]);

	pushEventQueue(&coffee_machine, event_table[RUBL_1]);
	pushEventQueue(&coffee_machine, event_table[RUBL_2]);

	pushEventQueue(&coffee_machine, event_table[RUBL_1]);
	pushEventQueue(&coffee_machine, event_table[CANCEL]);

	printf("%d\n", fsmProcessQueue(&coffee_machine));

    while(1) 
    {
		if (!pushEventQueue(&coffee_machine, get_event()))
			printf("\nEvent dont push in queue!\n\n");

		fsmProcessQueue(&coffee_machine);

        // if (dispatchFSM(&coffee_machine, get_event())) 
        //     printf("\nEvent handled!\n\n");
        // else 
        //     printf("\nEvent NOT handled (default_action called)\n\n");
    }

    return 0;
}

/* ============================================================
 * РЕАЛИЗАЦИЯ ДЕЙСТВИЙ СОСТОЯНИЙ
 * ============================================================ */

static void ready(FSMContext *context)
{
	printf("Ready\n");
}

static void wait(FSMContext *context)
{
	printf("Wait\n");
}

static void default_action(FSMContext *context)
{
	printf("Error, event dont handle!\n");
}

/* ============================================================
 * РЕАЛИЗАЦИЯ ДЕЙСТВИЙ НА ПЕРЕХОДАХ
 * ============================================================ */
static void prepare(FSMContext *context)
{
	print_prepare();
}

static void change(FSMContext *context)
{
	print_change();
    print_prepare();
}

static void return_rubl(FSMContext *context)
{
	print_change();
}

static void error(FSMContext *context)
{
	printf("Error signal CANCEL\n");
}

/* ============================================================
 * ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
 * ============================================================ */
static void print_change(void)
{
	printf("Change 1 Rubl\n");
}

static void print_prepare(void)
{
	printf("Prepare coffee\n");
}

static EventFSM get_event(void)
{
	while(1)
    { 
		printf("1.Put 1 rubl\n2.Put 2 rubl\n0.Cancel\n");
		
		switch(_getch())
        {
			case USER_ENTER_RUBL_1:
				return event_table[RUBL_1];
			case USER_ENTER_RUBL_2:
				return event_table[RUBL_2];
			case USER_ENTER_CANCEL:
				return event_table[CANCEL];
			default:
				printf("Enter the correct value.\n");
				break;
        }
    }
}

static bool init_coffee_machine(void)
{
	// static const для экономии стека
	static const FSMTemplateFill template_fsm = 
	{
		.current_state = READY,
		.state_table = state_table,
		.number_state = SIZE_TABLE(state_table),
		.transition_table = trans_table,
		.number_transition = SIZE_TABLE(trans_table),
		.context = (FSMContext){.number = 0}
	};

	const uint32_t kSizeQueueEvent = 20;

	if (!initializeFSM(&coffee_machine, template_fsm))
		return false;

	coffee_machine.event_queue = initializeBufferFSM(kSizeQueueEvent);
	if (coffee_machine.event_queue == NULL)
		return false;

	return true;
}