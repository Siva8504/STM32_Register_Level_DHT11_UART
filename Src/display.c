#include "display.h"
#include "uart.h"

void DisplaySensorData(const DHT11_Data *sensor)
{
    UART2_SendString("Temperature : ");
    UART2_SendNumber(sensor->temperature);
    UART2_SendString(" C\r\n");

    UART2_SendString("Humidity    : ");
    UART2_SendNumber(sensor->humidity);
    UART2_SendString(" %\r\n\r\n");
}

