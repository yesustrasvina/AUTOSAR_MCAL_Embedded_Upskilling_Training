#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Gpt.h"
#include "Platform.h"

#define BUTTON_PRESSED 1
#define BUTTON_RELEASED 0

uint8 state = BUTTON_RELEASED;
uint8 laststate = BUTTON_RELEASED;
uint8 toggle = 0;

void EcuM_Init( void );

/*this function is gonna be called on ISR from FTM0_CH0_CH1, it is basically a callback
called by FTM_0_CH_0_CH_1_ISR library function*/
void Gpt_TimeoutCallback_0( void )
{
    // Read the current button state
    state = Dio_ReadChannel(DioConf_DioChannel_BTN1);

    // Check for a button press event (state change from released to pressed)
    if (state == BUTTON_PRESSED && laststate == BUTTON_RELEASED)
    {
        toggle = 1; // Set flag to toggle the LED
    }

    // Update the last button state
    laststate = state;
}


int main( void )
{
    EcuM_Init();
    /*Start the timers and set it to Running state with a timeout of 50ms*/
    Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_0, 4687u );
    /*Enable notifications, Gpt_TimeoutCallbacks will be called on each timeout*/
    Gpt_EnableNotification( GptConf_GptChannelConfiguration_GptChannelConfiguration_0 );
    while( 1u )
    {
        if(toggle)
        {
            Dio_FlipChannel(DioConf_DioChannel_RGB_BLUE);
            toggle = 0;
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
    /*enable and setup interrupts*/
    Platform_Init( NULL_PTR );
    /*Apply all the Pin Port microcontroller configuration, for this case
    only Port Pin 96 (D0), 111 (D15) 112 (D16) and is configured as output*/
    Port_Init( &Port_Config );
    Gpt_Init( &Gpt_Config );
}