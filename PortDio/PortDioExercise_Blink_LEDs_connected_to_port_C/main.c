/**
 * @file main.c
 * @brief This file contains the main function of the project
 * @author Modular-MX
 * 
 * This file contains the main function of the project, it is the entry point of the program
 * it contains a simple program that toggles a pin of the microcontroller
*/
#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Dio_Cfg.h"

void EcuM_Init( void );

/**
 * @brief This is the main function of the project
 * 
 * This is the main function of the project, it is the entry point of the program
 * 
 * @return Always zero
*/
int main( void )
{
    EcuM_Init();

    while( 1u )
    {
        Dio_FlipChannel( DioConf_DioChannel_C8_LED );
        Dio_FlipChannel( DioConf_DioChannel_C9_LED );
        Dio_FlipChannel( DioConf_DioChannel_C10_LED );
        Dio_FlipChannel( DioConf_DioChannel_C11_LED );
        Dio_FlipChannel( DioConf_DioChannel_C12_LED );
        Dio_FlipChannel( DioConf_DioChannel_C13_LED );
        Dio_FlipChannel( DioConf_DioChannel_C14_LED );
        Dio_FlipChannel( DioConf_DioChannel_C15_LED );
        /*dummy delay*/
        for( uint32 i = 0u ; i < 1000000u ; i++ );
    }

    return 0u;
}

/**
 * @brief This function initialize the microcontroller and the peripherals
 * 
 * it is just a temporary function, in the future this function will be replaced when the EcuM module 
 * is configured and implemented
*/
void EcuM_Init( void )
{
    /*Init Mcu module, including internal PLL, reference to Mcu Config structure can 
    be found at Mcu_PBcfg.h and PLL defines at Mcu_Cfg.h*/
    Mcu_Init( &Mcu_Config );
    Mcu_InitClock( McuClockSettingConfig_0 );
    Mcu_SetMode( McuModeSettingConf_0 );
    /*Apply all the Pin Port microcontroller configuration, for this case
    C8 to C15 is configured as output*/
    Port_Init( &Port_Config );
}
