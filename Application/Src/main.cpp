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
#include "taskfor_test.h"


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
#define START_TASK_PRIO				1
#define COUNT_TASK_PRIO				2

/** 任务堆栈大小 */
#define START_TASK_SIZE 			64  
#define COUNT_TASK_SIZE 		 	64

/** 初始任务句柄 */
TaskHandle_t Start_Task_Handler;
TaskHandle_t Count_Task_Handler;


/** 初始任务函数 */
void start_task(void *pvParameters);


RCC_ClocksType rcc_clock;//获取时钟分频情况

/**
 * @brief  Main program.
 */
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//中断分组设置
	RCC_GetClocksFreqValue(&rcc_clock);//获取时钟树的时钟频率（拿来看看）
	NZ_Delay_init();//时钟初始化
	mc_timer2_init();
	mc_timer3_init();
	
	xTaskCreate((TaskFunction_t )start_task,            //任务函数
							(const char*    )"start_task",          //任务名称，有时候需要打印错误的时候可以知道是哪个任务出错
              (uint16_t       )START_TASK_SIZE,       //任务堆栈大小
              (void*          )NULL,                  //传递给任务函数的参数
              (UBaseType_t    )START_TASK_PRIO,       //任务优先级
              (TaskHandle_t*  )&Start_Task_Handler);  //任务句柄
	vTaskStartScheduler();          //开启任务调度
}


//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
    //创建LED0任务
    xTaskCreate((TaskFunction_t )count_task,     	
                (const char*    )"count_task",   	
                (uint16_t       )COUNT_TASK_SIZE,
                (void*          )NULL,				
                (UBaseType_t    )COUNT_TASK_PRIO,	
                (TaskHandle_t*  )&Count_Task_Handler);   
																
    vTaskDelete(Start_Task_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

/**
 * @}
 */
