/* Led toggle in frequency
   Fcpu / 10M
   2022.04
   tools: [VSCODE, cortex-debug, stm32 toolchain, cmake, make, uncrustify (formatter), make]
 */


#include <stdio.h>

#include "GPIOlib/gp.h"
#include "stm32f1xx.h"


#define PIN_PORTB 5


// FIXME: timer na poczatku wyzwala przerwanie, trza dać ifa

int main(void)
{
    // asm ("nop"); // test start

    RCC->APB2ENR |= (RCC_APB2ENR_IOPBEN);
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    GPIOcfg(GPIOB, PIN_PORTB, GP_Mode_out_OD_up2MHz); // out al

    // TIM3 - interrupt trigger once per (10M / Fcpu)
    TIM3->CNT = 1;
    TIM3->ARR = 1000;      // Przepelnienie licznika
    TIM3->CCR1 = 1000 - 1; // wartoc porównawcza
    TIM3->PSC = 10000;

    TIM3->DIER = TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM3_IRQn);

    for (uint8_t i = 2; i > 0; i--) {
        for (int ii = 0; ii < (8000000UL / 6); ++ii);  // Delay 1s
        GPIOB->ODR ^= (1 << 5);
    }

    for (uint8_t i = 8; i > 0; i--) {
        for (int ii = 0; ii < ((8000000UL / 6) / 10); ++ii);  // Delay 0,1s
        GPIOB->ODR ^= (1 << 5);
    }

    TIM3->CR1 = TIM_CR1_CEN;
    while (1);
} /* main */

__attribute__((interrupt)) void TIM3_IRQHandler(void)
{
    GPIOB->ODR ^= (1 << 5);
    TIM3->SR = 0;
}
