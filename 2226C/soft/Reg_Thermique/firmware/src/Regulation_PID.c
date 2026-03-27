/* ************************************************************************** */
/** Descriptive File Name

  @Company
    ETML-ES

  @File Name
    RegulationPID.c

  @Description
 *  Fichier c traitant la régulationPID
 */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#define CMD_MAX 1000
#define TEMP_MES_MAX 150    //c'est le capteur de température qui limite à 150 deg !

#include "Regulation_PID.h"
#include "MesureADC.h"
#include "GestPWM.h"
#include "GestMenu.h"
#include "system_config.h"
#include <string.h>

//----------------------  CONSTANTES PID ---------------------------------------
//float Kp = 1;       // Kp (proportionnel)  
//float Ki = 0;       // Ki (intégrateur)
//float Kd = 0;       // Kd (dérivateur)
//
////-- erreur 
//float erreurk, erreurk_1; 
//
////-- consigne 
//float consigne;
//
////-- mesure 
//float mesure;
//
////-- constante PID
//float Up_k = 0, Ui_k = 0, Ui_k_1 = 0,  Ud_k = 0, Ud_k_1 = 0; 
//float Uk;

//void CalculerPID(const S_ParamGainPID *ValGainPID)  
//{
//    //-- proportionnel --//
//    Up_k = ValGainPID->Kp * erreurk; 
//    
//    //-- intégrateur --// 
////    Ui_k = ValGainPID->Ki * erreurk + Ui_k_1; 
//    
//    //-- dérivateur --// 
////    Ud_k = ValGainPID->Kd * (erreurk - erreurk_1); 
//            
//    //-- final --// 
//    Uk = Up_k + Ui_k + Ud_k; 
//     
//} 
//
//void CalculerErreur()
//{
//    erreurk = consigne - mesure; 
//}
void CalculPID(const S_ParamGainPID *ValGainPID, const S_ParamConsigne* ValConsigne, S_ValReglage* pReglage)
{
    S_ValMesure ValAD;
    
    double Commande_kp;
    static double Commande_ki = 0.0;
        
    ADC_Read(&ValAD);
    
    pReglage->Temp = /*ConvToDegre(*/ValAD.Mes_Temp/*)*/;
    
    pReglage->Consigne = ValConsigne->Offset + ValConsigne->Amplitude;
    
    //Calcul de l'erreur
    pReglage->Erreur = pReglage->Consigne - pReglage->Temp;

    Commande_kp = pReglage->Erreur * ValGainPID->Kp;
    
    Commande_ki += pReglage->Erreur * ValGainPID->Ki;
        
    //Anti wind-up    
    if(Commande_ki < -CMD_MAX)
    {
        Commande_ki = -CMD_MAX;
    }
    else if (Commande_ki > CMD_MAX)
    {
        Commande_ki = CMD_MAX;   
    }      
    pReglage->Commande = Commande_kp + Commande_ki;
    
    //Saturation commande 
    if(pReglage->Commande < 0)
    {
        pReglage->Commande = 0;
    }
    else if (pReglage->Commande > CMD_MAX)
    {
        pReglage->Commande = CMD_MAX;   
    }
      
    //Sécurité température
    if (pReglage->Temp > TEMP_MES_MAX)
    {
        pReglage->Commande = 0;
    }    

    //Commande PWM ventillateur
    CommandHeater(pReglage->Commande);
}