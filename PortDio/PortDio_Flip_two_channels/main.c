#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
void EcuM_Init( void );
int main( void )
{
    EcuM_Init();
    while(1)
    {
        Dio_WriteChannelGroup( DioConf_DioChannelGroup_PORTD_LEDS, 0x0Fu );
        /*dummy delay*/
        for( uint32 i = 0u ; i < 500000u ; i++ );
        Dio_WriteChannelGroup( DioConf_DioChannelGroup_PORTD_LEDS, 0x00u );
        /*dummy delay*/
        for( uint32 i = 0u ; i < 500000u ; i++ );
    }
    return 0;
}
void EcuM_Init( void )
{
    Mcu_Init( &Mcu_Config );
    /* Initialize the clock tree with no PLL active*/
    Mcu_InitClock( McuClockSettingConfig_0 );
    Mcu_SetMode( McuModeSettingConf_0 );
    /*Init ports from C8 to C11*/
    Port_Init( &Port_Config );
}