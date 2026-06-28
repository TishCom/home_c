#include "fsm_callable.h"

/*--------------------------------------------*
 * Прототипы статических функций
 *--------------------------------------------*/

/*--------------------------------------------*
 * Публичные функции (внешний интерфейс)
 *--------------------------------------------*/

/* РЕАЛИЗАЦИЯ ФУНКЦИЙ УПРАВЛЕНИЯ ЖИЗНЕННЫМ ЦИКЛОМ */

/*оформление данных для вызываемого автомта*/
FSMCallableData* fsmCallableDataCreate(FSMCallableData template_callable_fsm)
{

}

/*освобождение памяти выделенной для данных необходимых для вызываемого автомта*/
void fsmCallableDataDestroy(FSMCallableData *data)
{
    
}

/*проверка, являются ли данные необходимые для вызываемого автомта инициализироваными*/
bool fsmCallableDataIsInitialise(const FSMCallableData *data)
{
    
}

/* РЕАЛИЗАЦИЯ ФУНКЦИЙ ДОСТУПА К ПОЛЯМ */

/*установка адреса вызывающего автомата*/
void fsmCallableDataSetCaller(FSMCallableData *data, FSM *caller)
{
    
}

/*получение адреса вызывающего автомата*/
FSM* fsmCallableDataGetCaller(const FSMCallableData *data)
{
    
}

/*установка значения состояния в которое нужно перейти в родительском автомате после завершения дочернего*/
void fsmCallableDataSetReturnState(FSMCallableData *data, State return_state)
{
    
}

/*получение значения состояния в которое нужно перейти в родительском автомате после завершения дочернего*/
State fsmCallableDataGetReturnState(const FSMCallableData *data)
{
    
}

/*установка значения конечного состояния дочернего автомата*/
void fsmCallableDataSetFinishState(FSMCallableData *data, State finish_state)
{
    
}

/*получение значения конечного состояния дочернего автомата*/
State fsmCallableDataGetFinishState(const FSMCallableData *data)
{
    
}

/*установка значения ночального состояния дочернего автомата*/
void fsmCallableDataSetStartState(FSMCallableData *data, State start_state)
{
    
}

/*получение значения ночального состояния дочернего автомата*/
State fsmCallableDataGetStartState(const FSMCallableData *data)
{
    
}

/*устанавка указанного автомат как вызыванный*/
void fsmCallableDataSetCalled(FSMCallableData *data)
{
    
}

/*устанавка указанного автомат как не вызыванный*/
void fsmCallableDataResetCalled(FSMCallableData *data)
{
    
}

/*проверка, является ли автомат вызванным*/
bool fsmCallableDataIsCalled(const FSMCallableData *data)
{
    
}

/*устанавка указанного автомат как завершившего работу*/
void fsmCallableDataSetFinished(FSMCallableData *data)
{
    
}

/*устанавка указанного автомат как работайющий*/
void fsmCallableDataResetFinished(FSMCallableData *data)
{
    
}

/*проверка, является ли автомат работающим*/
bool fsmCallableDataIsFinished(const FSMCallableData *data)
{
    
}

/*указывает родительскому автомато ждать завершения этого дочернего, это нужно, чтобы*/
/*родительский автомат не обрабатывал другие события, пока дочерний не завершится*/
void fsmCallableDataSetWaiting(FSMCallableData *data)
{
    
}

/*указывает родительскому автомато не ждать завершения этого дочернего*/
void fsmCallableDataResetWaiting(FSMCallableData *data)
{
    
}

/*проверка, нужно ли родительскому автомато ждать завершения этого дочернего*/
bool fsmCallableDataIsWaiting(const FSMCallableData *data)
{
    
}

/* РЕАЛИЗАЦИЯ ОСНОВНЫХ ФУНКЦИЙ */

/*вызвать автомат как подпрограмму*/
bool fsmCall(FSM *callee, FSM *caller, State finish_state, State return_state)
{
    
}

/*проверка, является ли автомат работающим*/
bool fsmIsFinished(const FSM *machine)
{
    
}

/*проверка, является ли автомат вызванным*/
bool fsmIsCalled(const FSM *machine)
{
    
}

/*принудительно завершить вызываемый автомат и вернуть управление вызывающему*/
void fsmReturn(FSM *machine)
{
    
}

/*сбросить вызываемый автомат в начальное состояние (с вызовом exit/entry)*/
bool fsmReset(FSM *machine)
{
    
}

/*--------------------------------------------*
 * Статические функции (реализация)
 *--------------------------------------------*/