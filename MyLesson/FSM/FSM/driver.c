#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "fsm.h"

/* ============================================================
 * ОПРЕДЕЛЕНИЕ СОСТОЯНИЙ И СОБЫТИЙ
 * ============================================================ */
typedef enum 
{
	READY = 0,
	WAIT  = 1,
	STATE_MAX,
} STATE_t;

typedef enum 
{
	RUBL_1 = 0,
	RUBL_2 = 1,
	CANCEL = 2,
	EVENT_MAX,
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
void ready(FSMContext *context);
void wait(FSMContext *context);
void default_action(FSMContext *context);

/* Действия на переходах */
void prepare(FSMContext *context);
void change(FSMContext *context);
void returnRubl(FSMContext *context);
void error(FSMContext *context);

/* Вспомогательные функции */
EventFSM getEvent(void);
void printChange(void);
void printPrepare(void);
static bool init_coffee_machine(void);

/* ============================================================
 * ТАБЛИЦА СОБЫТИЙ БЕЗ ПРИОРИТЕТОВ
 * ============================================================ */
const EventFSM event_table[] = 
{
    [RUBL_1] = {.event = RUBL_1},
    [RUBL_2] = {.event = RUBL_2},
	[CANCEL] = {.event = CANCEL},
};

/* ============================================================
 * ТАБЛИЦА ДЕЙСТВИЙ СОСТОЯНИЙ
 * ============================================================ */
const StateAction state_table[] = 
{
    [READY] = {.exit = NULL, .entry = ready, .default_action = default_action},
    [WAIT] = {.exit = NULL, .entry = wait, .default_action = default_action},
};

/* ============================================================
 * ТАБЛИЦА ПЕРЕХОДОВ
 * ============================================================ */
const Transition trans_table[] = 
{
    {.current_state = READY, .event = RUBL_1, .next_state = WAIT, .action = NULL},
    {.current_state = READY, .event = RUBL_2, .next_state = READY, .action = prepare},
    {.current_state = READY, .event = CANCEL, .next_state = READY, .action = error},
    {.current_state = WAIT, .event = RUBL_1, .next_state = READY, .action = prepare},
    {.current_state = WAIT, .event = RUBL_2, .next_state = READY, .action = change},
    {.current_state = WAIT, .event = CANCEL, .next_state = READY, .action = returnRubl}
};

/* ============================================================
 * ОПРЕДЕЛЕНИЕ КРНЕЧНОГО АВТОМАТА
 * ============================================================ */

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

	init_coffee_machine();

    while(1) 
    {
        if (dispatchFSM(&coffee_machine, getEvent())) 
            printf("\nEvent handled!\n\n");
        else 
            printf("\nEvent NOT handled (default_action called)\n\n");
    }

    return 0;
}

/* ============================================================
 * РЕАЛИЗАЦИЯ ДЕЙСТВИЙ СОСТОЯНИЙ
 * ============================================================ */

void ready(FSMContext *context)
{
	printf("Ready\n");
}

void wait(FSMContext *context)
{
	printf("Wait\n");
}

void default_action(FSMContext *context)
{
	printf("Error, event dont handle!\n");
}

/* ============================================================
 * РЕАЛИЗАЦИЯ ДЕЙСТВИЙ НА ПЕРЕХОДАХ
 * ============================================================ */
void prepare(FSMContext *context)
{
	printPrepare();
}

void change(FSMContext *context)
{
	printChange();
    printPrepare();
}

void returnRubl(FSMContext *context)
{
	printChange();
}

void error(FSMContext *context)
{
	printf("Error signal CANCEL\n");
}

/* ============================================================
 * ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
 * ============================================================ */
void printChange(void)
{
	printf("Change 1 Rubl\n");
}

void printPrepare(void)
{
	printf("Prepare coffee\n");
}

EventFSM getEvent(void)
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

	return initializeFSM(&coffee_machine, template_fsm);
}