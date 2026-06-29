#include <stdint.h>


volatile uint32_t *pAHB1ENR   = (uint32_t*)0x40023830;

volatile uint32_t *pGPIOAMODER = (uint32_t*)0x40020000;
volatile uint32_t *pGPIOAIDR   = (uint32_t*)0x40020010;
volatile uint32_t *pGPIOAODR   = (uint32_t*)0x40020014;

volatile uint32_t *pAPB1ENR = (uint32_t*)0x40023840;

volatile uint32_t *pTIM2CR1 = (uint32_t*)0x40000000;
volatile uint32_t *pTIM2CNT = (uint32_t*)0x40000024;
volatile uint32_t *pTIM2PSC = (uint32_t*)0x40000028;
volatile uint32_t *pTIM2ARR = (uint32_t*)0x4000002C;

volatile uint32_t timer_value = 0;

volatile uint8_t status = 0;
volatile uint8_t Rh_byte1 = 0;
volatile uint8_t Rh_byte2 = 0;

volatile uint8_t Temp_byte1 = 0;
volatile uint8_t Temp_byte2 = 0;

volatile uint8_t Checksum = 0;

volatile uint32_t test_cnt = 0;

volatile uint32_t pulse_width = 0;
volatile uint8_t byte_value = 0;


volatile uint8_t calculated_checksum = 0;

volatile uint8_t humidity = 0;
volatile uint8_t temperature = 0;

volatile uint32_t loop_count = 0;

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
