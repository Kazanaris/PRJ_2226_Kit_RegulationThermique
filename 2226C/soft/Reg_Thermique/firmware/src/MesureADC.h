/* ************************************************************************** */
/** Descriptive File Name

  @Company
    ETML-ES

  @File Name
    MesureADC.h

  @Description
 *  Gestion de l'ADC
 */
/* ************************************************************************** */

#include <stdint.h>


#ifndef _MESUREAD_H    /* Guard against multiple inclusion */
#define _MESUREAD_H

typedef struct {
    float Ref3V;         //AN0
    float Mes_I;         //AN6
    float Mes_Temp;      //AN7
    float Mes_PID_out;   //AN8
    float Consigne_EXT;  //AN9
} S_ValMesure;

/*--------------------------------------------------------*/
// Fonction ADC_Init                                      //
/*--------------------------------------------------------*/
void ADC_Init(void);

/*--------------------------------------------------------*/
// Fonction ADC_Read                                      //
/*--------------------------------------------------------*/
void ADC_Read(S_ValMesure *ValReadAD);

/*--------------------------------------------------------*/
// Fonction ConvToDegre                                   //
/*--------------------------------------------------------*/
uint8_t ConvToDegre(uint16_t ValAD);

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
