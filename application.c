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

uint8 password[7] = {"123456"};
uint8 entered_password[7];
uint8 password_index = 0;
uint8 lcd_output_data_col = 14;

int main()
{
    application_intialize();
    
    ret = lcd_4bit_send_string(&lcd, "Enter Password:");
    
    while(1)
    {
        /* Read Keypad value */
        keypad_value = keypad_read_value();
        /* check if the user entered 6 digit number (Max number of password digits) */
        if(6 == password_index)
        {
            /* resetting entered password index & starting output data colomn */
            password_index = 0;
            lcd_output_data_col = 14;
            
            /* check for password validity */
            uint8 isPasswordValid = 1;
            for(uint8 index_check = 0 ; index_check < 6 ; index_check++){
                if(password[index_check] != entered_password[index_check]){
                    isPasswordValid = 0;
                    break;
                }
            }
            /* if password is valid -> turn on green led */
            if(1 == isPasswordValid)
            {
                ret = led_turn_on(&led_opened);
                ret = motor_move_right(&motor);
                ret = lcd_4bit_send_command(&lcd, LCD_CLEAR);
                ret = lcd_4bit_send_string_pos(&lcd , 1, 7, "Welcome!");
                __delay_ms(3000);
                
                ret = led_turn_off(&led_opened);
                ret = motor_stop(&motor);
                ret = lcd_4bit_send_command(&lcd, LCD_CLEAR);
            }
            /* if password is not valid -> turn on red led */
            else
            {
                ret = led_turn_on(&led_locked);
                ret = lcd_4bit_send_command(&lcd, LCD_CLEAR);
                ret = lcd_4bit_send_string_pos(&lcd, 1, 2, "Incorrect Password!");
                ret = lcd_4bit_send_string_pos(&lcd, 2, 2, "Please, try again");
               
                __delay_ms(2000);
                ret = led_turn_off(&led_locked);
                ret = lcd_4bit_send_command(&lcd, LCD_CLEAR);
                ret = lcd_4bit_send_string(&lcd, "Enter Password:");
            }
            
        }
        /* Taking password from the user */
        if('0' <= keypad_value && keypad_value <= '9')
        {
           entered_password[password_index++] =  keypad_value;
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
