/* 
 * File:   internal_interrupt.h
 * Author: Amira Hassan
 * 
 * Created on 19 / 9 / 2024, 6:33 am
 * 
 * Description: This file contains the initialization and handling functions 
 *              for internal interrupts using the Hardware Abstraction Layer (HAL).
 *              Internal interrupts are triggered by internal peripherals such as timers,
 *              ADCs, or communication modules (e.g., UART, SPI) to handle specific events 
 *              (e.g., timer overflow, data reception).
 *             
 */

#ifndef INTERNAL_INTERRUPT_H
#define	INTERNAL_INTERRUPT_H

/* SECTION: Include */
#include "manage_interrupt.h"

/* SECTION: Macro Declarations */

/*
 * EUSART_INTERRUPT
 */
#ifdef EUSRAT_INTERRUPT_FEATURE_ENABLE
    #ifdef EUSRAT_Tx_INTERRUPT_FEATURE_ENABLE
        #define EUSRAT_Tx_INTERRUPT_ENABLE()    (PIE1bits.TXIE = 1)
        #define EUSRAT_Tx_INTERRUPT_DISABLE()    (PIE1bits.TXIE = 0)

        #ifdef INTERRUPT_PRIORITY_LEVELS
            #define EUSRAT_Tx_INTERRUPT_LOW_PRIORITY()    (IPR1bits.TXIP = 0)
            #define EUSRAT_Tx_INTERRUPT_HIGH_PRIORITY()    (IPR1bits.TXIP = 1)
        #endif
    #endif

    #ifdef EUSRAT_Rx_INTERRUPT_FEATURE_ENABLE
        #define EUSRAT_Rx_INTERRUPT_ENABLE()    (PIE1bits.RCIE = 1)
        #define EUSRAT_Rx_INTERRUPT_DISABLE()    (PIE1bits.RCIE = 0)

        #ifdef INTERRUPT_PRIORITY_LEVELS
            #define EUSRAT_Rx_INTERRUPT_LOW_PRIORITY()    (IPR1bits.RCIP = 0)
            #define EUSRAT_Rx_INTERRUPT_HIGH_PRIORITY()    (IPR1bits.RCIP = 1)
        #endif
    #endif
#endif

/* SECTION: Macro Function Declarations */
/* SECTION: Data Type Declarations */

/* SECTION: Interface Function Declarations */

#endif	/* INTERNAL_INTERRUPT_H */

