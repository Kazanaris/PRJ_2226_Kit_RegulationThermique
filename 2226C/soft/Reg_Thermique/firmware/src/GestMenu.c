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

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Includes                                                          */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include "system_config.h"
#include "app.h"
#include "GestMenu.h"
#include "Mc32DriverLcd.h"
#include "GesPec12.h"
#include "GestPWM.h"
#include "MesureADC.h"
#include "Display.h"

// Variable definitions
uint8_t PWM_Fan = 0;

static bool FlagMenuConsigne, FlagMenuGainPID, FlagMenuData; 
static bool Flag_Pec12_Ok = 0, Flag_Pec12_Ok_Cons = 0,Flag_Pec12_Ok_Gain = 0, Flag_Pec12_Ok_Mes = 0 ;
static bool FlagConsigne, FlagGainPID, FlagData;
static bool FlagMenuGen = 1;

static S_ParamConsigne Consigne;
static S_ParamGainPID S_GainPID;
S_ValMesure ValAD;

E_MenuSelect MenuSelect;

const char *SourceCons[3] = {"Int","Ext","USB"};

/*--------------------------------------------------------*/
void MenuGen()
{   
    static bool Src = 0 ;
    static uint8_t GestMenuG = 1;
    static uint8_t Consigne_Select = 1;
    static uint8_t GainPID_Select = 1;   
    
/*-------------------------Menu-général-----------------------*/
    if(FlagMenuGen == 1)
    {
         if(Pec12IsPlus())
        {  
            Pec12ClearPlus();
            GestMenuG++; 
            if(GestMenuG > 4)
            {
                GestMenuG = 1;
            }
        }
        else if(Pec12IsMinus())
        {          
            Pec12ClearMinus();
            GestMenuG--;
            if(GestMenuG < 1)
            {
                GestMenuG = 4;
            }
        }
        if(Pec12IsOK())
        {
            Pec12ClearOK();
            Flag_Pec12_Ok = 1;         
        }  
        MenuSelect = GestMenuG;
        Display_Gen(MenuSelect, SourceCons[Src], Flag_Pec12_Ok, FlagMenuGen); 
    }
    
/*-------------------------Menu-consigne-----------------------*/
    if(FlagMenuConsigne == 1)
    {   
        FlagMenuGen = 0;
        if(Pec12IsPlus())
        {                  
            Consigne_Select++;
            if(Consigne_Select > 4)
            {
                Consigne_Select = 1;
            }
            Pec12ClearPlus();
        }
        else if(Pec12IsMinus())
        {                          
            Consigne_Select--;
            if(Consigne_Select < 1)
            {
                Consigne_Select = 4;
            }
            Pec12ClearMinus();
        }         
        if(Pec12IsOK())
        {                                
            Pec12ClearOK();
            Flag_Pec12_Ok_Cons = 1;
        }
    }
    
/*-------------------------Menu-GainPID-----------------------*/   
    if(FlagMenuGainPID == 1)
    { 
        FlagMenuGen = 0;
        if(Pec12IsPlus())
        {                  
            GainPID_Select++; 
            if(GainPID_Select > 3)
            {
                GainPID_Select = 1;
            }
            Pec12ClearPlus();
        }
        else if(Pec12IsMinus())
        {                          
            GainPID_Select--;
            if(GainPID_Select < 1)
            {
                GainPID_Select = 3;
            }
            Pec12ClearMinus();
        }
        if(Pec12IsOK())
        {
           Pec12ClearOK();
           Flag_Pec12_Ok_Gain = 1;         
        }        
    }

/*-------------------------Selection-Menu-Principal-----------------------*/    
    switch (MenuSelect)
    {  
        //Choix de la source de la Consigne(interne ou externe)
        case SrcConsigne:
            
            if(Flag_Pec12_Ok)
            {
                if(Src == 0)
                {
                    Src++;                       
                }
                else if(Src == 1)
                {
                    Src++;                       
                }
                else if (Src >= 2)
                {
                    Src = 0;                        
                }
                Flag_Pec12_Ok = 0;                
            }        
        break;
        
        case paramConsigne:

            if(Flag_Pec12_Ok == 1)
            {
                lcd_clear();
                FlagMenuGen = 0;
                FlagMenuConsigne = 1;
                FlagMenuGainPID = 0;
                FlagMenuData = 0;
                Flag_Pec12_Ok = 0;
                FlagConsigne = 1;
            }
            if (FlagConsigne == 1)
            {
                if(Pec12IsOK())
                {        
                    Pec12ClearOK();
                    if(Flag_Pec12_Ok_Cons == 0 )
                    {
                      Flag_Pec12_Ok_Cons = 1;  
                    }
                    else
                        Flag_Pec12_Ok_Cons = 0;
                        FlagMenuConsigne = 1;
                }
                if(Pec12IsESC())
                {    
                    Pec12ClearESC();
                    FlagMenuGen = 1;
                    FlagMenuConsigne = 0;
                    FlagConsigne = 0;
                    Flag_Pec12_Ok = 0;
                    Flag_Pec12_Ok_Cons = 0;
                    lcd_clear();
                }
                MenuConsigne(Consigne_Select, &Consigne);
                DisplayConsigne(Consigne_Select, &Consigne, Flag_Pec12_Ok_Cons);
            }           
        break;
        
        case GainPID:

            if(Flag_Pec12_Ok == 1)
            {
                lcd_clear();
                FlagMenuGen = 0;
                FlagMenuConsigne = 0;
                FlagMenuGainPID = 1;
                FlagMenuData = 0;
                Flag_Pec12_Ok = 0;
                FlagGainPID = 1;
            }
            if(FlagGainPID == 1)
            {
                if(Pec12IsOK())
                {        
                    Pec12ClearOK();
                    if(Flag_Pec12_Ok_Gain == 0 )
                    {
                      Flag_Pec12_Ok_Gain = 1;  
                    }
                    else
                    {
                        Flag_Pec12_Ok_Gain = 0;
                        FlagMenuGainPID = 1;
                    }                
                }                
                if(Pec12IsESC())
                {    
                    Pec12ClearESC();
                    FlagMenuGainPID = 0;
                    FlagGainPID = 0;
                    FlagMenuGen = 1;
                    Flag_Pec12_Ok = 0;
                    Flag_Pec12_Ok_Gain = 0;
                    lcd_clear();
                }
                DisplayGainPID(GainPID_Select, &S_GainPID, Flag_Pec12_Ok_Gain);
                MenuGainPID(GainPID_Select, &S_GainPID);
            }  
        break;
        
        case Affichage_Data:
            
            if(Flag_Pec12_Ok == 1)
            {
                lcd_clear();
                FlagMenuGen = 0;
                FlagMenuData = 1;
                Flag_Pec12_Ok = 0;
                FlagData = 1;
            }            
            if(FlagData == 1)
            {            
                if(Pec12IsESC())
                {    
                    Pec12ClearESC();
                    FlagMenuData = 0;
                    FlagMenuGen = 1;                    
                    Flag_Pec12_Ok = 0;
                    Flag_Pec12_Ok_Mes = 0;
                    lcd_clear();
                }
                Display_Mesure(&ValAD, FlagMenuData);
            }
        break;
        
        default :
            break;                  
    }
}

/*-------------------------Consigne-----------------------*/
void MenuConsigne(uint8_t Consigne_Select,S_ParamConsigne *Consigne)
{        
    if(FlagConsigne == 1)
    {
        switch(Consigne_Select)
        {
            case FORME:                

                if(Flag_Pec12_Ok_Cons == 1)
                {  
                    FlagMenuConsigne = 0;
                    if(Pec12IsPlus())
                    {  
                        Pec12ClearPlus();
                        
                        if(Consigne->Forme >= 3)
                        {
                            Consigne->Forme = 0;
                        }
                        else
                        {
                            Consigne->Forme++;
                        }                       
                    }
                    else if(Pec12IsMinus())
                    {                                  
                        Pec12ClearMinus();
                        if(Consigne->Forme <= 0)
                        {
                            Consigne->Forme = 3;
                        }
                        else
                        {
                            Consigne->Forme-- ;
                        } 
                    }
                    if(Pec12IsOK())
                    {
                        Pec12ClearOK();
                        Flag_Pec12_Ok_Cons = 0;  
                    }
                }
                break;

            case FREQUENCE:               

                if(Flag_Pec12_Ok_Cons == 1 )
                {  
                    FlagMenuConsigne = 0;
                    if(Pec12IsPlus())
                    {  
                        Pec12ClearPlus();
                        if(Consigne->Frequence >= 1000)
                        {
                            Consigne->Frequence = 0;
                        }
                        else
                        {
                           Consigne->Frequence = Consigne->Frequence + 100;
                        }                       
                    }
                    else if(Pec12IsMinus())
                    {                                 
                        Pec12ClearMinus();
                        if(Consigne->Frequence <= 0)
                        {
                            Consigne->Frequence = 1000;
                        }
                        else
                        {
                            Consigne->Frequence = Consigne->Frequence - 100;
                        }
                    }
                    if(Pec12IsOK())
                    {
                        Pec12ClearOK();                    
                        Flag_Pec12_Ok_Cons = 0;  
                    }
                }
                break;

            case AMPLITUDE:                

                if(Flag_Pec12_Ok_Cons)
                {        
                    FlagMenuConsigne = 0;
                    if(Pec12IsPlus())
                    {                          
                        if(Consigne->Amplitude >= 3000)
                        {
                            Consigne->Amplitude = 0;
                        }
                        else
                        {
                            Consigne->Amplitude = Consigne->Amplitude + 100;
                        }
                        Pec12ClearPlus();
                    }
                    else if(Pec12IsMinus())
                    {                                  
                        Pec12ClearMinus();
                        if(Consigne->Amplitude <= 0)
                        {
                            Consigne->Amplitude = 3000;
                        }
                        else
                        {
                            Consigne->Amplitude = Consigne->Amplitude - 100;
                        }                        
                    }
                    if(Pec12IsOK())
                    {
                        Pec12ClearOK();  
                        Flag_Pec12_Ok_Cons = 0;  
                    }
                }
                break;

            case OFFSET:                

                if(Flag_Pec12_Ok_Cons)
                {      
                    FlagMenuConsigne = 0;
                    if(Pec12IsPlus())
                    {  
                        Pec12ClearPlus();
                        if(Consigne->Offset >= 50)
                        {
                            Consigne->Offset = 0;
                        }
                        else
                        {
                            Consigne->Offset = Consigne->Offset + 5;
                        }                        
                    }

                    else if(Pec12IsMinus())
                    {                                  
                        Pec12ClearMinus();
                        if(Consigne->Offset <= 0)
                        {
                            Consigne->Offset = 50;
                        }
                        else
                        {
                            Consigne->Offset = Consigne->Offset - 5;
                        }                      
                    }
                    if(Pec12IsOK())
                    {
                        Pec12ClearOK();
                        Flag_Pec12_Ok_Cons = 0;  
                    }
                }
                break;

            default :
                break;
        } 
    }    
}

/*-----------------------GainPID-------------------------------*/
void MenuGainPID(uint8_t GainPID_Select, S_ParamGainPID *S_GainPID)
{      
    if(FlagGainPID == 1)
    {
        switch(GainPID_Select)
        {
            case KPROPORTIONNEL:
                
                if(Flag_Pec12_Ok_Gain)
                {    
                    FlagMenuGainPID = 0;
                    if(Pec12IsPlus())
                    {
                        Pec12ClearPlus();
                        if(S_GainPID->Kp >= 500)
                        {
                            S_GainPID->Kp = 0;
                        }
                        else
                        {
                            S_GainPID->Kp = S_GainPID->Kp + 5;
                        }                    
                    }                
                    else if(Pec12IsMinus())
                    {          
                        Pec12ClearMinus();
                        if(S_GainPID->Kp <= 0)
                        {
                            S_GainPID->Kp = 500;
                        }
                        else
                        {
                            S_GainPID->Kp = S_GainPID->Kp - 5;
                        }                    
                    }
                    if(Pec12IsOK())
                    {
                        Pec12ClearOK();
                        Flag_Pec12_Ok_Gain = 0;  
                    }
                }    
                break;
               
            case KINTEGRAL:               
             
                if(Flag_Pec12_Ok_Gain)
                {    
                    FlagMenuGainPID = 0;
                    if(Pec12IsPlus())
                    {
                        if(S_GainPID->Ki >= 500)
                        {
                            S_GainPID->Ki = 0;
                        }
                        else
                        {
                            S_GainPID->Ki = S_GainPID->Ki + 5;
                        }
                        Pec12ClearPlus();
                    }

                    else if(Pec12IsMinus())
                    {          
                        if(S_GainPID->Ki <= 0)
                        {
                            S_GainPID->Ki = 500;
                        }
                        else
                        {
                            S_GainPID->Ki = S_GainPID->Ki - 5;
                        }
                        Pec12ClearMinus();
                    }
                    if(Pec12IsOK())
                    {
                        Pec12ClearOK();
                        Flag_Pec12_Ok_Gain = 0;  
                    }
                }    
                break;
               
            case KDERIVE:                
                
                if(Flag_Pec12_Ok_Gain)
                {      
                    FlagMenuGainPID = 0;
                    if(Pec12IsPlus())
                    {
                        if(S_GainPID->Kd >= 1.5)
                        {
                            S_GainPID->Kd = 0;
                        }
                        else
                        {
                            S_GainPID->Kd = S_GainPID->Kd + 0.05;
                        }
                        Pec12ClearPlus();
                    }                
                    else if(Pec12IsMinus())
                    {          
                        if(S_GainPID->Kd <= 0)
                        {
                            S_GainPID->Kd = 1.5;
                        }
                        else
                        {
                            S_GainPID->Kd = S_GainPID->Kd - 0.05;
                        }
                        Pec12ClearMinus();
                    }
                    if(Pec12IsOK())
                    {
                        Pec12ClearOK();
                        Flag_Pec12_Ok_Gain = 0;  
                    }
                }
                break;            
                             
            default :           
                break;
        }
    }       
}

const S_ParamGainPID* ValGainPID()
{     
    return (&S_GainPID);
}

const uint8_t ValPWM()
{     
    return (PWM_Fan);
}

const S_ParamConsigne* ValConsigne()
{     
    return (&Consigne);
}
/* *****************************************************************************
 End of File */
