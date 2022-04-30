/* Led toggle in frequency
   Fcpu / 10M
   2022.04
   tools: [VSCODE, cortex-debug, stm32 toolchain, cmake, make, uncrustify (formatter), make]
 */


#include <stdio.h>

#include "GPIOlib/gp.h"
#include "stm32f1xx.h"


// #define LED_PIN      5
// #define LED_PORT     PORTB
// #define LED_RCC_PORT RCC_APB2ENR_IOPBEN


#define LED_PIN      13
#define LED_PORT     GPIOC
#define LED_RCC_PORT RCC_APB2ENR_IOPCEN


// FIXME: timer na poczatku wyzwala przerwanie, trza dać ifa

int main(void)
{
    // asm ("nop"); // test start

    RCC->APB2ENR |= LED_RCC_PORT;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    GPIOcfg(LED_PORT, LED_PIN, GP_Mode_out_PP_up2MHz); // out al

    // TIM3 - interrupt trigger once per (10M / Fcpu)
    TIM3->CNT = 1;
    TIM3->ARR = 1000;      // Przepelnienie licznika
    TIM3->CCR1 = 1000 - 1; // wartoc porównawcza
    TIM3->PSC = 10000;

    TIM3->DIER = TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM3_IRQn);

    for (uint8_t i = 2; i > 0; i--) {
        for (int ii = 0; ii < (8000000UL / 6); ++ii);  // Delay 1s
        LED_PORT->ODR ^= (1 << LED_PIN);
    }

    for (uint8_t i = 8; i > 0; i--) {
        for (int ii = 0; ii < ((8000000UL / 6) / 10); ++ii);  // Delay 0,1s
        LED_PORT->ODR ^= (1 << LED_PIN);
    }

    TIM3->CR1 = TIM_CR1_CEN;
    while (1);
} /* main */

__attribute__((interrupt)) void TIM3_IRQHandler(void)
{
    LED_PORT->ODR ^= (1 << LED_PIN);
    TIM3->SR = 0;
}
