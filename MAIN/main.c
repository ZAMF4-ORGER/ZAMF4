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
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4);//���ȼ�����  ȫΪ��ռʽ���ȼ�
	SysTick_Config(SystemCoreClock / 1000);			//uCOSʱ��1ms
	Usart_Init_All();
	ADC_Init_All();
	DAC_Init_ALL();
	LED_Init();
	 RELAY_Init();
	 printf("****************************************\r\n");
	 printf("*              �����״�                *\r\n");
	 printf("*             �汾��V1.0               *\r\n");
	 printf("****************************************\r\n");
	 while(1)
	 {
		if(TIME_FLAG.time_sub.flag_1hz)
		{
			TIME_FLAG.time_sub.flag_1hz=FALSE;
			LED1_ON_OFF;
			LED2_ON_OFF;
			LED3_ON_OFF;
			printf("stm32 test ok\r\n");
			UART_SendString(UART4,"stm32 test ok\r\n");
		}
	 }
 }



