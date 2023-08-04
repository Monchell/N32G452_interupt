#include"timer.h"
/**
 * @brief  Configures the different system clocks.
 */
 
 
void mc_timer2_init(void)
{
  /* TIM2 clock enable */
	//使能TIM2的时钟
  RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
	

	/* Enable the TIM2 global Interrupt */
	//中断配置
	NVIC_InitType NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQn;//选中timer2中断
	//优先级配置，抢占优先级和子优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;//使能
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_TimeBaseInitType TIM_TimeBaseStructure;

  /* Time base configuration */
	//分频和计数设置
  TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.Period    = (uint16_t) 1000 - 1;
  TIM_TimeBaseStructure.Prescaler = (uint16_t) 72 - 1;
	TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
  TIM_InitTimeBase(TIM2, &TIM_TimeBaseStructure); 	//写入定时器配置	
	
	TIM_ClearFlag(TIM2,TIM_FLAG_UPDATE);//清楚更新中断标志位
	TIM_ConfigInt(TIM2,TIM_INT_UPDATE, ENABLE);//使能更新中断
	
	TIM_Enable(TIM2,ENABLE);//开始工作
	
}