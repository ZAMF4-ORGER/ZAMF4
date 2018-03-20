 /******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.h 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Header for main.c module
  ******************************************************************************/
#include "main.h"
 int main()
 {	
		SystemInit();
		delay_init(168); 
		NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4);//���ȼ�����  ȫΪ��ռʽ���ȼ�
		SysTick_Config(SystemCoreClock / 1000);			//uCOSʱ��1ms
		ADC_Init_All();
		DAC_Init_ALL();
		Usart_Init_All();
	 LED_Init();
		while(1);
 }



