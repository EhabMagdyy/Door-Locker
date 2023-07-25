/* 
 * File:   ecu_layer_intialize.c
 * Author: Ehab
 *
 * Created on 24 ?????, 2023, 07:05 ?
 */

#include "ecu_layer_intialize.h"
#include "LED/ecu_led.h"

led_t led_locked = {.port = PORTA_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
led_t led_opened = {.port = PORTA_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};

motor_t motor = {
    .motor_pin[0].port = PORTA_INDEX,
    .motor_pin[0].pin = GPIO_PIN3,
    .motor_pin[0].direction = GPIO_direction_output,
    .motor_pin[0].logic = GPIO_LOW,
    .motor_pin[1].port = PORTA_INDEX,
    .motor_pin[1].pin = GPIO_PIN4,
    .motor_pin[1].direction = GPIO_direction_output,
    .motor_pin[1].logic = GPIO_LOW,
};

keypad_t keypad = {
    .keypad_rows_pins[0].port = PORTD_INDEX,
    .keypad_rows_pins[0].pin = GPIO_PIN0,
    .keypad_rows_pins[0].direction = GPIO_direction_output,
    .keypad_rows_pins[0].logic = GPIO_LOW,
    .keypad_rows_pins[1].port = PORTD_INDEX,
    .keypad_rows_pins[1].pin = GPIO_PIN1,
    .keypad_rows_pins[1].direction = GPIO_direction_output,
    .keypad_rows_pins[1].logic = GPIO_LOW,
    .keypad_rows_pins[2].port = PORTD_INDEX,
    .keypad_rows_pins[2].pin = GPIO_PIN2,
    .keypad_rows_pins[2].direction = GPIO_direction_output,
    .keypad_rows_pins[2].logic = GPIO_LOW,
    .keypad_rows_pins[3].port = PORTD_INDEX,
    .keypad_rows_pins[3].pin = GPIO_PIN3,
    .keypad_rows_pins[3].direction = GPIO_direction_output,
    .keypad_rows_pins[3].logic = GPIO_LOW,
    
    .keypad_coloumns_pins[0].port = PORTD_INDEX,
    .keypad_coloumns_pins[0].pin = GPIO_PIN4,
    .keypad_coloumns_pins[0].direction = GPIO_direction_input,
    .keypad_coloumns_pins[0].logic = GPIO_LOW,
    .keypad_coloumns_pins[1].port = PORTD_INDEX,
    .keypad_coloumns_pins[1].pin = GPIO_PIN5,
    .keypad_coloumns_pins[1].direction = GPIO_direction_input,
    .keypad_coloumns_pins[1].logic = GPIO_LOW,
    .keypad_coloumns_pins[2].port = PORTD_INDEX,
    .keypad_coloumns_pins[2].pin = GPIO_PIN6,
    .keypad_coloumns_pins[2].direction = GPIO_direction_input,
    .keypad_coloumns_pins[2].logic = GPIO_LOW,
};

lcd_4bit_t lcd = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_direction_output,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_enable.port = PORTC_INDEX,
    .lcd_enable.pin = GPIO_PIN1,
    .lcd_enable.direction = GPIO_direction_output,
    .lcd_enable.logic = GPIO_LOW,
    
    .data_lines[0].port = PORTC_INDEX,
    .data_lines[0].pin = GPIO_PIN2,
    .data_lines[0].direction = GPIO_direction_output,
    .data_lines[0].logic = GPIO_LOW,
    .data_lines[1].port = PORTC_INDEX,
    .data_lines[1].pin = GPIO_PIN3,
    .data_lines[1].direction = GPIO_direction_output,
    .data_lines[1].logic = GPIO_LOW,
    .data_lines[2].port = PORTC_INDEX,
    .data_lines[2].pin = GPIO_PIN4,
    .data_lines[2].direction = GPIO_direction_output,
    .data_lines[2].logic = GPIO_LOW,
    .data_lines[3].port = PORTC_INDEX,
    .data_lines[3].pin = GPIO_PIN5,
    .data_lines[3].direction = GPIO_direction_output,
    .data_lines[3].logic = GPIO_LOW
};

Std_ReturnType ecu_layer_intialize()
{
    Std_ReturnType ret = E_NOT_OK;
    
    ret = led_intialiaze(&led_locked);
    ret = led_intialiaze(&led_opened);
    
    ret = motor_intialize(&motor);
    
    ret = keypad_intialize(&keypad);
    
    ret = lcd_4bit_intialize(&lcd);
    
    return ret;
}
