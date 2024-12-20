/**
 * @file kernel.h
 * @brief Header file for the kernel implementation in an embedded RTOS.
 *
 * This file contains function declarations, constants, and macros for
 * initializing and launching the kernel, managing threads, and setting
 * timing parameters.
 */

#ifndef __KERNEL_H_
#define __KERNEL_H_

#include <stdint.h>
#include "stm32f446xx.h"

#define PERIOD      100

/**
 * @brief Initializes the LunaRTOS kernel.
 *
 * Sets up necessary resources such as thread control blocks (TCBs),
 * stack memory, and system tick configuration.
 */
void KernelInit(void);

/**
 * @brief Launches the LunaRTOS kernel.
 *
 * Starts the kernel's scheduler and begins execution of the created threads.
 * This function does not return as the kernel takes over the program flow.
 */
void KernelLaunch(uint32_t quanta);

/**
 * @brief Creates threads and assigns tasks to them.
 *
 * @param task0 Pointer to the function representing the first thread's task.
 * @param task1 Pointer to the function representing the second thread's task.
 * @param task2 Pointer to the function representing the third thread's task.
 *
 * @return 0 if thread creation is successful, non-zero otherwise.
 *
 * Sets up thread control blocks (TCBs) for each task and prepares them
 * for scheduling.
 */
uint8_t KernelCreateThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void));

/**
 * @brief Voluntarily yields the processor to allow other threads to execute.
 *
 * This function is used by the currently running thread to voluntarily
 * yield its execution time, giving the scheduler an opportunity to
 * select another thread to run. It is typically invoked when the
 * current thread has completed its work and can wait until its
 * next scheduling cycle.
 *
 * @note This function should only be called from threads managed
 * by the kernel. Calling this function from an interrupt context
 * or an uninitialized thread context may lead to undefined behavior.
 */
void ThreadYield(void);

/**
 * @brief Initializes the TIM2 peripheral to generate a 1 Hz interrupt.
 *
 * Configures the TIM2 timer to operate at a frequency of 1 Hz,
 * generating periodic interrupts. This function sets up the timer
 * prescaler, auto-reload value, and interrupt enable, making it
 * suitable for timing or periodic task execution.
 *
 * @details This initialization routine assumes the timer clock is
 * correctly configured. The interrupt generated by TIM2 can be used
 * for tasks such as toggling LEDs, sampling sensors, or scheduling
 * events in an RTOS environment.
 *
 * @note Ensure the TIM2 interrupt handler is implemented appropriately
 * in the ISR vector table to handle the generated interrupts. Also,
 * ensure the global interrupt enable bit is set before calling this function.
 */
void TIM2_1Hz_Interrupt_Init(void);

/**
 * @brief A sample task for testing round-robin scheduling in the RTOS.
 *
 * This function represents the third task in the system and is primarily
 * used to validate the round-robin scheduling functionality of the RTOS.
 * It performs a simple operation, such as incrementing a variable in order
 * to demonstrate task switching between multiple threads.
 *
 * @details The behavior of this task should be observable to confirm
 * proper context switching and equal time allocation among tasks in
 * a round-robin scheduling algorithm. This task will be defined in
 * main.c
 *
 * @note Ensure that task3 is created and added to the scheduler's
 * task list before testing. The task should be designed to complete
 * within the time slice allocated by the RTOS.
 */
void task3(void);

#endif // __KERNEL_H_
