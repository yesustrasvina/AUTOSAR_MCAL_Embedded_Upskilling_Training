#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
void EcuM_Init( void );
int main( void )
{
    EcuM_Init();
    while( 1u )
    {
    }
    return 0u;
}
void EcuM_Init( void )
{
    /*Init Mcu module, including internal PLL, reference to Mcu Config structure can 
    be found at Mcu_PBcfg.h */
    Mcu_Init( &Mcu_Config );
    Mcu_InitClock( McuClockSettingConfig_0 );
    Mcu_SetMode( McuModeSettingConf_0 );
    /*Apply all the Pin Port microcontroller configuration, for this case
    Port Pin 110  (D14) is configured as clock output*/
    Port_Init( &Port_Config );
}