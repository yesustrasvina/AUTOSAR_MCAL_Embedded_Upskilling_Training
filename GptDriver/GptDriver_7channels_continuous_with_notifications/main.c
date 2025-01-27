#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Gpt.h"
#include "Platform.h"

void EcuM_Init( void );
/*this function is gonna be called on ISR from FTM1_CH0_CH1, it is basically a callback
called by FTM_1_CH_0_CH_1_ISR library function*/
void Gpt_TimeoutCallback_0( void )
{
    /*here, we just toggle led connected to C8*/
    Dio_FlipChannel( DioConf_DioChannel_Led0 );
}
void Gpt_TimeoutCallback_1( void )
{
    /*here, we just toggle led connected to C9*/
    Dio_FlipChannel( DioConf_DioChannel_Led1 );
}
void Gpt_TimeoutCallback_2( void )
{
    /*here, we just toggle led connected to C10*/
    Dio_FlipChannel( DioConf_DioChannel_Led2 );
}
void Gpt_TimeoutCallback_3( void )
{
    /*here, we just toggle led connected to C11*/
    Dio_FlipChannel( DioConf_DioChannel_Led3 );
}
void Gpt_TimeoutCallback_4( void )
{
    /*here, we just toggle led connected to C12*/
    Dio_FlipChannel( DioConf_DioChannel_Led4 );
}
void Gpt_TimeoutCallback_5( void )
{
    /*here, we just toggle led connected to C13*/
    Dio_FlipChannel( DioConf_DioChannel_Led5 );
}
void Gpt_TimeoutCallback_6( void )
{
    /*here, we just toggle led connected to C14*/
    Dio_FlipChannel( DioConf_DioChannel_Led6 );
}
void Gpt_TimeoutCallback_7( void )
{
    /*here, we just toggle led connected to C15*/
    Dio_FlipChannel( DioConf_DioChannel_Led7 );
}
int main( void )
{
    EcuM_Init();
    /*Start the timers and set it to Running state with a timeout of 1.4s*/
    Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_0, 32812u );
    Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_1, 32812u );
    Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_2, 32812u );
    Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_3, 32812u );
    Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_4, 32812u );
    Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_5, 32812u );
    Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_6, 32812u );
    Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_7, 32812u );

    /*Enable notifications, Gpt_TimeoutCallbacks will be called on each timeout*/
    Gpt_EnableNotification( GptConf_GptChannelConfiguration_GptChannelConfiguration_0 );
    Gpt_EnableNotification( GptConf_GptChannelConfiguration_GptChannelConfiguration_1 );
    Gpt_EnableNotification( GptConf_GptChannelConfiguration_GptChannelConfiguration_2 );
    Gpt_EnableNotification( GptConf_GptChannelConfiguration_GptChannelConfiguration_3 );
    Gpt_EnableNotification( GptConf_GptChannelConfiguration_GptChannelConfiguration_4 );
    Gpt_EnableNotification( GptConf_GptChannelConfiguration_GptChannelConfiguration_5 );
    Gpt_EnableNotification( GptConf_GptChannelConfiguration_GptChannelConfiguration_6 );
    Gpt_EnableNotification( GptConf_GptChannelConfiguration_GptChannelConfiguration_7 );
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