/*
 * light_functions_RX.h
 *
 *  Created on: 12 gru 2022
 *      Author: Jakub Górnisiewicz
 */

#ifndef INC_LIGHT_FUNCTIONS_RX_H_
#define INC_LIGHT_FUNCTIONS_RX_H_


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 DEFINE
*//////////////////////////////////////////////////////////////////////////////


#define BUZZING_TIME 50
#define TURNING_DIODE_REFRESH_TIME 130


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 INCLUDES
*//////////////////////////////////////////////////////////////////////////////


#include "main.h"
#include "spi.h"
#include "nRF24.h"
#include "nRF24_Defs.h"



/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 VARIABLES
*//////////////////////////////////////////////////////////////////////////////

//uint8_t Nrf24_Message[NRF24_PAYLOAD_SIZE];
//volatile uint8_t nrf24_rx_flag, nrf24_tx_flag, nrf24_mr_flag;
extern const uint8_t left_light_values[];
extern const uint8_t right_light_values[];


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	OTHER FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////

/**
 * @brief - function to send data to 74HC595 by SPI
 * @param - data, size of data
 * @return - none
 */
void shiftOut(uint8_t* data, uint8_t size);

/**
 * @brief - function to get voice (buzzing) on board RX
 * @param - none
 * @return - none
 */
void buzzing(void);

/**
 * @brief - function to get voice after init
 * @param - none
 * @return - none
 */
void board_ready_to_recive_voice(void);


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 LIGHT FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////


/**
 * @brief - function to turn OFF all "turning diodes"
 * @param - none
 * @return - none
 */
void turning_diode_reset(void);

/**
 * @brief - function to turn ON of the "position light" at board RX
 * @param - none
 * @return - none
 */
void position_lights_set(void);


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	STOP LIGHT FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////


/**
 * @brief - function to check what should happen with the "stop light" WHEN
 * TURNING DIODES ARE ON
 * @param - none
 * @return - none
 */
void check_stop_light_logic(void);

/**
 * @brief - function to turn ON the "stop light" at board RX
 * @param - none
 * @return - none
 */
void stop_light_set(void);

/**
 * @brief - function to turn OFF the "stop light" at board RX
 * @param - none
 * @return - none
 */
void stop_light_reset(void);


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	EMERGENCY LIGHT FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////


/**
 * @brief - function to check what should happen with the "emergency light" at board RX
 * @param - none
 * @return - none
 */
void emergency_lights_logic(void);

/**
 * @brief - function to turn ON the "emergency light"
 * @param - none
 * @return - none
 */
void emergency_lights_set(void);


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	TURNING LIGHT FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////


/**
 * @brief - function to check what should happen with the "left turning diodes" at board RX
 * @param - none
 * @return - none
 */
void turn_left_lights_logic(void);

/**
 * @brief - function to turn ON the "left turning" diodes
 * @param - none
 * @return - none
 */
void turn_left_lights_set(void);

/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	TURNING RIGHT FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////


/**
 * @brief - function to check what should happen with the "right turning diodes" at board RX
 * @param - none
 * @return - none
 */
void turn_right_lights_logic(void);

/**
 * @brief - function to turn ON the "right turning" diodes
 * @param - none
 * @return - none
 */
void turn_right_lights_set(void);





#endif /* INC_LIGHT_FUNCTIONS_RX_H_ */
