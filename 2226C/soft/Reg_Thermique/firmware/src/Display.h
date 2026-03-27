/* ************************************************************************** */
/** Descriptive File Name

  @Company
  ETML-ES

  @File Name
  Display.h

  @Description
    Affichage du menu
 */
/* ************************************************************************** */

#ifndef _DISPLAY_H    /* Guard against multiple inclusion */
#define _DISPLAY_H

#include "MesureADC.h"

typedef struct {
      uint16_t Erreur;
      uint16_t Consigne;    
} S_Affichage;

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Functions                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

void Display_Gen(uint8_t PointerG, const char* SrcCons, bool Flag_Pec12_Ok, bool FlagMenuGen );

void Display_Init(void);

void Display_Mesure(const S_ValMesure* ValAD, bool FlagMenuData);

void DisplayConsigne(uint8_t PointerC, const S_ParamConsigne *Consigne, bool Flag_Pec12_Ok_1);

void DisplayGainPID(uint8_t PointerP, const S_ParamGainPID *GainPID, bool Flag_Pec12_Ok_2);

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
