/* 
 * File:   manage_interrupt.h
 * Author: Amira Hassan
 *
 * Created on  19 / 9 / 2024, 6:33 am
 * 
 * Description: This header file declares the interface functions for managing
 *              interrupts in the project. It includes the declarations for
 *              interrupt service routines (ISRs) for various internal
 *              interrupts, as well as ADC-related interrupts.
 */  

#ifndef MANAGE_INTERRUPT_H
#define	MANAGE_INTERRUPT_H

/* SECTION: Include */
#include "interrupt_config.h"

/* SECTION: Interface Function Declarations */
void ISR_TX_EUSART(void);
void ISR_RX_EUSART(void);


#endif	/* MANAGE_INTERRUPT_H */

