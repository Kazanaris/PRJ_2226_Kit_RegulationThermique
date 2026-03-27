/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "driver/tmr/drv_tmr_mapping.h"
#include "Mc32DriverLcd.h"
#include "Regulation_PID.h"
#include "GestPWM.h"
#include "Display.h"
#include "GesPec12.h"
#include "MesureADC.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;
S_ValMesure ValAD;
S_ValReglage Reglage;
//S_ParamConsigne S_Consigne;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */


void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    Reglage.Commande = 0.0;
    Reglage.Consigne = 0;
    Reglage.Erreur = 0;
    Reglage.PID_out = 0; 

    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    static bool first = true;
//    static uint16_t OC3PulseWidth = 0;
    
    /* Check the application's current state. */
    switch ( appData.state )
    {       
        /* Application's initial state. */
        case APP_STATE_INIT:
        {            
            //Initialisation de LCD
            Display_Init();

            //Initialisation de ADC
            ADC_Init();
            
            //Initialisation du Pec12
            Pec12Init();

            //Initialisation des timers
            DRV_TMR0_Start();
            DRV_TMR1_Start();

            //Initialisation des OCs
            DRV_OC0_Start();
            DRV_OC1_Start();

            appData.state = APP_STATE_WAIT;
            break;
        }
        
        case APP_STATE_WAIT:
        {
            //Ne rien faire
            break;
        }
        
        case APP_STATE_SERVICE_TASKS:
        {
            static uint16_t I_Reg = 0;
            if (first)
            {
                first = false;
                lcd_clear();    
            }
            
            // Régulation du système toutes les secondes           
            if(I_Reg > 1000)
            {                
                I_Reg = 0;
                
                CalculPID(ValGainPID(), ValConsigne(), &Reglage);
            }
            else
            {
               I_Reg++;
            }
            
            //Commande ventillateur
            CommandFan(ValPWM());

//            if (Pec12IsOK())
//            {
//                Pec12ClearOK();
//                
//                OC3PulseWidth += 200;
//                if (OC3PulseWidth > 600)
//                    OC3PulseWidth = 0;
//                                
//                DRV_OC1_PulseWidthSet(OC3PulseWidth);
//                
//            }           
            MenuGen();

            appData.state = APP_STATE_WAIT;
            
            break;
        }
        
        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

/*******************************************************************************
  Function:
    void APP_UpdateState ( APP_STATES newState )

  Remarks:
    See prototype in app.h.
 */

void APP_UpdateState(APP_STATES newState)
{
    /* Place the App state machine in its task state. */   
    appData.state = newState;
}

/*******************************************************************************
  Function:
    void CallbackTimer1(APP_STATES NewState)

  Remarks:
    See prototype in app.h.
 */

void CallbackTimer1(APP_STATES NewState)
{
    static uint16_t waitInit = 0;
    static uint8_t cycle = 0;
       
    //Lecture de l'adc
    ADC_Read(&ValAD);
    
    //Lecture du pec12
    ScanPec12(PORTBbits.RB2, PORTBbits.RB3, PORTBbits.RB4);
    
    //attend le temps de l'init
    if(waitInit == 3000)
    {
        //attend le cycle pour le program
        if(cycle < 9)
            cycle++;
        else
        {
            appData.state = APP_STATE_SERVICE_TASKS;
            cycle = 0;
        }
    }
    else
        waitInit++;
}

/*******************************************************************************
 End of File
 */
