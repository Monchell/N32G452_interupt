#include "timer.h"
#include "Freertos.h"
#include "task.h"
/**
 * @brief  Configures the different system clocks.
 */
 
 
/**
* @brief Tim2���óɼ�����
* @note  Tim2���ó���1ms��һ���жϣ����ϼ�����1000װ��ֵ��1000hz��
*/

void mc_timer2_init(void)
{
  /* TIM2 clock enable */
	//ʹ��TIM2��ʱ��
  RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
	

	/* Enable the TIM2 global Interrupt */
	//�ж�����
	NVIC_InitType NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQn;//ѡ��timer2�ж�
	//���ȼ����ã���ռ���ȼ��������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;//ʹ��
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_TimeBaseInitType TIM_TimeBaseStructure;

  /* Time base configuration */
	//��Ƶ�ͼ�������
  TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.Period    = (uint16_t) 1000 - 1;
  TIM_TimeBaseStructure.Prescaler = (uint16_t) 72 - 1;
	TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
  TIM_InitTimeBase(TIM2, &TIM_TimeBaseStructure); 	//д�붨ʱ������	
	
	TIM_ClearFlag(TIM2,TIM_FLAG_UPDATE);//��������жϱ�־λ
	TIM_ConfigInt(TIM2,TIM_INT_UPDATE, ENABLE);//ʹ�ܸ����ж�
	
	TIM_Enable(TIM2,ENABLE);//��ʼ����
	
}


void mc_timer3_init(void)
{
  /* TIM2 clock enable */
	//ʹ��TIM2��ʱ��

  RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
	

	/* Enable the TIM2 global Interrupt */
	//�ж�����
	NVIC_InitType NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;//ѡ��timer2�ж�
	//���ȼ����ã���ռ���ȼ��������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;//ʹ��
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_TimeBaseInitType TIM_TimeBaseStructure;

  /* Time base configuration */
	//��Ƶ�ͼ�������
  TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.Period    = (uint16_t) 1000 - 1;
  TIM_TimeBaseStructure.Prescaler = (uint16_t) 72 - 1;
	TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
  TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure); 	//д�붨ʱ������	
	
	TIM_ClearFlag(TIM3,TIM_FLAG_UPDATE);//��������жϱ�־λ
	TIM_ConfigInt(TIM3,TIM_INT_UPDATE, ENABLE);//ʹ�ܸ����ж�
	
	TIM_Enable(TIM3,ENABLE);//��ʼ����
	
}






/**
 * @brief ��ʼ��SYSTICK,����������ʱ����
 * @note  SYSTICK��ʱ�ӹ̶�ΪHCLKʱ��
 */
static u32  fac_us = 0;	 //us��ʱ������			   
static u32  fac_ms = 0;	 //ms��ʱ������
void NZ_Delay_init(void)
{
	u32 reload;

	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//ѡ���ⲿʱ��HCLK 144M����ʱ�δ�1s������144M��
	fac_us = (SystemCoreClock / (1000000));					//SystemCoreClockΪϵͳʱ�ӣ�fac_us�����1us�δ����M��

	reload = (SystemCoreClock / 1000000);						//ÿ���ӵļ������� ��λΪM
	reload *= (1000000 / configTICK_RATE_HZ);       //����configTICK_RATE_HZ�趨���ʱ��
	fac_ms = (1000 / configTICK_RATE_HZ);				    //����OS���Ժ�����ʱ�����ٵ�λ,��OS��Ƶ�ʣ�����Ҳ�ǵδ������Ƶ�ʣ�������

	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;			  //����SYSTICK�ж�
	SysTick->LOAD=reload; 					     					  //ÿ1M/configTICK_RATE_HZ��һ��	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; 				//����SYSTICK   
}


/**
 * @brief us������ʱ����
 * @param nus����Ҫ��ʱ��΢����
 * @note  �����ʱ��ʱ�䵽�˺��뼶������NZ_Delay_xmsʵ��
 */
void NZ_Delay_us(u32 nus)
{
		u32 ticks;
		u32 told,tnow,tcnt = 0;
		u32 reload = SysTick->LOAD;		  //LOAD��ֵ	    	 
		ticks = nus*fac_us; 						//��Ҫ�Ľ����� 
		told  = SysTick->VAL;        		//�ս���ʱ�ļ�����ֵ
		while(1)
		{
				tnow = SysTick->VAL;	
				if(tnow != told)
				{	    
						if(tnow<told)   //����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����
							tcnt += told-tnow;	
						else 
							tcnt += reload-tnow+told;	   
						
						told = tnow;
						if(tcnt >= ticks)	//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�
							break;			
				}  
		};
}

/**
 * @brief ms������ʱ����,������ϵͳ����
 * @param nms����Ҫ��ʱ�ĺ�����
 */

void NZ_Delay_ms(u32 nms)
{
		if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) //ϵͳ�Ѿ�����
		{		
				if(nms >= fac_ms)							//��ʱ��ʱ�����OS������ʱ������ 
				{ 
						vTaskDelay(nms / fac_ms);	 		//FreeRTOS��ʱ
				}
				
				nms %= fac_ms;						//OS�Ѿ��޷��ṩ��ôС����ʱ��,������ͨ��ʽ��ʱ    
		}
		NZ_Delay_us((u32)(nms*1000));				//��ͨ��ʽ��ʱ    
}

/**
 * @brief ms������ʱ����,��������ϵͳ����
 * @param nms����Ҫ��ʱ�ĺ�����
 */
void NZ_Delay_xms(u32 nms)
{
		u32 i;
		for(i=0;i<nms;i++) NZ_Delay_us(1000);  
}


