/**
 * @file    Scheduler.c
 * @brief   **Cooperative round robin Scheduler**
 *
 * This is a very simple but yet effective cooperative round robin Scheduler, it is designed to
 * register tasks in static memory that should be provided by the application in the form of
 * Task_TypeDef variable type, also the number of Task should be specied at the beginning and
 * cannot be changed in running time. It is responsibility of the user to guaranty each Task
 * does not consume more than the time required that could affect the other tasks.
 *
 * Software timers are an optional resource that can be use with the Schedulerm, each Timer
 * shall be register previous use, and those will decrement on each tick until reaching zero,
 * after that the Timer will stop and can be re-started.
 *
 * The systick Timer is used trough the HAL_SysTick functions as a means of the tick counter
 * it is not advice to modify the default configuration that runs the tick each milliseconds
 *
 */
#include <stdint.h>
#include "scheduler.h"
#include "bsp.h"
#include "Osif.h"

/**
  * @defgroup UTEST macro to enable unit testing
  @{ */
#ifdef UTEST
#define STATIC    /*!< remove static qualifier*/
#define FOREVER 0 /*!< remove infinite loop */
#else
#define STATIC  static /*!< keep static qualifier*/
#define FOREVER 1      /*!< infinite loop */
#endif
/**
  @} */

/**
  * @defgroup Boolean true and flase definitions
  @{ */
#ifndef FALSE
#define FALSE 0u /*!< FALSE definition */
#endif

#ifndef TRUE
#define TRUE 1u /*!< TRUE definition */
#endif
/**
  @} */

STATIC void Inits_Dispatch( SchedulerType *Scheduler );
STATIC void Tasks_Dispatch( SchedulerType *Scheduler );
STATIC void Timers_Dispatch( SchedulerType *Scheduler );

/**
 * @brief   **Initialization Scheduler Function**
 *
 * The function will set-up the main Scheduler characteristics like the number of Task to run,
 * the tick base time and the static memory to allocate the Task control blocks, it is mandatory
 * to call this function before any other in this driver, the user is responsible to pass the right
 * value for the arguments.
 *
 * @param   Scheduler  Scheduler control structure
 */
void Scheduler_Init( SchedulerType *Scheduler, uint32_t TickBase, uint8_t Tasks, TaskType *TasksBuffer, uint8_t Timers, TimerType *TimerBuffer )
{
    Scheduler->Tick         = TickBase;
    Scheduler->Tasks        = Tasks;
    Scheduler->Timers       = Timers;
    Scheduler->TaskPtr      = TasksBuffer;
    Scheduler->TimerPtr     = TimerBuffer;

    Scheduler->TasksCount  = 0u;
    Scheduler->TimersCount = 0u;
}

/**
 * @brief   **Scheduler Periodic Function**
 *
 * The main Scheduler function, it is in charge of running the initialization functions just one time
 * before the tasks. After this step the function will loop through the tasks to run previously asking
 * if it is time to run accordingly to the Period registered on each of them. The function won't return
 * by any means since it is looping inside a __while(1u)__ forever. The algorithm is pretty simple since
 * first Task to dispatch will be the first registered with the **Scheduler__RegisterTask** function
 *
 * @param   Scheduler Scheduler control structure
 *
 */
void Scheduler_MainFunction( SchedulerType *Scheduler )
{
    uint32 tickstart = OsIf_GetCounter( OSIF_COUNTER_SYSTEM );

    Inits_Dispatch( Scheduler );

    do /* cppcheck-suppress misra-c2012-14.4 ; this is an infinite loop */
    {
        /*The configured tick has Elapsed*/
        if( ( OsIf_GetCounter( OSIF_COUNTER_SYSTEM ) - tickstart ) >= Scheduler->Tick )
        {
            tickstart = 0u; /* Reset timer */
            /*Scan all registered timers*/
            Timers_Dispatch( Scheduler );
            /*Scan all registered Task*/
            Tasks_Dispatch( Scheduler );
        }
    } while( FOREVER );
}

/**
 * @brief   **Register Tasks to Run**
 *
 * This is the function that will allow to register a Task to run within the Scheduler with the
 * periodicity indicated as one of the parameters, a init function is optional. Only a maximum of
 * __SchedulerType.Tasks__ can be registered if user try to register beyond this value it
 * wont work. Also the function validates parameters __TaskPtr__ be different than NULL and __Period__
 * be a multiple of the Scheduler tick.
 *
 * @param   Scheduler  Scheduler control structure
 * @param   InitPtr     The initialization function for the Task to register, if no init function is
 *                      needed then a NULL value can be passed
 * @param   TaskPtr     The function that should run periodically, it is mandatory this function
 *                      do not block the CPU more than is required
 * @param   Period      The time in milliseconds the Task function should run, this value has to be
 *                      larger that the tick and multiple
 *
 * @return  A Task ID different from zero is returned if the Task was registered with no errors other wise the Task wont
 *          be register and the value returned will be a #FALSE
 *
 * @note the Scheduler paramters shall be initialized prior to call this function
 */
uint8_t Scheduler_RegisterTask( SchedulerType *Scheduler, void (*InitPtr)(void), void (*TaskPtr)(void), uint32_t Period )
{
    uint8_t Task = FALSE;

    if( ( Scheduler->TasksCount < Scheduler->Tasks ) && ( TaskPtr != NULL ) && ( Period >= Scheduler->Tick ) && ( ( Period % Scheduler->Tick ) == 0u ) )
    {
        Scheduler->TaskPtr[ Scheduler->TasksCount ].InitFunc  = InitPtr;
        Scheduler->TaskPtr[ Scheduler->TasksCount ].TaskFunc  = TaskPtr;
        Scheduler->TaskPtr[ Scheduler->TasksCount ].Period    = Period;
        Scheduler->TaskPtr[ Scheduler->TasksCount ].Elapsed   = Period;
        Scheduler->TaskPtr[ Scheduler->TasksCount ].StartFlag = TRUE;
        Scheduler->TasksCount++;
        Task = Scheduler->TasksCount;
    }

    return Task;
}

/**
 * @brief   **Stop Tasks**
 *
 * This is the function that will allow to register a Task to stop from running within the Scheduler.
 * the function only set the __StartFlag__ to __FALSE__ which is used internally by the Scheduler to
 * decided if a Task runs or not
 *
 * @param   Scheduler  Scheduler control structure
 * @param   Task        The Task ID, it shall be number from 1 to n Task registered
 *
 * @return  A #TRUE is returned if the Task was stop was registered otherwise it will return a
 *          #FALSE
 *
 * @note the __Scheduler__ parameter shall be initialized prior to call this function
 */
uint8_t Scheduler_StopTask( SchedulerType *Scheduler, uint8_t Task )
{
    uint8_t error = FALSE;

    if( ( Task > 0u ) && ( Task <= Scheduler->TasksCount ) )
    {
        Scheduler->TaskPtr[ Task - 1u ].StartFlag = FALSE;
        error                                     = TRUE;
    }
    return error;
}

/**
 * @brief   **Start Tasks**
 *
 * This is the function that will allow to register a Task to run after been stop from running within
 * the Scheduler. the function only set the __StartFlag__ to __TRUE__ which is used internally by the
 * Scheduler to decided if a Task runs or not. By default the flag is set when a Task is been registered
 * succsefully.
 *
 * @param   Scheduler  Scheduler control structure
 * @param   Task        The Task ID, it shall be number from 1 to n Task registered
 *
 * @return  A #TRUE is returned if the Task was start was registered otherwise it will return a
 *          #FALSE
 *
 * @note the __Scheduler__ paramter shall be initialized prior to call this function
 */
uint8_t Scheduler_StartTask( SchedulerType *Scheduler, uint8_t Task )
{
    uint8_t error = FALSE;

    if( ( Task > 0u ) && ( Task <= Scheduler->TasksCount ) )
    {
        Scheduler->TaskPtr[ Task - 1u ].StartFlag = TRUE;
        error                                     = TRUE;
    }
    return error;
}

/**
 * @brief   **Update Task Period**
 *
 * This is the function that will allow to register a Task to change its periodicity from the one
 * that was set before. The function only set the __Period__ and __Elapsed__ with the new Period.
 *
 * @param   Scheduler  Scheduler control structure
 * @param   Task        The Task ID, it shall be number from 1 to n Task registered
 * @param   Period      New Period time in milliseconds
 *
 * @return  A __TRUE__ is returned if the Task was start was registered otherwise it will return a
 * __FALSE__
 *
 * @note the __Scheduler__ parameter shall be initialized prior to call this function
 */
uint8_t Scheduler_PeriodTask( SchedulerType *Scheduler, uint8_t Task, uint32_t Period )
{
    uint8_t error = FALSE;

    if( ( Task > 0u ) && ( Task <= Scheduler->TasksCount ) )
    {
        Scheduler->TaskPtr[ Task - 1u ].Period  = Period;
        Scheduler->TaskPtr[ Task - 1u ].Elapsed = Period;
        error                                   = TRUE;
    }
    return error;
}

/**
 * @brief   **Register Timer to use**
 *
 * The function will register a software Timer to run with a given Timeout, the value will be
 * decremented on each tick. A Timer can not be register if the Timeout is less than the Scheduler
 * tick or a non multiple value.
 *
 * @param   Scheduler  Scheduler control structure
 * @param   Timeout     The Timeout in milliseconds for the Timer to decrease
 * @param   CallbackPtr The callback function to run when the Timer reach zero, if no callback is
 *
 * @return An id different from zero is returned if the Timer was registered with no errors other wise the Timer
 *          wont be register and the value returned will be a #FALSE
 */
uint8_t Scheduler_RegisterTimer( SchedulerType *Scheduler, uint32_t Timeout, void (*CallbackPtr)(void) )
{
    uint8_t Timer = FALSE;

    if( ( Scheduler->TimersCount < Scheduler->Timers ) && ( Timeout >= Scheduler->Tick ) && ( ( Timeout % Scheduler->Tick ) == 0u ) )
    {
        Scheduler->TimerPtr[ Scheduler->TimersCount ].Timeout     = Timeout;
        Scheduler->TimerPtr[ Scheduler->TimersCount ].Count       = 0u;
        Scheduler->TimerPtr[ Scheduler->TimersCount ].CallbackPtr = CallbackPtr;
        Scheduler->TimerPtr[ Scheduler->TimersCount ].StartFlag   = FALSE;
        Scheduler->TimersCount++;
        Timer = Scheduler->TimersCount;
    }

    return Timer;
}

/**
 * @brief   **Get the current Timer time**
 *
 * The function will return the current decremented time in milisecond for the asked Timer, if no
 * valid Timer is requested a value of zero will be returned.
 *
 * @param   Scheduler  Scheduler control structure
 * @param   Timer     The Timer to get its current time a number from 0 to SchedulerType.Timers
 *
 * @return A value betwen zero and the Timeout registered for the requested Timer
 */
uint32_t Scheduler_GetTimer( SchedulerType *Scheduler, uint8_t Timer )
{
    uint32_t Time = 0u;

    if( ( Timer > 0u ) && ( Timer <= Scheduler->TimersCount ) )
    {
        Time = Scheduler->TimerPtr[ Timer - 1u ].Count;
    }

    return Time;
}

/**
 * @brief   **Set a new Timer Timeout value**
 *
 * The function will set a new Timeout for an already registered Timer, if no valid Timer or a valid
 * Timeout is set the function wont take any effect, also this function wont stop the Timer Count
 * neither start the Count.
 *
 * @param   Scheduler  Scheduler control structure
 * @param   Timer     The Timer to get its current time a number from 0 to Scheduler_HandleTypeDef.timers
 * @param   Timeout     The new Timer Timeout value to decrement
 *
 * @retval  #TRUE if the Timer was reloaded otherwise #FALSE
 */
uint8_t Scheduler_ReloadTimer( SchedulerType *Scheduler, uint8_t Timer, uint32_t Timeout )
{
    uint8_t error = FALSE;

    if( ( Timer > 0u ) && ( Timer <= Scheduler->TimersCount ) )
    {
        Scheduler->TimerPtr[ Timer - 1u ].Timeout = Timeout;
        /*reload current Count if Timer is active*/
        if( Scheduler->TimerPtr[ Timer - 1u ].StartFlag == TRUE )
        {
            Scheduler->TimerPtr[ Timer - 1u ].Count = Scheduler->TimerPtr[ Timer - 1u ].Timeout;
        }
        error = TRUE;
    }
    return error;
}

/**
 * @brief   **Start decrementing the Timer Count**
 *
 * The function will start the Timer decrement Count on each tick only if the Timer is registered,
 * This is the only mechanism to start a Timer, when a Timer reach its Count to zero the Timer will
 * stop nad only this function can re-start the Count again.
 *
 * @param   Scheduler  Scheduler control structure
 * @param   Timer     The Timer to start, any number from 0 to Scheduler_HandleTypeDef.timers
 *
 * @retval  #TRUE if the Timer was started otherwise #FALSE
 */
uint8_t Scheduler_StartTimer( SchedulerType *Scheduler, uint8_t Timer )
{
    uint8_t error = FALSE;

    if( ( Timer > 0u ) && ( Timer <= Scheduler->TimersCount ) )
    {
        Scheduler->TimerPtr[ Timer - 1u ].Count     = Scheduler->TimerPtr[ Timer - 1u ].Timeout;
        Scheduler->TimerPtr[ Timer - 1u ].StartFlag = TRUE;
        error                                       = TRUE;
    }
    return error;
}

/**
 * @brief   **Stop decrementing the Timer Count**
 *
 * The function will stop the Timer decrement Count on each tick only if the Timer is registered,
 * This is the only mechanism to stop a Timer. The function only set the flag StartFlag to FALSE.
 *
 * @param   Scheduler  Scheduler control structure
 * @param   Timer     The Timer to start, any number from 0 to Scheduler_HandleTypeDef.timers
 *
 * @return  A __TRUE__ is returned if the stoped Timer was registered otherwise it will return a
 * __FALSE__
 */
uint8_t Scheduler_StopTimer( SchedulerType *Scheduler, uint8_t Timer )
{
    uint8_t error = FALSE;

    if( ( Timer > 0u ) && ( Timer <= Scheduler->TimersCount ) )
    {
        Scheduler->TimerPtr[ Timer - 1u ].StartFlag = FALSE;
        error                                       = TRUE;
    }
    return error;
}

/**
 * @brief   **Run the Task initial functions**
 *
 * The function will stop the Timer decrement Count on each tick only if the Timer is registered,
 * This is the only mechanism to stop a Timer. The function only set the flag StartFlag to FALSE.
 *
 * @param   Scheduler  Scheduler control structure
 */
STATIC void Inits_Dispatch( SchedulerType *Scheduler )
{
    for( uint8_t i = 0u; i < Scheduler->TasksCount; i++ )
    {
        /*Only run those init functions truly registered*/
        if( Scheduler->TaskPtr[ i ].InitFunc != NULL )
        {
            /*Init registered Task*/
            Scheduler->TaskPtr[ i ].InitFunc( );
        }
    }
}

/**
 * @brief   **Stop decrementing the Timer Count**
 *
 * The function will stop the Timer decrement Count on each tick only if the Timer is registered,
 * This is the only mechanism to stop a Timer. The function only set the flag StartFlag to FALSE.
 *
 * @param   Scheduler  Scheduler control structure
 */
STATIC void Tasks_Dispatch( SchedulerType *Scheduler )
{
    /*Scan all registered Task*/
    for( uint8_t i = 0u; i < Scheduler->TasksCount; i++ )
    {
        /*Only run those tasks that are started*/
        if( Scheduler->TaskPtr[ i ].StartFlag == TRUE )
        {
            /*Only run those tasks that already has its Elapsed time*/
            if( Scheduler->TaskPtr[ i ].Elapsed >= Scheduler->TaskPtr[ i ].Period )
            {
                Scheduler->TaskPtr[ i ].Elapsed = 0u;
                /*Run Task*/
                Scheduler->TaskPtr[ i ].TaskFunc( );
            }
        }
        /*Increment the Task Elapsed time in ticks*/
        Scheduler->TaskPtr[ i ].Elapsed += Scheduler->Tick;
    }
}

/**
 * @brief   **Stop decrementing the Timer Count**
 *
 * The function will stop the Timer decrement Count on each tick only if the Timer is registered,
 * This is the only mechanism to stop a Timer. The function only set the flag StartFlag to FALSE.
 *
 * @param   Scheduler  Scheduler control structure
 */
STATIC void Timers_Dispatch( SchedulerType *Scheduler )
{
    for( uint8_t i = 0u; i < Scheduler->TimersCount; i++ )
    {
        /*Only run those Timer that are started*/
        if( Scheduler->TimerPtr[ i ].StartFlag == TRUE )
        {
            /*Decrement Timer Count by one tick*/
            Scheduler->TimerPtr[ i ].Count -= Scheduler->Tick;
            /*If Timer reach Count to zero, deactivate Timer*/
            if( Scheduler->TimerPtr[ i ].Count == 0u )
            {
                Scheduler->TimerPtr[ i ].StartFlag = FALSE;
                /*If a callback was registered, run*/
                if( Scheduler->TimerPtr[ i ].CallbackPtr != NULL )
                {
                    Scheduler->TimerPtr[ i ].CallbackPtr( );
                }
            }
        }
    }
}
