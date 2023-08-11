/**
 * @file main.cpp
 * @author Monchell
 * @version v1.0.0
 *
 * @copyright free
 */


#include "taskfor_test.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timer.h"


/** 任务函数 */
/**
 * @brief 任务,递归调用一个函数
 * @param pvParameters：任务参数，无
 * @note  这个任务会递归的调用函数，以此不断的增加任务栈使用情况
 */
int tick_task = 0;
void count_task(void *xTasks)
{
	while(1)
	{
		tick_task ++;
		portDISABLE_INTERRUPTS();
		NZ_Delay_xms(5000);
		portENABLE_INTERRUPTS();
		NZ_Delay_xms(5000);
	}
}




/**
 * @}
 */
