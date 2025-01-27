#include "Mcu.h"
#include "Port.h"
#include "Dio.h"

void EcuM_Init( void );
uint8_t speed = 5;
uint8_t state = 0;
uint8_t laststate = 0;

int main( void )
{
    EcuM_Init();
    while(1)
    {
        /*Inquire the pin state where the button is connected*/

        state =  (Dio_ReadChannel( DioConf_DioChannel_D17_BTN1 ) == STD_LOW );
        if(state == 1 && laststate == 0)
        {
            speed = speed + 1;
            if (speed > 3)
            speed = 0;
        }
        laststate = state;
        /*dummy delay to avoid polling the btn to often*/
        for( uint32 i = 0u ; i < 10000u ; i++ );

        
        if(speed == 0)
        {
            Dio_FlipChannel( DioConf_DioChannel_C8_LED );
            for( uint32 i = 0u ; i < 70000 ; i++ );
        }
        else if(speed == 1)
        {
            Dio_FlipChannel( DioConf_DioChannel_C8_LED );
            for( uint32 i = 0u ; i < 90000 ; i++ );
        }
        else if(speed == 2)
        {
            Dio_FlipChannel( DioConf_DioChannel_C8_LED );
            for( uint32 i = 0u ; i < 110000 ; i++ );           
        }
        else if(speed == 3)
        {
            Dio_FlipChannel( DioConf_DioChannel_C8_LED );
            for( uint32 i = 0u ; i < 130000 ; i++ );          
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