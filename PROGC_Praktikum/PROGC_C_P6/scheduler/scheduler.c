/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur   -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences) -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Project     : mini scheduler
 * -- Description : a simple time-sliced scheduler (non-preemptive)
 * --
 * -----------------------------------------------------------------
 * --
 * -- Change History
 * -- Date     | Name     | Modification
 * ------------|----------|-----------------------------------------
 * -- 10.02.11 | fisa     | file created
 * -----------------------------------------------------------------
 */


//------------------------------------------------------------------
// includes
//------------------------------------------------------------------
#include <signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "scheduler.h"


//------------------------------------------------------------------
// global variables
//------------------------------------------------------------------
static task tasks[32];

/**
 * addTask:
 * Register a new task.
 * 
 * @param char name[]               - task name
 * @param unsigned int intervaInMs  - repetive interval in milliseconds
 * @param void* funcPtr             - pointer to the task function
 * @return int                      - status
 */
int addTask(char name[], unsigned int intervaInMs, void* funcPtr) {
  
  static unsigned short nbOfTasks = 0;
  
  if(nbOfTasks <= MAX_TASKS) {
    
    //TODO: set the values for a Task in the Array
    
    ++nbOfTasks;
  }
  else {
    PRINT("Task \"%s\" could not be added.\n", name)
    return FALSE;
  }
    
  PRINT("Task \"%s\" added.\n", name)
  return TRUE;
}


/**
 * sysTick:
 * System ticks. 
 * 
 * @param int sig               - signal type
 * @return void      
 */
void sysTick(int sig) {
    static unsigned int sysTickCnt = 0;     
    unsigned int localSysTickCnt, i;
    void (*func)();

    ++sysTickCnt;                      //note: each overflow will result in a wrong scheduling -> with 1ms systick all 49.7 days 
    localSysTickCnt = sysTickCnt;      //save the global systick counter on the local function stack
    
    //TODO: scheduler
}    


/**
 * initSysTick:
 * Initialize system tick.
 * 
 * @param void
 * @return int      - status     
 */
int initSysTick(void) {

  struct itimerval timer;
       
  //establish a handler for SIGALRM signals
  signal(SIGALRM, sysTick);

  //set systick interval
  timer.it_interval.tv_usec = SYSTEM_TICK_MS*1000;
  timer.it_interval.tv_sec = 0;
  timer.it_value.tv_usec = SYSTEM_TICK_MS*1000;
  timer.it_value.tv_sec = 0;
  
  return (setitimer(ITIMER_REAL, &timer, NULL) == 0);
}

/**
 * stopSysTick:
 * Initialize system tick.
 * 
 * @param void
 * @return int      - status
 */
int stopSysTick(void) {

  struct itimerval timer;

  //set systick interval
  timer.it_interval.tv_usec = 0;
  timer.it_interval.tv_sec = 0;
  timer.it_value.tv_usec = 0;
  timer.it_value.tv_sec = 0;
  
  return (setitimer(ITIMER_REAL, &timer, NULL) == 0);
}