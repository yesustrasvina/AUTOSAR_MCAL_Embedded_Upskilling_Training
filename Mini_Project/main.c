#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Gpt.h"
#include "Osif.h"
#include "SEGGER_RTT.h"

#define BUTTON_PRESSED  0
#define BUTTON_RELEASED 1

#define IDLE            0
#define SINGLE_PRESS    1
#define SINGLE_RELEASE  2
#define DOUBLE_CLICK    3
#define HOLD            4

uint8 btnstate = 0;
uint8 laststate = BUTTON_RELEASED;
uint8 state = IDLE;

void EcuM_Init( void );
void DoubleClick_stMachine( void );

int main( void )
{
    EcuM_Init();
    SEGGER_RTT_Init();

    uint32 Timeout_50ms = OsIf_MicrosToTicks( 50000u, OSIF_COUNTER_SYSTEM );
    uint32 SeedTick = OsIf_GetCounter( OSIF_COUNTER_SYSTEM );
    uint32 ElapsedTime = 0u;

    while(1)
    {
        /* get the elapsed time count from the seed tick value*/
        ElapsedTime += OsIf_GetElapsed( &SeedTick, OSIF_COUNTER_SYSTEM );
        /*query if the elapsed time is already equal or bigger than the timeout*/
        if( ElapsedTime >= Timeout_50ms )
        {
            /*reset the elapsed time */
            ElapsedTime = 0u;
            DoubleClick_stMachine();
        }
    }

    return 0u;
}

void DoubleClick_stMachine( void )
{
    switch( state )
    {
        case IDLE :
            // query for the first time the button is press
            // Read the current button state
            btnstate = Dio_ReadChannel(DioConf_DioChannel_BTN1);

            // Check for a button press event (state change from released to pressed)
            if ( btnstate == BUTTON_PRESSED && laststate == BUTTON_RELEASED)
            {
                state = SINGLE_PRESS;
            }
            laststate = btnstate;
        break;

        case SINGLE_PRESS :
            // query if there is a timeout
            // start the 300ms counter if there is a press
            /*Start the timer and set it to Running state*/
            Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_0, 28125u );
            btnstate = Dio_ReadChannel(DioConf_DioChannel_BTN1);
            if( Gpt_GetTimeRemaining( GptConf_GptChannelConfiguration_GptChannelConfiguration_0 ) == 0u )
            {
                btnstate = Dio_ReadChannel(DioConf_DioChannel_BTN1);
                if(btnstate == BUTTON_PRESSED && laststate == BUTTON_PRESSED)
                {
                    Gpt_StopTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_0 );
                    state = HOLD;
                }
                laststate = btnstate;
            }
            else if(btnstate == BUTTON_RELEASED && laststate == BUTTON_PRESSED)
            {
                Gpt_StopTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_0 );
                state = SINGLE_RELEASE;
            }
            laststate = btnstate;
            // query if there is a release
        break;

        case SINGLE_RELEASE :
            // query if timeout
            Gpt_StartTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_0, 28125u );
            btnstate = Dio_ReadChannel(DioConf_DioChannel_BTN1);
            if(btnstate == BUTTON_PRESSED && laststate == BUTTON_RELEASED)
            {
                Gpt_StopTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_0 );
                state = DOUBLE_CLICK;
            }
            else if( Gpt_GetTimeRemaining( GptConf_GptChannelConfiguration_GptChannelConfiguration_0 ) == 0u && btnstate == BUTTON_RELEASED)
            {
                // if timeout is asingle click
                Gpt_StopTimer( GptConf_GptChannelConfiguration_GptChannelConfiguration_0 );
                Dio_FlipChannel(DioConf_DioChannel_LED_C8); 
                
                laststate = btnstate;
                state = IDLE;
            }
            
        break;

        case DOUBLE_CLICK :
                Dio_FlipChannel(DioConf_DioChannel_LED_C9);
                state = IDLE;
                laststate = btnstate;
        break;

        case HOLD :
            // if state jumps here is a hold click
            
            // wait until botton is released and go back to IDLE
            btnstate = Dio_ReadChannel(DioConf_DioChannel_BTN1);
            if(btnstate == BUTTON_RELEASED && laststate == BUTTON_PRESSED)
            { 
                Dio_FlipChannel(DioConf_DioChannel_LED_C10);
                state = IDLE;
            }
            laststate = btnstate;
        break;

        default :
          // if jump here is a error
          state = IDLE;
        break;
    }
}

void EcuM_Init( void )
{
    Mcu_Init( &Mcu_Config );
    Mcu_InitClock( McuClockSettingConfig_0 );
    Mcu_SetMode( McuModeSettingConf_0 );
    Port_Init( &Port_Config );
    OsIf_Init( NULL_PTR );
    Gpt_Init( &Gpt_Config );
}