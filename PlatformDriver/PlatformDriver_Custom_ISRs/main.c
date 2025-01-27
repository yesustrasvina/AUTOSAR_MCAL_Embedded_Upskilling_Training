#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Platform.h"
void EcuM_Init( void );
int main( void )
{
    EcuM_Init();
    /*On this example we decided to enable the interrupt manually and not by the 
    Platfomt_Init function*/
    IntCtrl_Ip_EnableIrq( FTM0_Ch2_Ch3_IRQn );
    while( 1u )
    {
        /*Trigger the interrupt manually*/
        IntCtrl_Ip_SetPending( FTM0_Ch2_Ch3_IRQn );
        /*dummy delay*/
        for( uint32 i = 0u ; i < 500000u ; i++ );
    }
    return 0u;
}
void EcuM_Init( void )
{
    Mcu_Init( &Mcu_Config );
    /* Initialize the clock tree with no PLL active*/
    Mcu_InitClock( McuClockSettingConfig_0 );
    Mcu_SetMode( McuModeSettingConf_0 );
    /*enable and setup interrupts*/
    Platform_Init( NULL_PTR );
    /*Apply all the Pin Port microcontroller configuration, for this case
    only Port Pin 96  (D0) is configured as output*/
    Port_Init( &Port_Config );
}
/*This is the interrupt service routine for the FTM0 Channel 2 and 3, the program
will jump here when the interrupt is manually triggered by the IntCtrl_Ip_SetPending, 
it only toggles the D0 pin */
ISR( FTM0_CH2_CH3_CUSTOM_ISR )
{
    Dio_FlipChannel( DioConf_DioChannel_DioChannel_0 );
}