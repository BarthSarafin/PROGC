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
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "main.h"
#include "scheduler.h"

//------------------------------------------------------------------
// global variables
//------------------------------------------------------------------


/**
 * taskA:
 * Example task.
 * 
 * @param void
 * @return void
 */
void taskA(void) {

  PRINT("Task A is running...\n");
}

/**
 * taskB:
 * Example task.
 * 
 * @param void
 * @return void
 */
void taskB(void) {

  PRINT("Task B is running...\n");
}

/**
 * taskC:
 * Example task.
 * 
 * @param void
 * @return void
 */
void taskC(void) {

  PRINT("Task C is running...\n");
 
}

/**
 * main:
 * Entry point.
 * 
 * @param int argc              - number of arguments
 * @param const char* argv[]    - arguments
 * @return int                  - error code
 */
int main(int argc, const char* argv[]) {

  // initialize system tick
  if(!initSysTick())
    return EXIT_FAILURE;
  
  addTask("TaskA", 10, (void*)taskA);
  addTask("TaskB", 20, (void*)taskB);
  addTask("TaskC", 40, (void*)taskC);
  
  //do some stuff during idle time
  while (1) {
    sleep(1);
  }

  return EXIT_SUCCESS;

}