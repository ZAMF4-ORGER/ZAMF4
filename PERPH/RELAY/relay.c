/**
  ******************************************************************************
  * @file    relay.c
  * @author  zam
  * @version V1.0
  * @date    20-3-2018
  * @brief   Header for relay.c module
  ******************************************************************************/
#include "relay.h"

void RELAY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RELAY1_RCC,ENABLE); //ʹ��GPIOD��ʱ��
	
	GPIO_InitStructure.GPIO_Pin=RELAY1_GPIO;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;//���
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;  //�������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;  //�������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; //����GPIO
	GPIO_Init(RELAY1_PORT,&GPIO_InitStructure);
	RELAY1_OFF;
}

