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


#ifndef _SCHEDULER_H
#define _SCHEDULER_H

//------------------------------------------------------------------
// defines
//------------------------------------------------------------------
#define SYSTEM_TICK_MS  1      // 1 system tick in milliseconds
#define MAX_TASKS       32

//------------------------------------------------------------------
// typedefs
//------------------------------------------------------------------
typedef struct {
  char active;
  char name[32];
  unsigned int intervaInMs;
  void* funcPtr;
} task;

//------------------------------------------------------------------
// function prototypes
//------------------------------------------------------------------
int addTask(char name[], unsigned int intervaInMs, void* funcPtr);
void sysTick(int sig);
int initSysTick(void);


#endif