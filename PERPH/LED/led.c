/**
  ******************************************************************************
  * @file    led.h 
  * @author  zam
  * @version V1.0
  * @date    20-3-2018
  * @brief   Header for led.h module
  ******************************************************************************/
#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(LED1_RCC | LED2_RCC | LED3_RCC,ENABLE); //ʹ��GPIOD��ʱ��
	
	GPIO_InitStructure.GPIO_Pin=LED1_GPIO;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;//���
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;  //�������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;  //�������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; //����GPIO
	GPIO_Init(LED1_PORT,&GPIO_InitStructure);
	LED1_OFF;
	
	GPIO_InitStructure.GPIO_Pin=LED2_GPIO;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;//���
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;  //�������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;  //�������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; //����GPIO
	GPIO_Init(LED2_PORT,&GPIO_InitStructure);
	LED2_OFF;
	
	GPIO_InitStructure.GPIO_Pin=LED3_GPIO;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;//���
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;  //�������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;  //�������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; //����GPIO
	GPIO_Init(LED3_PORT,&GPIO_InitStructure);
	LED3_OFF;
}




