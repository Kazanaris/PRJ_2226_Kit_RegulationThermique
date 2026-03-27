/* ************************************************************************** */
/** Descriptive File Name

  @Company
 ETML-ES

  @File Name
    Display.c

  @Summary
    Brief description of the file.

  @Description
    Affichage du menu
 */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include "system_config.h"
#include "Mc32Delays.h"
#include "app.h"
#include "GestMenu.h"
#include "Mc32DriverLcd.h"
#include "MesureADC.h"
#include "Display.h"

const char *AffichageFormes[4] = {"Sinus", "Triangle", "DentDeScie", "Carre"};

/*--------------------------------------------------------*/
void Display_Init(void)
{
    //Initialise l'écran LCD en mode 8bits//          
    lcd_init();            
    //Allume le backlight//           
    lcd_bl_on();
    //Affichage//
    lcd_gotoxy(2,1);   
    printf_lcd("2226_RegThermique");
    //Ligne 2
    lcd_gotoxy(2,2);   
    printf_lcd("Gaja Subra");
    //Ligne 3
    lcd_gotoxy(2,3);
    printf_lcd("Initialisation...");
}

/*-------------------------Affichage-Menu-Général------------------------------*/
void Display_Gen(uint8_t PointerG, const char* SrcCons, bool Flag_Pec12_Ok, bool FlagMenuGen )
{
    if(FlagMenuGen == 1)
    {
        static uint8_t PointerGold = 0;

        if(PointerG != PointerGold)
        {
           lcd_gotoxy(1,PointerGold);
           printf_lcd(" ");
        }

        lcd_gotoxy(1,PointerG);

        if(Flag_Pec12_Ok)
        {
            printf_lcd("?");
        }
        else
        {
            printf_lcd(">");
        }
        
        PointerGold = PointerG;
    }
    
    lcd_gotoxy(2,1);
    printf_lcd("Src consigne = %s", SrcCons);
    lcd_gotoxy(2,2);
    printf_lcd("Regl.consigne ->");    
    lcd_gotoxy(2,3);
    printf_lcd("Regl.gain PID -> "); 
    lcd_gotoxy(2,4);
    printf_lcd("Mesures ->");
}

/*-------------------------Affichage-Menu-Consigne------------------------------*/
void DisplayConsigne(uint8_t PointerC, const S_ParamConsigne *Consigne, bool Flag_Pec12_Ok_1/*, bool FlagMenuConsigne*/)
{
    static uint8_t PointerCold = 1;

    if(PointerC != PointerCold)
    {
       lcd_gotoxy(1,PointerCold);
       printf_lcd(" ");
    }

    lcd_gotoxy(1,PointerC);

    if(Flag_Pec12_Ok_1)
    {
        printf_lcd("?");
    }
    else
    {
        printf_lcd(">");
    }
    PointerCold = PointerC;

    lcd_gotoxy(2,1);   
    printf_lcd("Forme = %010s", AffichageFormes[Consigne->Forme]);
    lcd_gotoxy(2,2);   
    printf_lcd("Frequence = %04d", Consigne->Frequence);  
    lcd_gotoxy(2,3);
    printf_lcd("Amplitude = %04d", Consigne->Amplitude);
    lcd_gotoxy(2,4);
    printf_lcd("Offset = %02d", Consigne->Offset);  
}

/*-------------------------Affichage-Menu-GainPID------------------------------*/
void DisplayGainPID(uint8_t PointerP, const S_ParamGainPID *GainPID, bool Flag_Pec12_Ok_2/*, bool FlagMenuGainPID*/)
{
    static uint8_t PointerPold = 1;

    if(PointerP != PointerPold)
    {
       lcd_gotoxy(1,PointerPold);
       printf_lcd(" ");
    }

    lcd_gotoxy(1,PointerP);

    if(Flag_Pec12_Ok_2)
    {
        printf_lcd("?");
    }
    else
    {
        printf_lcd(">");
    }
    PointerPold = PointerP;
    
    lcd_gotoxy(2,1);   
    printf_lcd("Kp = %05.1f", GainPID->Kp);
    lcd_gotoxy(2,2);   
    printf_lcd("Ki = %05.1f", GainPID->Ki);  
    lcd_gotoxy(2,3);
    printf_lcd("Kd = %05.1f", GainPID->Kd);
}

/*-------------------------Affichage-Mesures------------------------------*/
void Display_Mesure(const S_ValMesure* ValAD, bool FlagMenuData)
{       
    S_Affichage Affichage;
    
    if(FlagMenuData == 1)
    {
        lcd_gotoxy(2,1);
        printf_lcd("Consigne= %3d" , Affichage.Consigne);
        lcd_gotoxy(2,2);   
        printf_lcd("Erreur= %3d" , Affichage.Erreur);
        lcd_gotoxy(2,3);
        printf_lcd("Mes.PID_out=%1.3fV", ValAD->Mes_PID_out);
        lcd_gotoxy(2,4);
        printf_lcd("Mes.Temp=%1.2fV" ,ValAD->Mes_Temp);
    }
}
/* *****************************************************************************
 End of File
 */
