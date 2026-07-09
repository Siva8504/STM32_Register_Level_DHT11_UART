#ifndef DHT11_H_
#define DHT11_H_

#include <stdint.h>

typedef struct
{
    uint8_t temperature;
    uint8_t humidity;
} DHT11_Data;

extern volatile uint32_t *pAHB1ENR ;


//#define DHT_THRESHOLD 682

void TIM2_Init(void);

void delay_us(uint32_t us);

void delay_ms(uint32_t ms);

void DHT11_Start(void);

uint8_t DHT11_Response(void);

uint8_t DHT11_ReadBit(void);

uint8_t DHT11_ReadByte(void);

uint8_t DHT11_ReadData(DHT11_Data *sensor);


#endif
