#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Gpt.h"
#include "Platform.h"

void EcuM_Init( void );

/*this function is gonna be called on ISR from FTM0_CH0_CH1, it is basically a callback
called by FTM_0_CH_0_CH_1_ISR library function*/
void Gpt_TimeoutCallback_0( void )
{
    /*here, we just toggle led connected to D0*/
    Dio_FlipChannel( DioConf_DioChannel_RGB_Blue );
}

/*this function is gonna be called on ISR from FTM1_CH0_CH1, it is basically a callback
called by FTM_1_CH_0_CH_1_ISR library function*/
void Gpt_TimeoutCallback_1( void )
{
    /*here, we just toggle led connected to D15*/
    Dio_FlipChannel( DioConf_DioChannel_RGB_Red );
}

/*this function is gonna be called on ISR from FTM2_CH0_CH1, it is basically a callback
called by FTM_2_CH_0_CH_1_ISR library function*/
void Gpt_TimeoutCallback_2( void )
{
    /*here, we just toggle led connected to D16*/
    Dio_FlipChannel( DioConf_DioChannel_RGB_Green );
}

int main( void )
{
    EcuM_Init();
    /*Start the timers and set it to Running state with a timeout of 100ms*/
    Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_0, 9375u );
    /*Start the timers and set it to Running state with a timeout of 500ms*/
    Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_1, 31250u );
    /*Start the timers and set it to Running state with a timeout of 1 second*/
    Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_2, 62500u );
    
    /*Enable notifications, Gpt_TimeoutCallbacks will be called on each timeout*/
    Gpt_EnableNotification( GptConf_GptChannelConfiguration_GptChannelConfiguration_0 );
    Gpt_EnableNotification( GptConf_GptChannelConfiguration_GptChannelConfiguration_1 );
    Gpt_EnableNotification( GptConf_GptChannelConfiguration_GptChannelConfiguration_2 );
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
    only Port Pin 96 (D0), 111 (D15) 112 (D16) and is configured as output*/
    Port_Init( &Port_Config );
    Gpt_Init( &Gpt_Config );
}