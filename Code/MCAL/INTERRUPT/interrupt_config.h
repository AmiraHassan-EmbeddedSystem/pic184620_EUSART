/* 
 * File:   interrupt_config.h
 * Author: Amira Hassan
 * 
 * Created on 19 / 9 / 2024, 6:33 am
 * 
 * Description: This file contains macro definitions and function-like macros for 
 *              configuring and managing interrupts, including global interrupts, 
 *              peripheral interrupts, and priority-based interrupt handling.
 *   
 */

#ifndef INTERRUPT_CONFIG_H
#define	INTERRUPT_CONFIG_H

/* SECTION: Include */
#include "interrupt_gen_cfg.h"

/* SECTION: Macro Declarations */
#define INTERRUPT_ENABLE        1
#define INTERRUPT_DISABLE       0

#define INTERRUPT_OCCUR         1
#define INTERRUPT_NOT_OCCUR     0

#define INTERRUPT_PRIORITY_ENABLE   1
#define INTERRUPT_PRIORITY_DISABLE  0




/* SECTION: Macro Function Declarations */
#ifdef INTERRUPT_PRIORITY_LEVELS
    #define Interrupt_priorityLevelEnable()   (RCONbits.IPEN = 1)
    #define Interrupt_priorityLevelDisable()   (RCONbits.IPEN = 0)

    #define Interrupt_HighPriorityEnable()   (INTCONbits.GIEH = 1)
    #define Interrupt_HighPriorityDisable()   (INTCONbits.GIEH = 0)

    #define Interrupt_LowPriorityEnable()   (INTCONbits.GIEL = 1)
    #define Interrupt_LowPriorityDisable()   (INTCONbits.GIEL = 0)

#else
    #define Interrupt_globalInterruptEnable()     (INTCONbits.GIE = 1)
    #define Interrupt_globalInterruptDiable()     (INTCONbits.GIE = 0)
    #define Interrupt_prepheralInterruptEnable()     (INTCONbits.PEIE = 1)
    #define Interrupt_prepheralInterruptDiable()     (INTCONbits.PEIE = 0)
#endif

/* SECTION: Data Type Declarations */
typedef enum{
    LOW_PRIORITY = 0,
    HIGH_PRIORITY
}interrupt_priority;

/* SECTION: Interface Function Declarations */

#endif	/* INTERRUPT_CONFIG_H */

