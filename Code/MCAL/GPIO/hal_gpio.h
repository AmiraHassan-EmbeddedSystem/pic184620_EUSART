/* 
 * File:   hal_gpio.c
 * Author: Amira Hassan
 * 
 * Created on 19 / 9 / 2024, 6:33 am
 * 
 * Description: This file contains functions for configuring and controlling
 *              GPIO pins using the Hardware Abstraction Layer (HAL). The GPIO
 *              pins are configured to support both input and output functionality.
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* SECTION: Include */
#include <xc.h>
#include "../mcal_std_types.h"
#include "pic18f4620.h"
//#include "../../../"

/* SECTION: Macro Declarations */
#define BIT_MASK                1
#define MAX_PIN                 7   /* starting from pin0 to pin7 */
#define MAX_PORT                4   /* starting from portA(0) to portE(4) */    

/* SECTION: Macro Function Declarations */
#define HWREG8(_X)                 (*((volatile uint8 *)(_X)))
#define SET_BIT(REG, POS_BIT)      (REG |= ( BIT_MASK << POS_BIT ))
#define CLEAR_BIT(REG, POS_BIT)    (REG &= ~( BIT_MASK << POS_BIT ))
#define TOGGLE_BIT(REG, POS_BIT)   (REG ^= ( BIT_MASK << POS_BIT ))
#define READ_BIT(REG, POS_BIT)     (( REG >> POS_BIT ) & BIT_MASK)



/* SECTION: Data Type Declarations */
typedef enum{
    GPIO_PORTA,
    GPIO_PORTB,
    GPIO_PORTC,
    GPIO_PORTD,
    GPIO_PORTE,
}port_index_t;

typedef enum{
    GPIO_PIN0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
}pin_index_t;

typedef enum{
    GPIO_OUTPUT,
    GPIO_INPUT
}direction_t;

typedef enum{
    GPIO_LOW,
    GPIO_HIGH,
}logic_t;

typedef struct{
    uint8 Port:3;           /*@ref Port_index_t*/
    uint8 Pin:3;            /*@ref pin_index_t*/
    uint8 Direction:1;      /*@ref Direction_t*/
    uint8 Logic:1;          /*@ref Logic_t*/
}pin_config_t;


/* SECTION: Interface Function Declarations */

Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config);


Std_ReturnType gpio_port_direction_initialize(port_index_t port, uint8 direction);
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status);
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic);
Std_ReturnType gpio_port_read_logic(port_index_t port, logic_t *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);




#endif	/* HAL_GPIO_H */

