#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
void EcuM_Init( void );
int main( void )
{
    EcuM_Init();
    while(1)
    {
        /*Inquire the pin state where the button is connected*/
        if( Dio_ReadChannel( DioConf_DioChannel_D17_SW2_BTN ) == STD_LOW )
        {
            Dio_FlipChannel( DioConf_DioChannel_D16_GREEN_LED );
        }
        /*dummy delay to avoid polling the btn to often*/
         for( uint32 i = 0u ; i < 1000000u ; i++ );
    }
    return 0;
}
void EcuM_Init( void )
{
    Mcu_Init( &Mcu_Config );
    /* Initialize the clock tree with no PLL active*/
    Mcu_InitClock( McuClockSettingConfig_0 );
    Mcu_SetMode( McuModeSettingConf_0 );
    /*Init ports D16 and D17*/
    Port_Init( &Port_Config );
}