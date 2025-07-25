#include <project.h>
#include <stdio.h>

#define ADC_WET_THRESHOLD    1500  
#define ADC_MOIST_THRESHOLD  3000   

int main(void)
{
    uint16 adcResult = 0;  
    float voltage = 0.0;    
    char lcdStr[16];        
    char moistureState[16]; 
    char uartBuffer[64];    

    /* Start components */
    ADC_Start();    
    LCD_Start();
    UART_Start(0, UART_5V_OPERATION);  // Use USBUART instead of UART

    LCD_Position(0, 0);
    LCD_PrintString("Soil Sensor:");
    
    CyGlobalIntEnable; 

    for(;;)
    {
        /* ADC Conversion */
        ADC_StartConvert();
        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
        adcResult = ADC_GetResult16();
        voltage = (adcResult / 4096.0) * 5.0;

        /* Determine moisture state */
        if(adcResult < ADC_WET_THRESHOLD) {
            sprintf(moistureState, "Soil : Wet ");
        }
        else if(adcResult < ADC_MOIST_THRESHOLD) {
            sprintf(moistureState, "Soil : Moist");
        }
        else {
            sprintf(moistureState, "Soil : Dry ");
        }

        /* Update LCD */
        LCD_ClearDisplay();
        LCD_Position(0, 0);
        LCD_PrintString(moistureState);

        /* Show ADC Value & Voltage on LCD */
        sprintf(lcdStr, "ADC:%u V:%.2fV", adcResult, voltage);
        LCD_Position(1, 0);
        LCD_PrintString(lcdStr);
        
        /* Ensure USB UART is ready before sending */
        if (UART_GetConfiguration())  
        {
            UART_CDC_Init();  
            
            /* Format the message */
            sprintf(uartBuffer, "Moisture: %s, ADC: %u, Voltage: %.2fV\r\n", moistureState, adcResult, voltage);
            
            /* Send data using USBUART_PutString */
            while (!UART_CDCIsReady());  
            UART_PutString(uartBuffer);
        }
        
        CyDelay(1000);
    }
}
