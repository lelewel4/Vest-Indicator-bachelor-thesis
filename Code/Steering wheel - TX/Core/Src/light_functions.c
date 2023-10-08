/*
 * light_functions.c
 *
 *  Created on: 12 gru 2022
 *      Author: Jakub Górnisiewicz
 */



/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 INCLUDES
*//////////////////////////////////////////////////////////////////////////////


#include "light_functions.h"
#include "main.h"
#include "nRF24.h"
#include "nRF24_Defs.h"


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 VARIABLES
*//////////////////////////////////////////////////////////////////////////////


uint8_t message[32];

volatile bool_t emergency_button_value = false;
volatile bool_t left_button_value = false;
volatile bool_t right_button_value = false;

volatile light_values_t light = LIGHT_INIT;

uint32_t previous_time = 0;
uint32_t current_time = 0;


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 FUNCTIONS OTHER
*//////////////////////////////////////////////////////////////////////////////


void send_light(uint8_t data)
{
    sprintf(message, "%d", data);
    nRF24_WriteTXPayload(message);
    HAL_Delay(1);
    nRF24_WaitTX();
}


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 FUNCTIONS STOP
*//////////////////////////////////////////////////////////////////////////////


void stop_light_logic(void)
{
    if(HAL_GPIO_ReadPin(BS_GPIO_Port, BS_Pin) == 1)
    {
#ifdef DEBUG_PRINTF
    	//printf("STOP start");
        HAL_UART_Transmit(&huart2, "STOP START ", 11, HAL_MAX_DELAY);
#endif
        stop_light_start_send();
    }
    else
    {
#ifdef DEBUG_PRINTF
    	//printf("STOP stop");
        HAL_UART_Transmit(&huart2, "STOP STOP ", 10, HAL_MAX_DELAY);
#endif
        stop_light_end_send();
    }
}


void stop_light_start_send(void)
{
    uint8_t light_to_send = 2;
    send_light(light_to_send);
}


void stop_light_end_send(void)
{
    uint8_t light_to_send = 3;
    send_light(light_to_send);
}


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 FUNCTIONS EMERGENCY
*//////////////////////////////////////////////////////////////////////////////


void emergency_light_logic(void)
{
    if((left_button_value == false) && (right_button_value == false))
    {
        if(emergency_button_value == true)
        {
        	emergency_light_start_send();
        }
        else
        {
        	emergency_light_end_send();
        }
    }
    else
    {
        emergency_button_value = false;
    }
}


void emergency_light_start_send(void)
{
#ifdef DEBUG_PRINTF
	//printf("EMERGENCY start");
    HAL_UART_Transmit(&huart2, "EMERGENCY START ", 16, HAL_MAX_DELAY);
#endif
    HAL_GPIO_WritePin(DE_GPIO_Port, DE_Pin, GPIO_PIN_SET);		     /*set diode
    														     for emergency*/
    uint8_t light_to_send = 4;
    send_light(light_to_send);
}


void emergency_light_end_send(void)
{
#ifdef DEBUG_PRINTF
	//printf("EMERGENCY stop");
    HAL_UART_Transmit(&huart2, "EMERGENCY STOP ", 15, HAL_MAX_DELAY);
#endif
    uint8_t light_to_send = 5;
    send_light(light_to_send);
    HAL_GPIO_WritePin(DE_GPIO_Port, DE_Pin, GPIO_PIN_RESET);	   /*reset diode
    														  	 for emergency*/
}


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 FUNCTIONS LEFT TURNING
*//////////////////////////////////////////////////////////////////////////////


void left_light_logic(void)
{
    if((right_button_value == false) && (emergency_button_value == false))
    {
        if(left_button_value == true)
        {
            left_light_start_send();
        }
        else if(left_button_value == false)
        {
            left_light_end_send();
        }
    }
    else
    {
        left_button_value = false;
    }
}


void left_light_start_send(void)
{
#ifdef DEBUG_PRINTF
	//printf("LEFT start");
    HAL_UART_Transmit(&huart2, "LEFT START ", 11, HAL_MAX_DELAY);
#endif
    HAL_GPIO_WritePin(TL_GPIO_Port, TL_Pin, GPIO_PIN_SET);		     /*set diode
    														  for turning left*/
    uint8_t light_to_send = 6;
    send_light(light_to_send);
}


void left_light_end_send(void)
{
#ifdef DEBUG_PRINTF
	//printf("LEFT stop");
    HAL_UART_Transmit(&huart2, "LEFT STOP ", 10, HAL_MAX_DELAY);
#endif
    uint8_t light_to_send = 7;
    send_light(light_to_send);
    HAL_GPIO_WritePin(TL_GPIO_Port, TL_Pin, GPIO_PIN_RESET);	   /*reset diode
    														  for turning left*/
}


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 FUNCTIONS RIGHT TURNING
*//////////////////////////////////////////////////////////////////////////////


void right_light_logic(void)
{
    if((left_button_value == false) && (emergency_button_value == false))
    {
        if(right_button_value == true)
        {
            right_light_start_send();
        }
        else if(right_button_value == false)
        {
            right_light_end_send();
        }
    }
    else
    {
        right_button_value = false;
    }
}


void right_light_start_send(void)
{
#ifdef DEBUG_PRINTF
	//printf("RIGHT start");
    HAL_UART_Transmit(&huart2, "RIGHT START ", 12, HAL_MAX_DELAY);
#endif
    HAL_GPIO_WritePin(TR_GPIO_Port, TR_Pin, GPIO_PIN_SET);		     /*set diode
    														 for turning right*/
    uint8_t light_to_send = 8;
    send_light(light_to_send);
}


void right_light_end_send(void)
{
#ifdef DEBUG_PRINTF
	//printf("RIGHT stop");
    HAL_UART_Transmit(&huart2, "RIGHT STOP ", 11, HAL_MAX_DELAY);
#endif
    uint8_t light_to_send = 9;
    send_light(light_to_send);
    HAL_GPIO_WritePin(TR_GPIO_Port, TR_Pin, GPIO_PIN_RESET);	   /*reset diode
    														 for turning right*/
}


