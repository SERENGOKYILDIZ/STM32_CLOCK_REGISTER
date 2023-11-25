#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */
uint32_t system_clock;

//--> Using HSE with Register config <--//
void RCC_Config(void)
{
	//-> We can change a specific byte value with '|=' (OR).
	//-> We can write the new value over the current value with '&=' (AND).
	//-> The '~' sign takes the reverse of the expression.
	////////////////////////////////////////////
	//--> Opening HSE <--//
	/* Reset CFGR register */
	RCC->CR &= ~(1 << 0); 				//-> HSION became 0. HSI=OFF
	RCC->CR |= 1 << 16; 				//-> HSEON became 1. HSE=ON
	while(!(RCC->CR & (1 << 17))); 		//-> Wait HSE active
	////////////////////////////////////////////
	//--> PLL CONFIG <--//
	RCC->CR |= 1<<19; 					//-> CSSON became 1.
	RCC->PLLCFGR = 0x00000000; 			//-> PLLCFGR = 0
	RCC->PLLCFGR |= (1 << 22); 			//-> PLLSRC = 1, PLL Source = HSE

	//PLL_M = 4 (000100)
	RCC->PLLCFGR &= ~(1 << 0); 			//-> PLLM0 = 0
	RCC->PLLCFGR &= ~(1 << 1); 			//-> PLLM1 = 0
	RCC->PLLCFGR |= (1 << 2);  			//-> PLLM2 = 1
	RCC->PLLCFGR &= ~(1 << 3); 			//-> PLLM3 = 0
	RCC->PLLCFGR &= ~(1 << 4); 			//-> PLLM4 = 0
	RCC->PLLCFGR &= ~(1 << 5); 			//-> PLLM5 = 0
	//RCC->PLLCFGR |= (4<<0); 			//-> PLL_M = 4 (We processed the value)

	//PLL_N = 168
	RCC->PLLCFGR |= (168<<6); 			//-> PLL_N = 168 (We processed the value)

	//PLL_P = 2 (00)
	RCC->PLLCFGR &= ~(1 << 16); 		//-> PLLP0 = 0
	RCC->PLLCFGR &= ~(1 << 17); 		//-> PLLP1 = 0

	//////-->> SYSCLK = [(8Mhz/4)*168/4] = 84Mhz

	RCC->CR |= (1 << 24); 				//-> PLLON = 1, PLL opens
	while(!(RCC->CR & (1 << 25))); 		//-> Wait PLL active

	RCC->CFGR &= ~(1 << 0); 			//->SW0 = 0
	RCC->CFGR |= (1 << 1);  			//->SW1 = 1
	//-> System clock is PLL
	while(!(RCC->CFGR & (1 << 1))); 	//-> Select system clock is pll clock


	// 8Mhz -> 168Mhz
	////////////////////////////////////////////
}
int main(void)
{
	system_clock = SystemCoreClock;
	//--> Using HSI <--//
	//RCC_DeInit(); //-> HSI->ON, PLL->OFF (This bit cannot be cleared if the HSI is used directly or indirectly as the system clock.)
	SystemCoreClockUpdate(); //-> Updates the system clock
	system_clock = SystemCoreClock;
	////////////////////
	//--> Using PLL <--//
	RCC_Config();
	SystemCoreClockUpdate();
	system_clock = SystemCoreClock;
	////////////////////
	while (1)
	{

	}
}





void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
