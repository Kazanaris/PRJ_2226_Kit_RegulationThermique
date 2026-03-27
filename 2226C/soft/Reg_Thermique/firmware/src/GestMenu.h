/* ************************************************************************** */
/** Descriptive File Name

  @Company
  ETML-ES

  @File Name
  GestMenu.c

  @Description
  Gestion du menu
 */
/* ************************************************************************** */

#ifndef _GESTMENU_H    /* Guard against multiple inclusion */
#define _GESTMENU_H

#include <stdbool.h>
#include <stdint.h>


#define FORME   1
#define FREQUENCE   2
#define AMPLITUDE   3
#define OFFSET  4

#define KPROPORTIONNEL   1
#define KINTEGRAL   2
#define KDERIVE   3

typedef enum  { SrcConsigne = 1, paramConsigne, GainPID, Affichage_Data } E_MenuSelect;

typedef enum  { SignalSinus, SignalTriangle, SignalDentDeScie, SignalCarre } E_FormesSignal;

typedef struct {
      int16_t Consigne;
      int16_t Temp; 
      int16_t PID_out;
      int16_t Erreur;
      double Commande;        
} S_ValReglage;

typedef struct {
      E_FormesSignal Forme;
      int16_t Amplitude;
      uint16_t Frequence;
      int16_t Offset;
} S_ParamConsigne;

typedef struct {
      float Kp;
      float Ki;
      float Kd;
} S_ParamGainPID;

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Functions                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

void MenuGen();

void MenuConsigne(uint8_t Consigne_Select, S_ParamConsigne *S_Consigne);

void MenuGainPID(uint8_t GainPID_Select, S_ParamGainPID *S_GainPID);

void MenuData();

void MenuSrc(bool Src);

const S_ParamGainPID* ValGainPID();

const S_ParamConsigne* ValConsigne();

const uint8_t ValPWM();

#endif /* _GESTMENU_H */

/* *****************************************************************************
 End of File
 */
