#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Gpt.h"
void EcuM_Init( void );
int main( void )
{
    EcuM_Init();
    /*Start the timer and set it to Running state*/
    Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_0, 37500u );
    while( 1u )
    {
        if( Gpt_GetTimeRemaining( GptConf_GptChannelConfiguration_GptChannelConfiguration_0 ) == 0u )
        {
            /*if we are not using notifications it is neceseary to change the channel status from running
            manually, we can use the Stop function for that purpose, otherwise the Start function will 
            never reload the timer with a new count again */
            Gpt_StopTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_0 );
            Dio_FlipChannel( DioConf_DioChannel_DioChannel_0 );
            /*start the timer again*/
            Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_0, 37500u );
        }
    }
    return 0u;
}
void EcuM_Init( void )
{
    Mcu_Init( &Mcu_Config );
    /* Initialize the clock tree with no PLL active*/
    Mcu_InitClock( McuClockSettingConfig_0 );
    Mcu_SetMode( McuModeSettingConf_0 );
    /*Apply all the Pin Port microcontroller configuration, for this case
    only Port Pin 96  (D0) is configured as output*/
    Port_Init( &Port_Config );
    /*Apply Gpt configuration for FTM0 channel 0*/
    Gpt_Init( &Gpt_Config );
}