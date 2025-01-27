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
    be found at Mcu_PBcfg.h and PLL defines at Mcu_Cfg.h*/
    Mcu_Init( &Mcu_Config );
    Mcu_InitClock( McuClockSettingConfig_0 );
    /* Wait until the System PLL is locked */
    while( MCU_PLL_LOCKED != Mcu_GetPllStatus() );
    Mcu_DistributePllClock();
    Mcu_SetMode( McuModeSettingConf_0 );
    /*Apply any port configuration, none for this example*/
    Port_Init( &Port_Config );
}