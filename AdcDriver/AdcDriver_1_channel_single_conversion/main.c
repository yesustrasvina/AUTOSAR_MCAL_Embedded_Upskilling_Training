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

int main( void )
{
    Adc_CalibrationStatusType CalibStatus;
    Adc_ValueGroupType    AdcReadGroupBuffer[1];
    Adc_ValueGroupType    ResultBuffer[1];
    EcuM_Init();
    /*intiliaze RTT library*/
    SEGGER_RTT_Init();
    /*calibrate ADC module*/
    Adc_Calibrate( AdcHwUnit_0, &CalibStatus );
    /*Set the memeory buffer to store convertions*/
    Adc_SetupResultBuffer(AdcGroup_0, ResultBuffer);
    while( 1u )
    {
        /*Software trigger convertion*/
        Adc_StartGroupConversion( AdcGroup_0 );
        /*wait until the convertion is done*/
        while( Adc_GetGroupStatus( AdcGroup_0 ) == ADC_BUSY );
        /*Read ready convertion*/
        Adc_ReadGroup( AdcGroup_0, AdcReadGroupBuffer );
        /*display value*/
        SEGGER_RTT_printf( 0, "Adc Channel value: %d\n", AdcReadGroupBuffer[0] );
        Delay( 2000u );
    }
    return 0u;
}

void EcuM_Init( void )
{
    Mcu_Init( &Mcu_Config );
    /* Initialize the clock tree with no PLL active*/
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