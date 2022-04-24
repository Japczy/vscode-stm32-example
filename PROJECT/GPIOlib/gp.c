
#include "gp.h"

void GPIOcfg(GPIO_TypeDef *GPIOx , uint8_t PIN , MODE_Typedef MODE)
{//remember add befor this func! RCC->APB2ENR |= RCC_APB2ENR_IOPxEN;
	uint32_t reg;
	PIN *= 4;
	if(PIN<32){
		reg = GPIOx->CRL;
		reg &= ~(0b1111 << PIN);
		GPIOx->CRL = reg | (MODE << PIN );
	}else{
		PIN -= 32;
		reg = GPIOx->CRH;
		reg &= ~(0b1111 << PIN);
		GPIOx->CRH = reg | (MODE << PIN);
	}
}
