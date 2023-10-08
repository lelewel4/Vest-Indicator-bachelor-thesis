/*
 * ADC_functions.c
 *
 *  Created on: 12 gru 2022
 *      Author: Jakub Górnisiewicz
 */


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 INCLUDES
*//////////////////////////////////////////////////////////////////////////////


#include "ADC_functions.h"
#include "main.h"
#include "usart.h"
#include "adc.h"

/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 VARIABLES
*//////////////////////////////////////////////////////////////////////////////


//variable for ADC, measurement of battery voltage
uint32_t adc_value = 0;


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////


//measure battery value (ADC)
uint32_t get_adc_battery_value(void)
{
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    uint32_t value_adc = HAL_ADC_GetValue(&hadc1);
    //values
    float voltage = (3.3f * value_adc / 4096.0f);
    float voltage_real_battery = (3.3f * value_adc / 4096.0f) + 5;
#ifdef DEBUG_PRINTF
    printf("ADC = %lu (%.3f V), Real Battery = %.3f V\n", value_adc,
    													  voltage,
														  voltage_real_battery);
#endif
    return value_adc;
}


//diodes turn ON for battery measurement
void battery_level_show(uint32_t value)
{
    if(value <= 1365)
    {
        HAL_GPIO_WritePin(DR_GPIO_Port, DR_Pin, GPIO_PIN_SET);
        HAL_Delay(DIODES_ADC_TIME);
        HAL_GPIO_WritePin(DR_GPIO_Port, DR_Pin, GPIO_PIN_RESET);
    }
    else if((value > 1365) && (value <= 2730))
    {
        HAL_GPIO_WritePin(DR_GPIO_Port, DR_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(DY_GPIO_Port, DY_Pin, GPIO_PIN_SET);
        HAL_Delay(DIODES_ADC_TIME);
        HAL_GPIO_WritePin(DR_GPIO_Port, DR_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(DY_GPIO_Port, DY_Pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(DR_GPIO_Port, DR_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(DY_GPIO_Port, DY_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(DG_GPIO_Port, DG_Pin, GPIO_PIN_SET);
        HAL_Delay(DIODES_ADC_TIME);
        HAL_GPIO_WritePin(DR_GPIO_Port, DR_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(DY_GPIO_Port, DY_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(DG_GPIO_Port, DG_Pin, GPIO_PIN_RESET);
    }
}
