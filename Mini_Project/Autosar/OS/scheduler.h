/**
 * @file    scheduler.h
 * @brief   **Cooperative round robin scheduler**
 *
 * This is a very simple but yet effective cooperative round robin scheduler, it is designed to
 * register tasks in static memory that should be provided by the application in the form of
 * Task_TypeDef variable type, also the number of task should be specied at the beginning and
 * cannot be changed in running time. It is responsibility of the user to guaranty each task
 * does not consume more than the time required that could affect the other tasks.
 *
 * Software timers are an optional resource that can be use with the scheduler, each timer
 * shall be register previous use, and those will decrement on each tick until reaching zero,
 * after that the timer will stop and can be re-started.
 *
 * The systick timer is used trough the HAL_SysTick functions as a means of the tick counter
 * it is not advice to modify the default configuration that runs the tick each milliseconds
 *
 */
#ifndef SCHEDULER_H_
#define SCHEDULER_H_

/**
 * @brief   Task Control Block definition
 *
 * This is the structure that will define the elements need to controll a given task, the elements
 * will be set using the Scheduler_Register function
 */
typedef struct _TaskType 
{
    uint32_t Period;          /*How often the task shopud run in ms*/
    uint32_t Elapsed;         /*the cuurent elapsed time*/
    uint8_t StartFlag;        /*flag to run task*/
    void (*InitFunc)(void);   /*pointer to init task function*/
    void (*TaskFunc)(void);   /*pointer to task function*/
} TaskType;

/**
 * @brief   Software Timer definition
 *
 * This is the structure that will define the elements need to controll a software timer, the elements
 * will be set using the extern function Scheduler_RegisterTimer function
 */
typedef struct _TimerType
{
    uint32_t Timeout;       /*!< timer timeout to decrement and reload when the timer is re-started */
    uint8_t Count;         /*!< actual timer decrement count */
    uint8_t StartFlag;     /*!< flag to start timer count */
    void(*CallbackPtr)(void);  /*!< pointer to callback function function */
} TimerType;

/**
 * @brief   Scheduler Control Block
 *
 * This is the control structure to define the number of task to run and also the base time for the
 * system tick in milliseconds
 */
typedef struct _SchedulerType
{
    uint8_t Tasks;          /*!< number of task to handle*/
    uint32_t Tick;          /*!< the time base in ms*/
    uint32_t Timeout;       /*!< the number of milliseconds the scheduler should run*/
    uint8_t TasksCount;     /*!< internal task counter*/
    TaskType *TaskPtr;      /*!< Pointer to buffer for the TCB tasks*/
    uint8_t Timers;         /*number of software timer to use*/
    TimerType *TimerPtr;    /*Pointer to buffer timer array*/
    uint8_t TimersCount;    /*!< internal timer counter*/
} SchedulerType;


void Scheduler_Init( SchedulerType *Scheduler, uint32_t TickBase, uint8_t Tasks, TaskType *TasksBuffer, uint8_t Timers, TimerType *TimerBuffer );
void Scheduler_MainFunction( SchedulerType *Scheduler );

uint8_t Scheduler_RegisterTask( SchedulerType *Scheduler, void (*InitPtr)(void), void (*TaskPtr)(void), uint32_t Period );
uint8_t Scheduler_StopTask( SchedulerType *Scheduler, uint8_t Task );
uint8_t Scheduler_StartTask( SchedulerType *Scheduler, uint8_t Task );
uint8_t Scheduler_PeriodTask( SchedulerType *Scheduler, uint8_t Task, uint32_t Period );

uint8_t Scheduler_RegisterTimer( SchedulerType *Scheduler, uint32_t Timeout, void (*CallbackPtr)(void) );
uint32_t Scheduler_GetTimer( SchedulerType *Scheduler, uint8_t Timer );
uint8_t Scheduler_ReloadTimer( SchedulerType *Scheduler, uint8_t Timer, uint32_t Timeout );
uint8_t Scheduler_StartTimer( SchedulerType *Scheduler, uint8_t Timer );
uint8_t Scheduler_StopTimer( SchedulerType *Scheduler, uint8_t Timer );

#endif