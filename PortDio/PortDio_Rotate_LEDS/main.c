#include "Mcu.h"
#include "Port.h"
#include "Dio.h"

uint8 state = 0;
uint8 laststate = 0;
uint8 mode = 2;

void EcuM_Init( void );
int main( void )
{
    EcuM_Init();
    while(1)
    {
        state =  (Dio_ReadChannel( DioConf_DioChannel_A12_BUTTON ) == STD_LOW );
        if(state == 1 && laststate == 0)
        {
            mode = (mode + 1) % 2;
        }
        laststate = state;

        /*dummy delay to avoid polling the btn to often*/
        for( uint32 i = 0u ; i < 10000u ; i++ );

        if (mode == 0)
        {
        for( uint8 i = 0u ; i < 8u ; i++ )
        {
            Dio_WriteChannelGroup( DioConf_DioChannelGroup_PORTC_LEDS, 0x00u );
            Dio_WriteChannelGroup( DioConf_DioChannelGroup_PORTC_LEDS, ( 1u << i ) );
            /*dummy delay*/
             for( uint32 i = 0u ; i < 500000u ; i++ );
        }
        }
        if (mode == 1)
        {
        for (uint8 i = 7u; i < 8u; i--)
        {
            Dio_WriteChannelGroup( DioConf_DioChannelGroup_PORTC_LEDS, 0x00u );
            Dio_WriteChannelGroup( DioConf_DioChannelGroup_PORTC_LEDS, ( 1u << i ) );
            /*dummy delay*/
            for( uint32 i = 0u ; i < 500000u ; i++ );
        }
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
    /*Init ports from C8 to C15*/
    Port_Init( &Port_Config );
}