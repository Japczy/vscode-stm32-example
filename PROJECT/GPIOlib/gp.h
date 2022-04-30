/* gp.h
   lcd_inprogress_1
   TODO

    Created on: 18.12.2020
        Author: Szymonp
 */

#ifndef GPIOlib_GP_H_
#define GPIOlib_GP_H_

extern int test;


#include "stm32f1xx.h"

typedef enum {// CNF[1:0]
    GP_Mode_out_PP_up10MHz         = 0x01,
    GP_Mode_out_PP_up2MHz          = 0x02,
    GP_Mode_out_PP_up50MHz         = 0x03,
    GP_Mode_out_OD_up10MHz         = 0x05,
    GP_Mode_out_OD_up2MHz          = 0x06,
    GP_Mode_out_OD_up50MHz         = 0x07,
    GP_Mode_alternative_PP_up10MHz = 0x09,
    GP_Mode_alternative_PP_up2MHz  = 0x0A,
    GP_Mode_alternative_PP_up50MHz = 0x0B,
    GP_Mode_alternative_OD_up10MHz = 0x0D,
    GP_Mode_alternative_OD_up2MHz  = 0x0E,
    GP_Mode_alternative_OD_up50MHz = 0x0F,
    GP_Mode_inFloating             = 0x04,
    GP_Mode_inPull_X               = 0x08,
    GP_Mode_inAnalog               = 0x00,
} MODE_Typedef;

void GPIOcfg(GPIO_TypeDef * GPIOx, uint8_t PIN, MODE_Typedef MODE);
// void GPIOset(GPIO_TypeDef *GPIOx , uint8_t PIN);


#endif /* GPIOlib_GP_H_ */
