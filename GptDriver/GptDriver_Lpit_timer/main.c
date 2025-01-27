#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Gpt.h"
#include "Platform.h"

void EcuM_Init( void );

/*this function is gonna be called on ISR from FTM1_CH0_CH1, it is basically a callback
called by LPIT_1_CH_0_CH_1_ISR library function*/
void Gpt_TimeoutCallback_0( void )
{
    /*here, we just toggle led connected to D0*/
    Dio_FlipChannel( DioConf_DioChannel_RGB_BLUE);
}

int main( void )
{
    EcuM_Init();

    /*Start the timers and set it to Running state with a timeout of 300ms*/
    Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_0, 3600000u );

    /*Enable notifications, Gpt_TimeoutCallbacks will be called on each timeout*/
    Gpt_EnableNotification( GptConf_GptChannelConfiguration_GptChannelConfiguration_0 );

    while( 1u )
    {
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
    C8 to C15 is configured as output*/
    Port_Init( &Port_Config );
    Gpt_Init( &Gpt_Config );
}
