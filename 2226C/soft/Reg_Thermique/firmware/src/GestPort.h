/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _GEST_PORT_H    /* Guard against multiple inclusion */
#define _GEST_PORT_H 


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

#define BSP_OSC_FREQUENCY 40000000   //40MHz

/*--------------------------------------------------------------------------------*/
// PEC12
/*--------------------------------------------------------------------------------*/

//#define PEC12_A     PORTBbits.RB2
//#define PEC12_B     PORTBbits.RB3
//#define PEC12_PB    PORTBbits.RB4

/*--------------------------------------------------------------------------------*/
// LCD
/*--------------------------------------------------------------------------------*/
//On écrit dans le latch pour éviter les problèmes de R/W
#define LCD_DB4_W      LATBbits.LATB5
#define LCD_DB5_W      LATBbits.LATB6
#define LCD_DB6_W      LATBbits.LATB7
#define LCD_DB7_W      LATBbits.LATB8
#define LCD_BL_W       LATBbits.LATB9
#define LCD_E_W        LATBbits.LATB10
#define LCD_RW_W       LATBbits.LATB11
#define LCD_RS_W       LATBbits.LATB12

//On lit directement sur le port, sinon on obtient la valeur
//précédemment écrite dans le latch!!
#define LCD_DB4_R      PORTBbits.RB5
#define LCD_DB5_R      PORTBbits.RB6
#define LCD_DB6_R      PORTBbits.RB7
#define LCD_DB7_R      PORTBbits.RB8
#define LCD_BL_R       PORTBbits.RB9
#define LCD_E_R        PORTBbits.RB10
#define LCD_RW_R       PORTBbits.RB11
#define LCD_RS_R       PORTBbits.RB12

#define LCD_DB4_T      TRISBbits.TRISB5
#define LCD_DB5_T      TRISBbits.TRISB6
#define LCD_DB6_T      TRISBbits.TRISB7
#define LCD_DB7_T      TRISBbits.TRISB8
#define LCD_BL_T       TRISBbits.TRISB9
#define LCD_E_T        TRISBbits.TRISB10 
#define LCD_RW_T       TRISBbits.TRISB11
#define LCD_RS_T       TRISBbits.TRISB12


//// Definitions pour fonctions PLIB_PORTS
//#define LCD_DB4_PORT   0x01
//#define LCD_DB4_BIT    0
//#define LCD_DB5_PORT   0x01
//#define LCD_DB5_BIT    1
//#define LCD_DB6_PORT   0x01
//#define LCD_DB6_BIT    2
//#define LCD_DB7_PORT   0x01
//#define LCD_DB7_BIT    3
//#define LCD_BL_PORT    0x01
//#define LCD_BL_BIT     4
//#define LCD_E_PORT     0x01
//#define LCD_E_BIT      5
//#define LCD_RW_PORT    0x01
//#define LCD_RW_BIT     6
//#define LCD_RS_PORT    0x01
//#define LCD_RS_BIT     7

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************



    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    

#endif /* _GEST_PORT_H */

/* *****************************************************************************
 End of File
 */
