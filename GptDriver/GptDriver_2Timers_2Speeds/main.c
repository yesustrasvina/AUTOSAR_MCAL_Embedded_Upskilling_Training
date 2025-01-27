#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Gpt.h"
#include "Platform.h"
void EcuM_Init( void );
/*this function is gonna be called on ISR from FTM1_CH0_CH1, it is basically a callback
called by FTM_1_CH_0_CH_1_ISR library function*/
void Gpt_Notification_1( void )
{
    /*here, we just toggle led connected to D0*/
    Dio_FlipChannel( DioConf_DioChannel_DioChannel_0 );
}
/*this function is gonna be called on ISR from FTM2_CH0_CH1, it is basically a callback
called by FTM_2_CH_0_CH_1_ISR library function*/
void Gpt_Notification_2( void )
{
    /*here, we just toggle led connected to D16*/
    Dio_FlipChannel( DioConf_DioChannel_DioChannel_1 );
}
int main( void )
{
    EcuM_Init();
    /*Start the timer and set it to Running state with a timeout of 100ms*/
    Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_0, 9375u );
    /*Enable notifications, Gpt_TimeoutCallback will be called on each timeout*/
    Gpt_EnableNotification( GptConf_GptChannelConfiguration_GptChannelConfiguration_0 );
    /*Start the timer and set it to Running state with a timeout of 100ms*/
    Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_1, 28125u );
    /*Enable notifications, Gpt_TimeoutCallback will be called on each timeout*/
    Gpt_EnableNotification( GptConf_GptChannelConfiguration_GptChannelConfiguration_1 );
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
    only Port Pin 96  (D0) is configured as output*/
    Port_Init( &Port_Config );
    Gpt_Init( &Gpt_Config );
}