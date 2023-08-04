/**
 * @file main.cpp
 * @author Monchell
 * @version v1.0.0
 *
 * @copyright free
 */
#include "main.h"
#include "timer.h"
#include <stdio.h>
#include <stdint.h>

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
	
	while(1)
	{
		myus = TIM_GetCnt(TIM2);
	}
	
	
	

}
/**
 * @}
 */
