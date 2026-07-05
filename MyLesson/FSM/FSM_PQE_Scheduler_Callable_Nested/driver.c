/* ============================================================
 * driver.c - SIMPLEST NESTED AUTOMATON
 * Parent: starts/stops mode
 * Child: just prints that it works
 * ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "fsm.h"
#include "event_buffer_fsm.h"
#include "fsm_callable.h"
#include "fsm_callable_dispatcher.h"

/* ============================================================
 * PARENT STATES
 * ============================================================ */
typedef enum 
{
    P_IDLE = 0,
    P_ACTIVE = 1,
} ParentState_t;

typedef enum 
{
    EVT_START = 0,
    EVT_STOP = 1,
} ParentEvent_t;

/* ============================================================
 * CHILD STATES
 * ============================================================ */
typedef enum 
{
    C_IDLE = 0,
    C_WORK = 1,
} ChildState_t;

typedef enum 
{
    CEVT_RUN = 0,
    CEVT_STOP = 1,
} ChildEvent_t;

/* ============================================================
 * CONTEXT
 * ============================================================ */
typedef struct {
    uint32_t counter;
} AppContext;

static AppContext ctx = {0};
static FSM parent_fsm;
static FSM child_fsm;

/* ============================================================
 * EVENT TABLES
 * ============================================================ */
const EventFSM parent_events[] = 
{
    [EVT_START] = {.event = EVT_START, .priority = 1},
    [EVT_STOP]  = {.event = EVT_STOP, .priority = 1},
};

const EventFSM child_events[] = 
{
    [CEVT_RUN] = {.event = CEVT_RUN, .priority = 1},
    [CEVT_STOP] = {.event = CEVT_STOP, .priority = 1},
};

/* ============================================================
 * PROTOTYPES
 * ============================================================ */
static void parent_idle(void *ctx);
static void parent_active(void *ctx);
static void parent_default(void *ctx);
static void on_start(void *ctx);
static void on_stop(void *ctx);

static void child_idle(void *ctx);
static void child_work(void *ctx);
static void child_default(void *ctx);
static void on_child_run(void *ctx);
static void on_child_stop(void *ctx);

/* ============================================================
 * STATE TABLES
 * ============================================================ */
const StateAction parent_actions[] = 
{
    [P_IDLE]   = {.entry = parent_idle,   .exit = NULL, .default_action = parent_default},
    [P_ACTIVE] = {.entry = parent_active, .exit = NULL, .default_action = parent_default},
};

const StateAction child_actions[] = 
{
    [C_IDLE] = {.entry = child_idle, .exit = NULL, .default_action = child_default},
    [C_WORK] = {.entry = child_work, .exit = NULL, .default_action = child_default},
};

/* ============================================================
 * TRANSITION TABLES
 * ============================================================ */
const Transition parent_trans[] = 
{
    {P_IDLE,   parent_events[EVT_START], P_ACTIVE, on_start},
    {P_ACTIVE, parent_events[EVT_STOP],  P_IDLE,   on_stop},
};

const Transition child_trans[] = 
{
    {C_IDLE, child_events[CEVT_RUN], C_WORK, on_child_run},
    {C_WORK, child_events[CEVT_STOP], C_IDLE, on_child_stop},
};

/* ============================================================
 * MAIN
 * ============================================================ */
int main(void)
{
    printf("\n=== SIMPLE NESTED ===\n");
    printf("s - start, q - stop\n\n");

    /* Parent */
    FSMTemplateFill tpl_parent = {
        .current_state = P_IDLE,
        .state_table = parent_actions,
        .number_state = 2,
        .transition_table = parent_trans,
        .number_transition = 2,
        .context = &ctx
    };
    initializeFSM(&parent_fsm, tpl_parent);
    parent_fsm.event_queue = initializeBufferFSM(10);
    parent_fsm.scheduler_data = NULL;

    /* Child (nested) */
    FSMTemplateFill tpl_child = {
        .current_state = C_IDLE,
        .state_table = child_actions,
        .number_state = 2,
        .transition_table = child_trans,
        .number_transition = 2,
        .context = NULL
    };
    initializeFSM(&child_fsm, tpl_child);
    child_fsm.event_queue = initializeBufferFSM(10);
    child_fsm.scheduler_data = NULL;
    child_fsm.callable_data = NULL;

    printf("Ready!\n\n");

    while (1)
    {
        printf("> ");
        int ch = getchar();
        getchar();

        EventFSM evt;
        switch (ch) {
            case 's': evt = parent_events[EVT_START]; break;
            case 'q': evt = parent_events[EVT_STOP];  break;
            default:
                printf("Use s or q\n");
                continue;
        }

        pushEventQueue(&parent_fsm, evt);
        fsmProcessCallable(&parent_fsm);
        printf("\n");
    }

    return 0;
}

/* ============================================================
 * PARENT
 * ============================================================ */
static void parent_idle(void *ctx)
{
    (void)ctx;
    printf("[P] IDLE\n");
}

static void parent_active(void *ctx)
{
    AppContext *c = (AppContext*)ctx;
    c->counter++;
    printf("[P] ACTIVE (counter: %d)\n", c->counter);
}

static void parent_default(void *ctx)
{
    (void)ctx;
    printf("[P] UNKNOWN\n");
}

static void on_start(void *ctx)
{
    (void)ctx;
    printf("[P] START -> sending CEVT_RUN to child\n");
    pushEventQueue(&child_fsm, child_events[CEVT_RUN]);
    fsmNestedStep(&child_fsm);
}

static void on_stop(void *ctx)
{
    (void)ctx;
    printf("[P] STOP -> sending CEVT_STOP to child\n");
    pushEventQueue(&child_fsm, child_events[CEVT_STOP]);
    fsmNestedStep(&child_fsm);
}

/* ============================================================
 * CHILD (NESTED)
 * ============================================================ */
static void child_idle(void *ctx)
{
    (void)ctx;
    printf("[C] IDLE\n");
}

static void child_work(void *ctx)
{
    (void)ctx;
    printf("[C] WORKING!\n");
}

static void child_default(void *ctx)
{
    (void)ctx;
    printf("[C] UNKNOWN\n");
}

static void on_child_run(void *ctx)
{
    (void)ctx;
    printf("[C] RUN (IDLE -> WORK)\n");
}

static void on_child_stop(void *ctx)
{
    (void)ctx;
    printf("[C] STOP (WORK -> IDLE)\n");
}