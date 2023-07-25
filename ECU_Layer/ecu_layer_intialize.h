/* 
 * File:   ecu_layer_intialize.h
 * Author: Ehab
 *
 * Created on 24 ?????, 2023, 07:05 ?
 */

#ifndef ECU_LAYER_INTIALIZE_H
#define	ECU_LAYER_INTIALIZE_H

/* Includes */
#include "LED/ecu_led.h"
#include "Keypad/ecu_keypad.h"
#include "LCD/ecu_lcd.h"
#include "DC_Motor/ecu_dc_motor.h"

/* Data Types Declarations */
extern led_t led_locked;
extern led_t led_opened;
extern motor_t motor;
extern keypad_t keypad;
extern lcd_4bit_t lcd;

/* Function Declarations */
Std_ReturnType ecu_layer_intialize();

#endif	/* ECU_LAYER_INTIALIZE_H */

