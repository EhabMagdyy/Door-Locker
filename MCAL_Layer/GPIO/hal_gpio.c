/* 
 * File:   hal_gpio.c
 * Author: Ehab
 *
 * Created on 24 ?????, 2023, 07:06 ?
 */

#include "hal_gpio.h"

volatile uint8* tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile uint8* port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};
volatile uint8* lat_registers[] = {&LATA, &LATB, &LATC, &LATD, &LATE};

/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if(_pin_config == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        switch(_pin_config->direction){
            case GPIO_direction_output:   
                CLEAR_BIT(*tris_registers[_pin_config->port] , _pin_config->pin);
                break;
            case GPIO_direction_input:
                SET_BIT(*tris_registers[_pin_config->port] , _pin_config->pin);
                break;
            default:    ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t
 * @param logic
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic){
    Std_ReturnType ret = E_OK;
    if(_pin_config == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        switch(logic){
            case GPIO_LOW:
                CLEAR_BIT(*lat_registers[_pin_config->port] , _pin_config->pin);
                break;
            case GPIO_HIGH:
                SET_BIT(*lat_registers[_pin_config->port] , _pin_config->pin);
                break;
            default:    ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t
 * @param logic
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic){
    Std_ReturnType ret = E_OK;
    if(_pin_config == NULL || logic == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        *logic = READ_BIT(*port_registers[_pin_config->port] , _pin_config->pin);
    }
    return ret;    
}

/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t  
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if(_pin_config == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_intialize(_pin_config);
        ret = gpio_pin_write_logic(_pin_config,_pin_config->logic);
    }
    return ret; 
}
