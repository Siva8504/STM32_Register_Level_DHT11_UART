#ifndef DHT11_H_
#define DHT11_H_

#include <stdint.h>

extern volatile uint8_t humidity;
extern volatile uint8_t temperature;

extern volatile uint32_t *pAHB1ENR ;


extern volatile uint8_t status ;
extern volatile uint8_t Rh_byte1 ;
extern volatile uint8_t Rh_byte2 ;

extern volatile uint8_t Temp_byte1 ;
extern volatile uint8_t Temp_byte2 ;

extern volatile uint8_t Checksum ;
extern volatile uint8_t calculated_checksum ;



#define DHT_THRESHOLD 682

void TIM2_Init(void);

void delay_us(uint32_t us);

void delay_ms(uint32_t ms);

void DHT11_Start(void);

uint8_t DHT11_Response(void);

uint8_t DHT11_ReadBit(void);

uint8_t DHT11_ReadByte(void);

#endif
