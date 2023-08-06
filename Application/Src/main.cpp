/**
 * @file main.cpp
 * @author Monchell
 * @version v1.0.0
 *
 * @copyright free
 */
#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "timer.h"
#include "FreeRTOS.h"
#include "task.h"

/**
 * @brief Assert failed function by user.
 * @param file The name of the call that failed.
 * @param line The source line number of the call that failed.
 */
#ifdef USE_FULL_ASSERT
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    while (1)
    {
    }
}
#endif // USE_FULL_ASSERT


/** 任务优先级 */
#define START_TASK_PRIO		1
#define TASK1_PRIO		2
#define TASK2_PRIO		3

/** 任务堆栈大小 */
#define START_TASK_SIZE 		64  
#define TASK1_SIZE 		32
#define TASK2_SIZE 		64

/** 任务句柄 */
TaskHandle_t Start_Task_Handler;
TaskHandle_t Task1_Handler;
TaskHandle_t Task2_Handler;

/** 任务函数 */
void start_task(void *pvParameters);
void task1(void *pvParameters);
void task2(void *pvParameters);

RCC_ClocksType rcc_clock;//获取时钟分频情况
uint16_t myus = 0;

/**
 * @brief  Main program.
 */
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	RCC_GetClocksFreqValue(&rcc_clock);
	mc_timer2_init();
	NZ_Delay_init();
	//while(1);
	//创建开始任务
	xTaskCreate((TaskFunction_t )start_task,            //任务函数
							(const char*    )"start_task",          //任务名称
              (uint16_t       )START_TASK_SIZE,        //任务堆栈大小
              (void*          )NULL,                  //传递给任务函数的参数
              (UBaseType_t    )START_TASK_PRIO,       //任务优先级
              (TaskHandle_t*  )&Start_Task_Handler);   //任务句柄
	vTaskStartScheduler();          //开启任务调度
}


//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
    //创建LED0任务
    xTaskCreate((TaskFunction_t )task1,     	
                (const char*    )"task1",   	
                (uint16_t       )TASK1_SIZE,
                (void*          )NULL,				
                (UBaseType_t    )TASK1_PRIO,	
                (TaskHandle_t*  )&Task1_Handler);   
								
    xTaskCreate((TaskFunction_t )task2,     	
                (const char*    )"task2",   	
                (uint16_t       )TASK2_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )TASK2_PRIO,	
                (TaskHandle_t*  )&Task2_Handler);   
								
    vTaskDelete(Start_Task_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

int task1_tick = 0;
void task1(void *pvParameters)
{	
	//uint32_t* p = (uint32_t*)malloc(64*sizeof(uint32_t));
	while(1)
	{
		task1_tick++;
		vTaskDelay(1000);
	}
	
}

int task2_tick = 0;
void task2(void *pvParameters)
{
	while(1)
	{
		task2_tick += 2;
		vTaskDelay(1000);
	}
}

/**
 * @}
 */
