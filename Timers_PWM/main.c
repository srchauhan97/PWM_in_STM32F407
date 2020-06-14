#include "stm32f4xx.h"

int main()
{
	//enabling clocks for GPIOB pin and TIM4
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	RCC->AHB1ENR |= (1 << 1); //enabling clock for GPIOB
	
	//Setting as alternate function for pin PB9
	GPIOB->MODER |= (2 << 18);
	//Setting output type of the pin PB9
	GPIOB->OTYPER &=~ (1 << 9);
	//setting up output speed of the PB9
	GPIOB->OSPEEDR |= (2 << 18);
	//Alternate function type(AF2) setting
	GPIOB->AFR[1] |= (2 << 4);
	
	
	//1. we need to enable the output chennal by configuring OCxE bit in CCER register
	TIM4->CCER |= ( 1 << 12); // 12 is bit position of OC4 
	//2. Auto-reload preload register enable in CR1.
	TIM4->CR1 |= (1 << 7); //To enable auto reload preload enable so that TIMx_ARR register is buffered
	//3. Output compare preload enable
	TIM4->CCMR2 |= (1 << 11); //Preload register on TIMx_CCR1 enabled.
	TIM4->CCMR2 |= (1 << 14) | (1 << 13) | (0 << 12);
	//now setting the polarity of PWM output
	TIM4->CCER &=~ (1 << 13);  //setting as active high 
	
	
	//now, we know that PWM freq = Fclk / PSC/ARR
	/*or, fclk/desired freq = PSC*ARR
	we want 1000khz desired PWM freq. so 16000000/1000 = 16000
	so we can take 16 as PSC and 1000 as arr*/
	//PWM Duty = CCR4 / ARR
	TIM4->PSC = 16;
	TIM4->ARR = 1000;
	TIM4->CCR4 = 250; //25%duty cycle   1000* 25% = 250

}
