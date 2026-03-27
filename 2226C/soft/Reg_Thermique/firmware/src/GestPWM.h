/* ************************************************************************** */
/** Descriptive File Name

  @Company
    ETML-ES

  @File Name
    GestPWM.h

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _GESTPWM_H    /* Guard against multiple inclusion */
#define _GESTPWM_H

//Prototype PWM Resistance de puissance et du ventillateur
void CommandHeater(uint16_t Val_Commande);
void CommandFan(uint16_t Val_PWM);

#endif /* _GESTPWM_H */

/* *****************************************************************************
 End of File
 */
