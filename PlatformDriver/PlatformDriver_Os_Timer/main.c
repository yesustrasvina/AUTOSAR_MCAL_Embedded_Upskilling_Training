#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Osif.h"
void EcuM_Init( void );
int main( void )
{
    EcuM_Init();
    /*get the number of ticks corresponding to 500ms, the resolution will depend
    on the frequency feediong the systick timer in this case with a freq of
    48MHz we could have up to 20ns, but the fucntion only accpet microseconds*/
    uint32 Timeout_500ms = OsIf_MicrosToTicks( 500000u, OSIF_COUNTER_SYSTEM );
    /*get the Systic Timer count for the first time*/
    uint32 SeedTick = OsIf_GetCounter( OSIF_COUNTER_SYSTEM );
    /*We need to count the elapsed time from zero*/
    uint32 ElapsedTime = 0u;
    while( 1u )
    {
        /* get the elapsed time count from the seed tick value*/
        ElapsedTime += OsIf_GetElapsed( &SeedTick, OSIF_COUNTER_SYSTEM );
        /*query if the elapsed time is already equal or bigger than the timeout*/
        if( ElapsedTime >= Timeout_500ms )
        {
            /*reset the elapsed time */
            ElapsedTime = 0u;
            /*toggle led*/
            Dio_FlipChannel( DioConf_DioChannel_DioChannel_0 );
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
    /*Init the internal tick reference Systick Timer*/
    OsIf_Init( NULL_PTR );
    /*Apply all the Pin Port microcontroller configuration, for this case
    only Port Pin 96  (D0) is configured as output*/
    Port_Init( &Port_Config );
}