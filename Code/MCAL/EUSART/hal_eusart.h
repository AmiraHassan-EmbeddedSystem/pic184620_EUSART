/* 
 * File:   hal_eusart.h
 * Author: ah427
 *
 * Created on 24 ??????, 2024, 07:27 ?
 */

#ifndef HAL_EUSART_H
#define	HAL_EUSART_H

/* Section: Include */
#include "../GPIO/hal_gpio.h"
#include "../../MCAL/INTERRUPT/internal_interrupt.h"

/* SECTION: Macro Declarations */
    // Transmission
#define EUSART_SELECT_9BIT_TRANSMIT_DISABLE   0
#define EUSART_SELECT_9BIT_TRANSMIT_ENABLE    1

#define EUSART_TRANSMIT_DISABLE                  0
#define EUSART_TRANSMIT_ENABLE                   1

#define EUSART_TRANSMIT_INTERRUPT_DISABLE        0
#define EUSART_TRANSMIT_INTERRUPT_ENABLE         1

    // In Transmission & Receiver
#define EUSART_ASYNCHRONOUS_MODE                 0
#define EUSART_SYNCHRONOUS_MODE                  1

#define EUSAR_LOW_SPEED            0
#define EUSAR_HIGH_SPEED           1

#define EUSART_ENABLE   1
#define EUSART_DISABLE  0

    // Receiver
#define EUSART_SELECT_9BIT_RECEIVE_DISABLE   0
#define EUSART_SELECT_9BIT_RECEIVE_ENABLE    1

#define EUSART_RECEIVE_ENABLE       1
#define EUSART_RECEIVE_DISABLE      0

#define EUSART_RECEIVE_INTERRUPT_DISABLE        0
#define EUSART_RECEIVE_INTERRUPT_ENABLE         1

    // Baud Rate
#define EUSART_16BAUD_RATE_GEN          1
#define EUSART_8BAUD_RATE_GEN           0

#define EUSART_BAUD_RATE_ENABLE         1
#define EUSART_BAUD_RATE_DISABLE        0

    //Framing Error
#define EUSART_FRAMING_ERROR_DETECTED     1
#define EUSART_FRAMING_ERROR_CLEARED      0

    //Overrun Error
#define EUSART_OVERRUN_ERROR_DETECTED     1
#define EUSART_OVERRUN_ERROR_CLEARED      0

/* SECTION: Macro Function Declarations */

/* SECTION: Data Type Declarations */

typedef union{
    struct{
        uint8 reseved:6;
        uint8 framing_error:1;
        uint8 overrun_error:1;
    };
    uint8 status;
}error_status_t;

typedef enum{
    ASYNC_8BIT_LOW = 0,
    ASYNC_8BIT_HIGH,
    ASYNC_16BIT_LOW,
    ASYNC_16BIT_HIGH,
    SYNC_8BIT,
    SYNC_16BIT,
}baud_rate_gen_t;

typedef struct{
    uint8 reseved:4;
    uint8 transmit_enable:1;
    uint8 transmit_interrupt_enable:1;
    uint8 select_9bit_transmit:1;
    interrupt_priority tx_interrupt_priority;
}transmit_t;

typedef struct{
    uint8 reseved:4;
    uint8 receive_enable:1;
    uint8 receive_interrupt_enable:1;
    uint8 select_9bit_receive:1;
    interrupt_priority rx_interrupt_priority;
}receive_t;

typedef struct{
    uint32 baudrate;
    baud_rate_gen_t baud_rate_config;
    transmit_t tx;
    receive_t rx;
    error_status_t error_status;
    void(*EUSART_TXDefaultInterruptHandler)(void);
    void(*EUSART_RXDefaultInterruptHandler)(void);
    void(*EUSART_FraminErrorInterruptHandler)(void);
    void(*EUSART_OverrunErrorInterruptHandler)(void);

}eusart_t;

/* SECTION: Interface Function Declarations */
Std_ReturnType EUSART_Async_Init(const eusart_t *eusart);
Std_ReturnType EUSART_Async_DeInit(const eusart_t *eusart);
Std_ReturnType EUSART_Async_ReadCharBlocking(uint8 *data);
Std_ReturnType EUSART_Async_ReadCharNotBlocking(uint8 *data);
Std_ReturnType EUSART_Async_Rx_Restart();

Std_ReturnType EUSART_Async_WriteCharBlocking(uint8 data);
Std_ReturnType EUSART_Async_WriteStringBlocking(uint8 *data, uint16 lenStr);
Std_ReturnType EUSART_Async_WriteCharNonBlocking(uint8 data);
Std_ReturnType EUSART_Async_WriteStringNonBlocking(uint8 *data, uint16 lenStr);
#endif	/* HAL_EUSART_H */

