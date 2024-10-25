/*
 * File:   app.c
 * Author: Amira Hassan
 *
 * Created on 24 ??????, 2024, 07:22 ?
 */


#include <xc.h>
#include "app.h"

led_t led1 = { .port_name = GPIO_PORTD, .pin = GPIO_PIN0, .led_status = LED_OFF};
led_t led2 = { .port_name = GPIO_PORTD, .pin = GPIO_PIN1, .led_status = LED_OFF};


volatile uint8 tx_interrupt = 0, rx_interrupt = 0, overrunError_interrupt = 0, framingError_interrupt = 0;
uint8 readByte;

void Eusart_Call_Tx_Interrupt(void){
    tx_interrupt++;
}

void Eusart_Call_Rx_Interrupt(void){
    uint8 temp = 0;
    EUSART_Async_ReadCharNotBlocking(&readByte);
    switch(readByte){
        case 'a':
            led_turn_on(&led1);
            EUSART_Async_WriteStringBlocking("\r\rTurn On Led1\r", 15);
            break;
        case 'b':
            led_turn_on(&led2);
            EUSART_Async_WriteStringBlocking("\r\rTurn On Led2\r", 15);
            break;
        case 'c':
            led_turn_off(&led1);
            EUSART_Async_WriteStringBlocking("\r\rTurn Off Led1\r", 16);
            break;
        case 'd':
            led_turn_off(&led2);
            EUSART_Async_WriteStringBlocking("\r\rTurn Off Led2\r", 16);
            break;
        case 'e':
            led_turn_on(&led1);
            led_turn_on(&led2);
            EUSART_Async_WriteStringBlocking("\r\rTurn On Led1\r", 15);
            EUSART_Async_WriteStringBlocking("Turn On Led2\r", 13);
            break;
        default:
            led_turn_off(&led1);
            led_turn_off(&led2);
            EUSART_Async_WriteStringBlocking("\r\rTurn Off Led1\r", 16);
            EUSART_Async_WriteStringBlocking("Turn Off Led2\r", 14);
            break;
        }
    temp = RCREG;
}

void Eusart_Call_OverrunError_Interrupt(void){
    overrunError_interrupt++;
    EUSART_Async_Rx_Restart();
}

void Eusart_Call_FramingError_Interrupt(void){
    framingError_interrupt++;
    uint8 _data = 0;
    EUSART_Async_ReadCharNotBlocking(&_data);
}

eusart_t eusart_obj = {
    .baudrate = 9600,
    .baud_rate_config = ASYNC_8BIT_HIGH,
    
    .tx.transmit_enable = EUSART_TRANSMIT_ENABLE,
    .tx.transmit_interrupt_enable = EUSART_TRANSMIT_INTERRUPT_ENABLE,
    .tx.select_9bit_transmit = EUSART_SELECT_9BIT_TRANSMIT_DISABLE,
    
    .rx.receive_enable = EUSART_RECEIVE_ENABLE,
    .rx.receive_interrupt_enable = EUSART_RECEIVE_INTERRUPT_ENABLE,
    .rx.select_9bit_receive = EUSART_SELECT_9BIT_RECEIVE_DISABLE,
    
    
    .EUSART_FraminErrorInterruptHandler = NULL,
    .EUSART_OverrunErrorInterruptHandler = NULL,
    .EUSART_RXDefaultInterruptHandler = Eusart_Call_Rx_Interrupt,
    .EUSART_TXDefaultInterruptHandler = Eusart_Call_Tx_Interrupt,
};



void initialization(void);
Std_ReturnType ret = E_NOT_OK;

int main(void) {
    initialization();
    
   
    while(1){

    }
    return(EXIT_SUCCESS);
}

void initialization(void){
    EUSART_Async_Init(&eusart_obj);
    led_initialize(&led1);
    led_initialize(&led2);
}
