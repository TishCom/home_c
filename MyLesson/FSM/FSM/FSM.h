#ifndef FSM_H_
#define FSM_H_

#include <stdbool.h>
#include <inttypes.h>

/* Макрос для определения колличества элементов в таблице */
#define SIZE_TABLE(TABLE)	(sizeof(TABLE) / sizeof(TABLE[0]))

/*Определение типа контекста для дествий в состояниях автомата - необходимо переопределять*/
typedef struct
{
    uint32_t number;
} FSMContext;

/*Определение типа для функций которые отвечают за действия автомата*/
typedef void (*ActionInStateFunc)(FSMContext *context);

/*Определение типа для состояний автомата*/
typedef uint32_t State;

/*Определение типа для событий автомата*/
typedef struct
{
    uint32_t event;
    uint32_t priority;
} EventFSM;

/*Определение типа для таблици действий автомата при входе в состояние и выходе из него*/
typedef struct
{
    ActionInStateFunc entry;
    ActionInStateFunc exit;
    ActionInStateFunc default_action;
} StateAction;

/*Определение типа для таблици переходов автомата*/
typedef struct
{
    State current_state;
    EventFSM event;
    State next_state;
    ActionInStateFunc action;
} Transition;

/*Определение типа шаблона за заполнения обязательных полей конечного автомата*/
typedef struct
{
    State current_state;
    const StateAction *state_table;
    uint32_t number_state;
    const Transition *transition_table;
    uint32_t number_transition;
    FSMContext context;
} FSMTemplateFill;

/*Определение типа для конечного автомата*/
typedef struct
{
    // Базовая структура автомата - инициализировать обязательно
    State current_state;
    const StateAction *state_table;
    uint32_t number_state;
    const Transition *transition_table;
    uint32_t number_transition;
    FSMContext context;

    // Организация очереди событий - инициализировать опционально
    void *event_queue;

    // Организация планировщика - инициализировать опционально
    void *scheduler_data;
} FSM;

/*операция:     инициализация конечного автомата                                                */
/*предусловия:  target_machine указывает на конечный автомат который будем инициализировать,    */
/*              source_machine конечный автомат в который записанны данные для инициализации    */
/*              базовой модели автомата                                                         */
/*постусловия:  конечный автомат инициализирован, функция возвращает false если не удалось      */
/*              инициализировать автомат и true в противном случае                              */
bool initializeFSM(FSM *target_machine, FSMTemplateFill source_machine);

/*операция:     диспетчеризация конечного автомата                                              */
/*предусловия:  machine указывает на инициализированный конечный автомат,                       */
/*              event событие которое должен обработать диспетчер                               */
/*постусловия:  диспетчер обработал событие(совершились действия entry/exit, изменилось         */
/*              автомата и т.д.), функция возвращает false если не удалось обработать событие   */
/*              и true в противном случае                                                       */
bool dispatchFSM(FSM *machine, EventFSM event);

/*операция:     получение текущего состояния конечного автомата                                 */
/*предусловия:  machine указывает на инициализированный конечный автомат,                       */
/*              в current_state считывается текущее состояние конечного автомата                */
/*постусловия:  получили текущее состояние конечного автомата, функция возвращает false если не */
/*              удалось обработать событие и true в противном случае                            */
bool getStateFSM(const FSM *machine, State *current_state);

/*операция:     установка нового состояния конечного автомата                                   */
/*предусловия:  machine указывает на инициализированный конечный автомат,                       */ 
/*              в set_state находится состояние конечного автомата которое мы установим         */
/*постусловия:  установили новое состояние конечного автомата, функция возвращает false если не */
/*              удалось обработать событие и true в противном случае                            */
bool setStateFSM(FSM *machine, State set_state);

#endif