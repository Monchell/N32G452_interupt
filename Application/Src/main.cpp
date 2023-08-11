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



/** �������ȼ� */
#define START_TASK_PRIO				1
#define COUNT_TASK_PRIO				2

/** �����ջ��С */
#define START_TASK_SIZE 			64  
#define COUNT_TASK_SIZE 		 	64

/** ��ʼ������ */
TaskHandle_t Start_Task_Handler;
TaskHandle_t Count_Task_Handler;


/** ��ʼ������ */
void start_task(void *pvParameters);


RCC_ClocksType rcc_clock;//��ȡʱ�ӷ�Ƶ���

/**
 * @brief  Main program.
 */
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ�������
	RCC_GetClocksFreqValue(&rcc_clock);//��ȡʱ������ʱ��Ƶ�ʣ�����������
	NZ_Delay_init();//ʱ�ӳ�ʼ��
	mc_timer2_init();
	mc_timer3_init();
	
	xTaskCreate((TaskFunction_t )start_task,            //������
							(const char*    )"start_task",          //�������ƣ���ʱ����Ҫ��ӡ�����ʱ�����֪�����ĸ��������
              (uint16_t       )START_TASK_SIZE,       //�����ջ��С
              (void*          )NULL,                  //���ݸ��������Ĳ���
              (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
              (TaskHandle_t*  )&Start_Task_Handler);  //������
	vTaskStartScheduler();          //�����������
}


//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
    //����LED0����
    xTaskCreate((TaskFunction_t )count_task,     	
                (const char*    )"count_task",   	
                (uint16_t       )COUNT_TASK_SIZE,
                (void*          )NULL,				
                (UBaseType_t    )COUNT_TASK_PRIO,	
                (TaskHandle_t*  )&Count_Task_Handler);   
																
    vTaskDelete(Start_Task_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

/**
 * @}
 */
