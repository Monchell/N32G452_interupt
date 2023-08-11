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


/** ������ */
/**
 * @brief ����,�ݹ����һ������
 * @param pvParameters�������������
 * @note  ��������ݹ�ĵ��ú������Դ˲��ϵ���������ջʹ�����
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
