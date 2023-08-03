/* 
 * File:   application.c
 * Author: Ehab
 *
 * Created on 24 ?????, 2023, 06:59 ?
 */

#include "application.h"

#define DEBOUNE_TIME    150

Std_ReturnType ret = E_OK;

uint8 keypad_value;

uint32 password = 123456;
uint32 entered_password = 0;
uint8 number_of_clicks = 0;
uint8 lcd_output_data_col = 14;

uint8 incorrect_pass = 0;

int main()
{
    application_intialize();
    
    ret = lcd_4bit_send_string(&lcd, "Enter Password:");
    
    while(1)
    {
        /* Read Keypad value */
        keypad_value = keypad_read_value();
        /* check if the user entered 6 digit number (Max number of password digits) */
        if(6 == number_of_clicks)
        {
            /* resetting variables */
            number_of_clicks = 0;
            lcd_output_data_col = 14;
            
            /* if password is valid -> turn on green led and open the door(moving motor) */
            if(entered_password == password)
            {
                ret = led_turn_on(&led_opened);
                ret = motor_move_right(&motor);
                ret = lcd_4bit_send_command(&lcd, LCD_CLEAR);
                ret = lcd_4bit_send_string_pos(&lcd , 1, 7, "Welcome!");
                incorrect_pass = 0;
                __delay_ms(3000);
                
                ret = led_turn_off(&led_opened);
                ret = motor_stop(&motor);
                ret = lcd_4bit_send_command(&lcd, LCD_CLEAR);
                ret = lcd_4bit_send_string(&lcd, "Enter Password:");
            }
            /* if password is not valid -> turn on red led */
            else
            {
                ret = led_turn_on(&led_locked);
                ret = lcd_4bit_send_command(&lcd, LCD_CLEAR);
                ret = lcd_4bit_send_string_pos(&lcd, 1, 2, "Incorrect Password!");
                //ret = lcd_4bit_send_string_pos(&lcd, 2, 2, "Please, try again");
                incorrect_pass++;
               
                __delay_ms(2000);
                ret = led_turn_off(&led_locked);
                ret = lcd_4bit_send_command(&lcd, LCD_CLEAR);
                ret = lcd_4bit_send_string(&lcd, "Enter Password:");
            }
            /* If the password entered incorrectly three times wait 60 sec */
            if(3 == incorrect_pass){
                ret = lcd_4bit_send_string_pos(&lcd, 1, 1, "Try again in    sec");
                uint8 _char = 0;
                for(uint8 counter = 60 ; counter > 0 ; counter--){
                    _char = '0' + (counter % 10);
                    ret = lcd_4bit_send_char_pos(&lcd, 1, 16, _char);
                    _char = '0' + ((counter/10) % 10);
                    ret = lcd_4bit_send_char_pos(&lcd, 1, 15, _char);
                    ret = led_turn_on(&led_locked);
                    __delay_ms(500);
                    ret = led_turn_off(&led_locked);
                    __delay_ms(500);
                }
                incorrect_pass = 0;
                ret = lcd_4bit_send_command(&lcd, LCD_CLEAR);
                ret = lcd_4bit_send_string(&lcd, "Enter Password:");
            }
            /* Clear previous password */
            entered_password = 0;
        }
        /* Taking password from the user */
        if('0' <= keypad_value && keypad_value <= '9')
        {
            number_of_clicks++;
            /* storing entered password */
           entered_password = (entered_password * 10) + (keypad_value - '0');
           ret = lcd_4bit_send_char_pos(&lcd, 2, ++lcd_output_data_col, keypad_value);
           __delay_ms(400);
           ret = lcd_4bit_send_char_pos(&lcd, 2, lcd_output_data_col, '*');
        }
        else{ /* Nothing */ }
    }
    
    return (EXIT_SUCCESS);
}

void application_intialize(){
    ret = ecu_layer_intialize();
}

/* Reading value of keypad */
uint8 keypad_read_value()
{
    uint8 current_value;
    
    ret = keypad_get_value(&keypad, &current_value);
    __delay_ms(DEBOUNE_TIME);
    if('\0' == current_value){
        return 0;
    }
    uint8 new_value;
    ret = keypad_get_value(&keypad, &new_value);
    
    if (current_value == new_value){
        return new_value;
    }
    return 0;  
}
