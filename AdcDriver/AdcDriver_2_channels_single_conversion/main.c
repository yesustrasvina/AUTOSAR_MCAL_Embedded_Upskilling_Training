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
    Adc_ValueGroupType    AdcReadGroupBuffer[2];
    Adc_ValueGroupType    ResultBuffer[2];
    EcuM_Init();
    /*intiliaze RTT library*/
    SEGGER_RTT_Init();
    /*by default ADC0-CH8 is not connected to B13, but with this functions
    it will, this is called Interleave, read RM page 1194*/
    Port_Ci_Port_Ip_SetMuxModeSel( IP_PORTB, 13, PORT_MUX_ADC_INTERLEAVE );
    /*calibrate ADC module*/
    Adc_Calibrate( AdcHwUnit_0, &CalibStatus );
    /*Set the memeory buffer to store convertions*/
    Adc_SetupResultBuffer( AdcGroup_0, ResultBuffer );

    while( 1u )
    {
        Adc_StartGroupConversion( AdcGroup_0 );
        /*wait until the convertion is done*/
        while( Adc_GetGroupStatus( AdcGroup_0 ) == ADC_BUSY );
        Adc_ReadGroup( AdcGroup_0, AdcReadGroupBuffer );
        /*display value*/
        SEGGER_RTT_printf( 0, "Adc1 value: %d, Adc2 value: %d\n", 
            AdcReadGroupBuffer[AdcChannel_0], AdcReadGroupBuffer[AdcChannel_1] );
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
    /*Apply all the Pin Port microcontroller configuration, for this case
    only Port Pin 96  (D0) is configured as output*/
    Port_Init( &Port_Config );
    /*init the FlexCAN0 with the paramters set in Tresos in loop back mode*/
    Adc_Init( &Adc_Config );
}