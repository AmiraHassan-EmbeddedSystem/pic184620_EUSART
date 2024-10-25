/* 
 * File:   mcal_std_types.h
 * Author: Amira Hassan
 *
 * Created on 19 / 9 / 2024, 6:33 am
 * 
 * Description: This header file contains standard type definitions and macro 
 *              declarations used across the MCAL (Microcontroller Abstraction Layer) 
 *              for various modules. It provides typedefs for commonly used data types
 *              and defines macros for standard return types.
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* SECTION: Include */
#include "config.h"
/* SECTION: Macro Function Declarations */
#define _XTAL_FREQ 8000000UL
/* SECTION: Data Type Declarations */

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;

typedef uint8 Std_ReturnType;

/* SECTION: Macro Declarations */

#define E_OK           (Std_ReturnType)1
#define E_NOT_OK       (Std_ReturnType)1

/* SECTION: Interface Function Declarations */


#endif	/* MCAL_STD_TYPES_H */

