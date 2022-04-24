#ifndef GPIOLIB_GP_DEF_H_
#define GPIOLIB_GP_DEF_H_


#define _BV(x) (1<<(x))

//_lcd_
#define GPIO_BLK GPIOA
#define GPIO_CS GPIOA
#define GPIO_DC GPIOB
#define GPIO_RES GPIOB
#define P_BLK	6	//A
#define P_CS	7	//A
#define P_DC	0	//B
#define P_RES	1	//B
#define P_SDA	5	//B
#define P_SCL	3	//B

//_ENCODER_
#define GPIO_ENC_SW GPIOC
#define GPIO_ENC_A GPIOA
#define GPIO_ENC_B GPIOA
#define P_ENC_SW	15	//B
#define P_ENC_A		0	//A
#define P_ENC_B		1	//A

//EEPROM
#define GPIO_EEPROM GPIOB
#define P_I2C_SCK 8	//PB8
#define P_I2C_SDA 9	//PB9
#define P_I2C_RW 7 	//PB9


#endif /* GPIOLIB_GP_DEF_H_ */
