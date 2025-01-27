#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Platform.h"
#include "Osif.h"
#include "Adc.h"
#include "SEGGER_RTT.h"

void EcuM_Init( void );

/*this is dummy delay function prepare just for this example, in a real application 
no delay shall be used*/
void Delay( uint32 ms )
{
    uint32 Timeout = OsIf_MicrosToTicks( ms * 1000u, OSIF_COUNTER_SYSTEM );
    uint32 SeedTick = OsIf_GetCounter( OSIF_COUNTER_SYSTEM );
    uint32 ElapsedTime = 0u;
    do
    {
        ElapsedTime += OsIf_GetElapsed( &SeedTick, OSIF_COUNTER_SYSTEM );
    }while( ElapsedTime < Timeout );
}

uint8 AdcFlag = FALSE;
Adc_ValueGroupType    AdcReadGroupBuffer[1];
/*This function is called when the ADC conversion is done and the result is ready to be read
name of the function can be anytthing but as per autosar shall be IoHwAb_AdcNotification_<groupID> */
void IoHwAb_AdcNotification_0( void )
{
    /*Read ready convertion*/
    AdcFlag = TRUE;
    Adc_ReadGroup( AdcGroup_0, AdcReadGroupBuffer );    
}

int main( void )
{
    Adc_CalibrationStatusType CalibStatus;
    Adc_ValueGroupType    ResultBuffer[1];
    EcuM_Init();
    /*intiliaze RTT library*/
    SEGGER_RTT_Init();
    /*calibrate ADC module*/
    Adc_Calibrate( AdcHwUnit_0, &CalibStatus );
    /*Set the memeory buffer to store convertions*/
    Adc_SetupResultBuffer( AdcGroup_0, ResultBuffer );
    /*Enable the notification function*/
    Adc_EnableGroupNotification( AdcGroup_0 );
    while( 1u )
    {
        /*Software trigger convertion*/
        Adc_StartGroupConversion( AdcGroup_0 );
        /*wait for the conversion to be done, in a real world application
        we shall not wait at all*/
        while( AdcFlag == FALSE );
        AdcFlag = FALSE;
        /*display value*/
        SEGGER_RTT_printf( 0, "Adc Channel value: %d\n", AdcReadGroupBuffer[0] );
        Delay( 2000u );
    }
    return 0u;
}
void EcuM_Init( void )
{
    /*Init Mcu module, including internal PLL, reference to Mcu Config structure can 
    be found at Mcu_PBcfg.h and PLL defines at Mcu_Cfg.h*/
    Mcu_Init( &Mcu_Config );
    Mcu_InitClock( McuClockSettingConfig_0 );
    Mcu_SetMode( McuModeSettingConf_0 );
    /*Init the internal tick reference Systick Timer*/
    OsIf_Init( NULL_PTR );
    /*enable and setup interrupts*/
    Platform_Init( NULL_PTR );
    /*Apply all the Pin Port microcontroller configuration*/
    Port_Init( &Port_Config );
    /*init the ADC) with the paramters set in Tresos*/
    Adc_Init( &Adc_Config );
}