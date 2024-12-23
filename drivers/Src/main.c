#include <stdio.h>
#include "led.h"
#include "uart.h"
#include "kernel.h"

#define QUANTA	10

typedef uint32_t TaskProfiler;

TaskProfiler Task0_Profiler = 0, Task1_Profiler = 0,Task2_Profiler = 0;

void motor_run(void);
void motor_stop(void);
void valve_open(void);
void valve_close(void);


void task0(void)
{  
	while(1)
	{
		Task0_Profiler++;
		ThreadYield();
//		motor_run();

	}
}


void task1(void)
{
	while(1)
	{
		Task1_Profiler++;
		ThreadYield();
//		valve_open();
	}
}

void task2(void)
{
	while(1)
	{
		Task2_Profiler++;
		ThreadYield();
//		motor_stop();
	}
}

void task3(void){
	while(1){

	}
}

int main(void)
{


	uart_tx_init();

	/*Initialize Kernel*/
	KernelInit();
	/*Add Threads*/
	KernelCreateThreads(&task0,&task1,&task2);

	/*Set RoundRobin time quanta*/
	KernelLaunch(QUANTA);


}


void motor_run(void)
{
	printf("Motor is starting...\n\r");

}


void motor_stop(void)
{
	printf("Motor is stopping...\n\r");
}

void valve_open(void)
{
	printf("Valve is opening...\n\r");
}


void valve_close(void)
{
	printf("Valve is closing...\n\r");
}


