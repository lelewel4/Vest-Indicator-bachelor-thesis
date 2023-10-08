/*
 * light_functions_RX.c
 *
 *  Created on: 12 gru 2022
 *      Author: Jakub Górnisiewicz
 */

/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 INCLUDES
*//////////////////////////////////////////////////////////////////////////////


#include "main.h"
#include "light_functions_RX.h"
#include "nRF24.h"
#include "nRF24_Defs.h"


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 VARIABLES
*//////////////////////////////////////////////////////////////////////////////

uint8_t Nrf24_Message[NRF24_PAYLOAD_SIZE];
volatile uint8_t nrf24_rx_flag, nrf24_tx_flag, nrf24_mr_flag;
const uint8_t left_light_values[] = {0, 1, 3, 7, 15, 31};
const uint8_t right_light_values[] = {0, 16, 24, 28, 30, 31};


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	OTHER FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////


void shiftOut(uint8_t* data, uint8_t size)
{
	//latch pin low
	HAL_GPIO_WritePin(SPI2_LATCH_GPIO_Port, SPI2_LATCH_Pin, GPIO_PIN_RESET);
	//write data
	HAL_SPI_Transmit(&hspi2, data, size, 100);
	//once data is ready, latch pin high
	HAL_GPIO_WritePin(SPI2_LATCH_GPIO_Port, SPI2_LATCH_Pin, GPIO_PIN_SET);
}


void buzzing(void)
{
	HAL_GPIO_WritePin(BZ_GPIO_Port, BZ_Pin, GPIO_PIN_SET);
	HAL_Delay(BUZZING_TIME);
	HAL_GPIO_WritePin(BZ_GPIO_Port, BZ_Pin, GPIO_PIN_RESET);
}


void board_ready_to_recive_voice(void)
{
	for(int i=0; i<5; i++)
	{
		//buzzing for 5*50ms=200ms
		buzzing();
	}
}

/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 LIGHT FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////


void turning_diode_reset(void)
{
	uint8_t size= 2;
	uint8_t data[2] = {0x00, 0x00};
	shiftOut(data, size);
}

void position_lights_set(void)
{
	HAL_GPIO_WritePin(DP_GPIO_Port, DP_Pin, GPIO_PIN_SET);
}


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	STOP LIGHT FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////


void check_stop_light_logic(void)
{
	if(nRF24_RXAvailible())
	{
	nRF24_ReadRXPaylaod(Nrf24_Message);
	//MessageLength = sprintf(Message, "%c\n\r", Nrf24_Message[0]);
	//HAL_UART_Transmit(&huart2, Message, MessageLength, 1000);
		if(Nrf24_Message[0] == 0x32)
		{
			stop_light_set();
		}
		else
		{
			stop_light_reset();
		}
	}
}


void stop_light_set(void)
{
	buzzing();
	HAL_GPIO_WritePin(DS_GPIO_Port, DS_Pin, GPIO_PIN_SET);
}


void stop_light_reset(void)
{
	HAL_GPIO_WritePin(DS_GPIO_Port, DS_Pin, GPIO_PIN_RESET);
	buzzing();
}


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	EMERGENCY LIGHT FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////


void emergency_lights_logic(void)
{
	buzzing();
 	while (Nrf24_Message[0] != 0x35)
 	{
 		emergency_lights_set();
 	}
 	check_stop_light_logic();
 	turning_diode_reset();
}


void emergency_lights_set(void)
{
	uint8_t size= 2;
 	uint8_t data[2];
	for(int i=0; i<6; i++)
	{
		check_stop_light_logic();
		data[0] = left_light_values[i];
		data[1] = right_light_values[i];
		shiftOut(data, size);
		HAL_Delay(TURNING_DIODE_REFRESH_TIME);
	}
}


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	TURNING LIGHT FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////


void turn_left_lights_logic(void)
{
	buzzing();
 	while (Nrf24_Message[0] != 0x37)
 	{
 		turn_left_lights_set();
 	}
 	check_stop_light_logic();
 	turning_diode_reset();
}


void turn_left_lights_set(void)
{
	uint8_t size= 2;
 	uint8_t data[2];
	data[1] = 0;
	for(int i=0; i<6; i++)
	{
		check_stop_light_logic();
		data[0] = left_light_values[i];
		data[1] = 0;
		shiftOut(data, size);
		HAL_Delay(TURNING_DIODE_REFRESH_TIME);
	}
}


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	TURNING RIGHT FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////


void turn_right_lights_logic(void)
{
	buzzing();
 	while (Nrf24_Message[0] != 0x39)
 	{
 		turn_right_lights_set();
 	}
 	check_stop_light_logic();
 	turning_diode_reset();
}


void turn_right_lights_set(void)
{
	uint8_t size= 2;
	uint8_t data[2];
	data[0] = 0;
	for(int i=0; i<6; i++)
	{
		check_stop_light_logic();
		data[1] = right_light_values[i];
		shiftOut(data, size);
		HAL_Delay(TURNING_DIODE_REFRESH_TIME);
	}
}


