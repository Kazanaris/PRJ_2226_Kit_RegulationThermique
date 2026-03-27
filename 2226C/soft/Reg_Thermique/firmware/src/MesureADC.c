/* ************************************************************************** */
/** Descriptive File Name

  @Company
    ETML-ES

  @File Name
    MesureADC.c

  @Description
 *  Gestion de l'ADC
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "MesureADC.h"
#include <stdint.h>
#include "system_config.h"
#include "framework/driver/adc/drv_adc_static.h"

#define configscan    0x03C1       //masque des addresses des AN à lire (AN0,AN6, AN7, AN8, AN9) 
#define TEMP_MAX      150
#define VAL_UTEMP_MAX    1.5
#define VAL_AD_MAX    1023

//static S_ADCResults Raw;

void ADC_Init(void)
{
    // Configure l'ADC
    PLIB_ADC_InputScanMaskAdd(ADC_ID_1, configscan) ;   // liste des AN à scanner
    PLIB_ADC_ResultFormatSelect(ADC_ID_1, ADC_RESULT_FORMAT_INTEGER_16BIT);
    PLIB_ADC_ResultBufferModeSelect(ADC_ID_1, ADC_BUFFER_MODE_TWO_8WORD_BUFFERS);
    PLIB_ADC_SamplingModeSelect(ADC_ID_1, ADC_SAMPLING_MODE_MUXA);

    PLIB_ADC_ConversionTriggerSourceSelect(ADC_ID_1, ADC_CONVERSION_TRIGGER_INTERNAL_COUNT);
    PLIB_ADC_VoltageReferenceSelect(ADC_ID_1, ADC_REFERENCE_VDD_TO_AVSS );
    PLIB_ADC_SampleAcquisitionTimeSet(ADC_ID_1, 0x1F);
    PLIB_ADC_ConversionClockSet(ADC_ID_1, SYS_CLK_FREQ, 32);

    // Rem CHR le nb d'échantillon par interruption doit correspondre au nb d'entrées
    // de la liste de scan
    PLIB_ADC_SamplesPerInterruptSelect(ADC_ID_1, ADC_5SAMPLES_PER_INTERRUPT);
    PLIB_ADC_MuxAInputScanEnable(ADC_ID_1);

    // Enable the ADC module
    PLIB_ADC_Enable(ADC_ID_1);
}

void ADC_Read(S_ValMesure *ValReadAD)
{   
    ADC_RESULT_BUF_STATUS BufStatus;

    // Auto start sampling
    // PLIB_ADC_SampleAutoStartEnable(ADC_ID_1);

    // Attente fin de conversion
    //    while (!PLIB_ADC_ConversionHasCompleted(ADC_ID_1))

    // Stop sample/convert
    PLIB_ADC_SampleAutoStartDisable(ADC_ID_1);

    // traitement avec buffer alterné
    BufStatus = PLIB_ADC_ResultBufferStatusGet(ADC_ID_1);
    if (BufStatus == ADC_FILLING_BUF_0TO7) 
    {
        ValReadAD->Ref3V        = PLIB_ADC_ResultGetByIndex(ADC_ID_1, 8);
        ValReadAD->Mes_I        = PLIB_ADC_ResultGetByIndex(ADC_ID_1, 9);
        ValReadAD->Mes_Temp     = PLIB_ADC_ResultGetByIndex(ADC_ID_1, 10);
        ValReadAD->Mes_PID_out  = PLIB_ADC_ResultGetByIndex(ADC_ID_1, 11);
        ValReadAD->Consigne_EXT = PLIB_ADC_ResultGetByIndex(ADC_ID_1, 12);     
    } 
    else
    {
        ValReadAD->Ref3V        = PLIB_ADC_ResultGetByIndex(ADC_ID_1, 0);
        ValReadAD->Mes_I        = PLIB_ADC_ResultGetByIndex(ADC_ID_1, 1);
        ValReadAD->Mes_Temp     = PLIB_ADC_ResultGetByIndex(ADC_ID_1, 2);
        ValReadAD->Mes_PID_out  = PLIB_ADC_ResultGetByIndex(ADC_ID_1, 3);
        ValReadAD->Consigne_EXT = PLIB_ADC_ResultGetByIndex(ADC_ID_1, 4);  
    }
    
    ValReadAD->Ref3V = (ValReadAD->Ref3V / 1023) * 3.3;
    ValReadAD->Mes_Temp = 3 -((ValReadAD->Mes_Temp / 1023) * 3.3);
    ValReadAD->Mes_PID_out = (ValReadAD->Mes_PID_out / 1023) * 3.3;
//    ValReadAD->Mes_I = ((ValReadAD->Mes_I - 515) / 1023) * 3.3;
    ValReadAD->Consigne_EXT = (ValReadAD->Consigne_EXT / 1023) * 3.3;
    
    // Auto start sampling
    PLIB_ADC_SampleAutoStartEnable(ADC_ID_1);
    
}

//uint8_t ConvToDegre(uint16_t ValU)
//{
//    uint8_t Temp = 0;
//    
//    ValAD = VAL_AD_MAX - ValAD;
//    
//    Temp = (ValU * 100);
//    
//    return (Temp);
//}

/* *****************************************************************************
 End of File
 */
