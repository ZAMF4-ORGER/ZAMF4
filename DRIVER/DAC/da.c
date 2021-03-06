/**
  ******************************************************************************
  * @file    da.c 
  * @author  zam
  * @version V1.0
  * @date    20-3-2018
  * @brief   Header for da.c module
  ******************************************************************************/
	
	#include "da.h"
	#define DAC_DHR12R2_ADDRESS    0x40007414
	const uint16_t aSine12bit[32] = {
                      2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056,
                      3939, 3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909, 
                      599, 344, 155, 38, 0, 38, 155, 344, 599, 909, 1263, 1647};
					  
	const uint16_t asaw12bit[32] = {
                      0, 132, 264,396,528,660,792,924,1056,1188,1320,1452,1584,1716,1848,1980,
					  	2112,2244,2376,2508,2640,2772,2904,3036,3168,3300,3432,3564,3696,
					  	3828,3960,4092};
	static void TIM6_Config(void)
	{
  		TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
  	/* TIM6 Periph clock enable */
  		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  
  	/* --------------------------------------------------------
  		TIM3 input clock (TIM6CLK) is set to 2 * APB1 clock (PCLK1), 
  		since APB1 prescaler is different from 1.   
    		TIM6CLK = 2 * PCLK1  
    		TIM6CLK = HCLK / 2 = SystemCoreClock /2 
          
  		TIM6 Update event occurs each TIM6CLK/256 
  	Note: 
   			SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
   		Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
   		function to update SystemCoreClock variable value. Otherwise, any configuration
   		based on this variable will be incorrect.    

  		----------------------------------------------------------- */
 	 	/* Time base configuration */
  		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
  		TIM_TimeBaseStructure.TIM_Period = 0xFF;          
  		TIM_TimeBaseStructure.TIM_Prescaler = 0;       
 	 	TIM_TimeBaseStructure.TIM_ClockDivision = 0;    
 	 	TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up;  
 	 	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

  		/* TIM6 TRGO selection */
 		TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
  
 	 	/* TIM6 enable counter */
	  	TIM_Cmd(TIM6, ENABLE);
	}
	static void DAC_Init_IO()
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHB1PeriphClockCmd(DACx_CHANNEL_GPIO_CLK_1, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = DAC_GPIO_PINx_1;
 		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  		GPIO_Init(DAC_GPIO_PORTx_1, &GPIO_InitStructure);

		TIM6_Config();
	}
	void DAC_Ch2_TriangleConfig(void)
	{
		DAC_InitTypeDef  DAC_InitStructure;
		DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
		DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Triangle;
		DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude =DAC_TriangleAmplitude_4095;//设置电压值
		DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
		DAC_Init(DAC_CHANNEL_1, &DAC_InitStructure);

		/* Enable DAC Channel2 */
		DAC_Cmd(DAC_CHANNEL_1, ENABLE);

		/* Set DAC channel2 DHR12RD register */
		DAC_SetChannel2Data(DAC_Align_12b_R, 0);//设置升值高度
	}
static void DAC_Ch2_SineWaveConfig(void)
{
	DMA_InitTypeDef DMA_InitStructure;
  DAC_InitTypeDef DAC_InitStructure;
	
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
  /* DAC channel2 Configuration */
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
  DAC_Init(DAC_Channel_2, &DAC_InitStructure);

  /* DMA1_Stream6 channel7 configuration **************************************/
  DMA_DeInit(DMA1_Stream6);
  DMA_InitStructure.DMA_Channel = DMA_Channel_7;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)DAC_DHR12R2_ADDRESS;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&aSine12bit;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = 32;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream6, &DMA_InitStructure);

  /* Enable DMA1_Stream6 */
  DMA_Cmd(DMA1_Stream6, ENABLE);

  /* Enable DAC Channel2 */
  DAC_Cmd(DAC_Channel_2, ENABLE);

  /* Enable DMA for DAC Channel2 */
  DAC_DMACmd(DAC_Channel_2, ENABLE);
}
	void DAC_Init_ALL()
	{
		DAC_Init_IO();
		DAC_Ch2_SineWaveConfig();
		//DAC_Ch2_TriangleConfig();
	}
	
	
