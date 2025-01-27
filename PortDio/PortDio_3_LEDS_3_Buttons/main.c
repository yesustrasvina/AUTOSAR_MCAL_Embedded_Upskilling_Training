#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
void EcuM_Init( void );
uint8_t speed = 0;

int main( void )
{
    EcuM_Init();
    while(1)
    {
        /*Inquire the pin state where the button is connected*/
        if( Dio_ReadChannel( DioConf_DioChannel_E12_BTN0 ) == STD_LOW )
        {
            speed = 1;
        }
        else if( Dio_ReadChannel( DioConf_DioChannel_D17_BTN1 ) == STD_LOW )
        {
            speed = 2;
        }
        else if( Dio_ReadChannel( DioConf_DioChannel_A12_BTN2 ) == STD_LOW )
        {
            speed = 3;
        }
        /*dummy delay to avoid polling the btn to often*/
        for( uint32 i = 0u ; i < 1000000u ; i++ );

        if(speed == 1)
        {
            Dio_FlipChannel( DioConf_DioChannel_C8_LED );
            for( uint32 i = 0u ; i < 2000u ; i++ );
        }
        if(speed == 2)
        {
            Dio_FlipChannel( DioConf_DioChannel_C8_LED );
            for( uint32 i = 0u ; i < 300000u ; i++ );
        }
        if(speed == 3)
        {
            Dio_FlipChannel( DioConf_DioChannel_C8_LED );
            for( uint32 i = 0u ; i < 40000000u ; i++ );            
        }
    }
    return 0;
}
void EcuM_Init( void )
{
    Mcu_Init( &Mcu_Config );
    /* Initialize the clock tree with no PLL active*/
    Mcu_InitClock( McuClockSettingConfig_0 );
    Mcu_SetMode( McuModeSettingConf_0 );
    /*Init ports A12, D0, D15, D16, D17, E12*/
    Port_Init( &Port_Config );
}