/*
 * light_functions.h
 *
 *  Created on: 12 gru 2022
 *      Author: Jakub Górnisiewicz
 */

#ifndef INC_LIGHT_FUNCTIONS_H_
#define INC_LIGHT_FUNCTIONS_H_



/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 DEFINE
*//////////////////////////////////////////////////////////////////////////////


#define DEBUG_PRINTF
//define for debouncing
#define BUTTON_DEBOUNCE_TIME 250
#define STOP_DEBOUNCE_TIME 100


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 INCLUDES
*//////////////////////////////////////////////////////////////////////////////


#include "main.h"
#include "usart.h"


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 TYPEDEF
*//////////////////////////////////////////////////////////////////////////////


//enum for while logic to choose a light
typedef enum {
	LIGHT_INIT = 0,				//default value
	LIGHT_BATTERY = 1,
	LIGHT_STOP = 2,
	LIGHT_EMERGENCY = 4,
	LIGHT_LEFT = 6,
	LIGHT_RIGHT = 8
} light_values_t;

//enum for value of button
typedef enum {
	false,
	true
} bool_t;


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 VARIABLES
*//////////////////////////////////////////////////////////////////////////////


//variable for nRF send data
extern uint8_t message[32];

//variable for double click button
extern volatile bool_t emergency_button_value;
extern volatile bool_t left_button_value;
extern volatile bool_t right_button_value;

//variable for choose a type of light
extern volatile light_values_t light;

//variable for software denouncing GPIO interrupt
extern uint32_t previous_time;
extern uint32_t current_time;


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 FUNCTIONS OTHER
*//////////////////////////////////////////////////////////////////////////////


/**
 * @brief - a function that sends data using nRF
 * @param - light number save in data uint8_t
 * @return - none
 */
void send_light(uint8_t data);


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 FUNCTIONS STOP
*//////////////////////////////////////////////////////////////////////////////


/**
 * @brief - logic select function for "stop" light
 * @param - none
 * @return - none
 */
void stop_light_logic(void);

/**
 * @brief - function to turn ON the "stop" light at the board RX
 * @param - none
 * @return - none
 */
void stop_light_start_send(void);

/**
 * @brief - function to turn OFF the "stop" light at the board RX
 * @param - none
 * @return - none
 */
void stop_light_end_send(void);


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 FUNCTIONS EMERGENCY
*//////////////////////////////////////////////////////////////////////////////


/**
 * @brief - logic select function for "emergency" light
 * @param - none
 * @return - none
 */
void emergency_light_logic(void);

/**
 * @brief - function to turn ON the "emergency" light at the board RX and turn ON
 * middle diode at TX board
 * @param - none
 * @return - none
 */
void emergency_light_start_send(void);

/**
 * @brief - function to turn OFF the "emergency" light at the board RX and turn OFF
 * middle diode at TX board
 * @param - none
 * @return - none
 */
void emergency_light_end_send(void);


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 FUNCTIONS LEFT TURNING
*//////////////////////////////////////////////////////////////////////////////

/**
 * @brief - logic select function for "left turn" light
 * @param - none
 * @return - none
 */
void left_light_logic(void);

/**
 * @brief - function to turn ON the "left turn" light at the board RX and turn ON
 * left diode at TX board
 * @param - none
 * @return - none
 */
void left_light_start_send(void);

/**
 * @brief - function to turn OFF the "left turn" light at the board RX and turn OFF
 * left diode at TX board
 * @param - none
 * @return - none
 */
void left_light_end_send(void);


/*/////////////////////////////////////////////////////////////////////////////
 	 	 	 	 	 	 	 	 FUNCTIONS RIGHT TURNING
*//////////////////////////////////////////////////////////////////////////////


/**
 * @brief - logic select function for "right turn" light
 * @param - none
 * @return - none
 */
void right_light_logic(void);

/**
 * @brief - function to turn ON the "right turn" light at the board RX and turn ON
 * right diode at TX board
 * @param - none
 * @return - none
 */
void right_light_start_send(void);

/**
 * @brief - function to turn OFF the "right turn" light at the board RX and turn OFF
 * right diode at TX board
 * @param - none
 * @return - none
 */
void right_light_end_send(void);



#endif /* INC_LIGHT_FUNCTIONS_H_ */
