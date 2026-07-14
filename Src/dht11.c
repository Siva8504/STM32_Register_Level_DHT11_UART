#include <stdint.h>
#include "dht11.h"

volatile uint32_t *pAHB1ENR   = (uint32_t*)0x40023830;

volatile uint32_t *pGPIOAMODER = (uint32_t*)0x40020000;
volatile uint32_t *pGPIOAIDR   = (uint32_t*)0x40020010;
volatile uint32_t *pGPIOAODR   = (uint32_t*)0x40020014;

volatile uint32_t *pAPB1ENR = (uint32_t*)0x40023840;

volatile uint32_t *pTIM2CR1 = (uint32_t*)0x40000000;
volatile uint32_t *pTIM2CNT = (uint32_t*)0x40000024;
volatile uint32_t *pTIM2PSC = (uint32_t*)0x40000028;
volatile uint32_t *pTIM2ARR = (uint32_t*)0x4000002C;

#define DHT_THRESHOLD 682


void TIM2_Init(void)
{
    *pAPB1ENR |= (1<<0);

    *pTIM2PSC = 15;

    *pTIM2ARR = 0xFFFFFFFF;

    *pTIM2CR1 |= (1<<0);
}



void delay_us(uint32_t us)
{
    *pTIM2CNT = 0;

    while(*pTIM2CNT < us);

}

void delay_ms(uint32_t ms)
{
    *pTIM2CNT = 0;

    while(*pTIM2CNT < (ms * 1000));

}



void DHT11_Start(void)
{
    *pGPIOAMODER &= ~(3<<12);
    *pGPIOAMODER |=  (1<<12);

    *pGPIOAODR &= ~(1<<6);

    delay_ms(18);

    *pGPIOAODR |= (1<<6);



    delay_us(40);

    *pGPIOAMODER &= ~(3<<12);


}



uint8_t DHT11_Response(void)
{
    while((*pGPIOAIDR & (1<<6)));

    *pTIM2CNT = 0;

    while(((*pGPIOAIDR & (1<<6)) == 0));


    *pTIM2CNT = 0;

    while((*pGPIOAIDR & (1<<6)));


    return 1;
}



uint8_t DHT11_ReadBit(void)
{
	uint32_t pulse_width;
    while((*pGPIOAIDR & (1<<6))){

    }
	    while(((*pGPIOAIDR & (1<<6)) == 0)){

	    }

	    *pTIM2CNT = 0;

	    while((*pGPIOAIDR & (1<<6)));

	    pulse_width = *pTIM2CNT;

	    if(pulse_width > DHT_THRESHOLD ){
	        return 1;
	    }else{

	    return 0;
	    }
}



uint8_t DHT11_ReadByte(void)
{
    uint8_t data = 0;
    uint8_t i;

    for(i=0;i<8;i++)
    {
         data <<= 1;

         data |= DHT11_ReadBit();
    }

    return data;
}

DHT11_Status DHT11_ReadData(DHT11_Data *sensor)
{
	uint8_t status;
	uint8_t Rh_byte1;
	uint8_t Rh_byte2;
	uint8_t Temp_byte1;
	uint8_t Temp_byte2;
	uint8_t Checksum;
	uint8_t calculated_checksum;

	DHT11_Start();
    status = DHT11_Response();

    if(status)
    {
        Rh_byte1 = DHT11_ReadByte();
        Rh_byte2 = DHT11_ReadByte();
        Temp_byte1 = DHT11_ReadByte();
        Temp_byte2 = DHT11_ReadByte();
        Checksum = DHT11_ReadByte();

        calculated_checksum =
            Rh_byte1 + Rh_byte2 + Temp_byte1 + Temp_byte2;

        if(calculated_checksum == Checksum)
        {
            sensor->temperature = Temp_byte1;
            sensor->humidity = Rh_byte1;

            return DHT11_OK;
        }

        return DHT11_ERROR_CHECKSUM;
    }

    return DHT11_ERROR_NO_RESPONSE;
}
