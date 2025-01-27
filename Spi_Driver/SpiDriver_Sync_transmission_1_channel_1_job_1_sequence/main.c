#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Platform.h"
#include "Osif.h"
#include "Spi.h"

void EcuM_Init( void );

/*this is dummy delay function prepare just for this example, in a real application 
no delay shall be used*/
void Delay( uint32 ms )
{
    uint32 Timeout = OsIf_MicrosToTicks( ms * 1000u, OSIF_COUNTER_SYSTEM );
    uint32 SeedTick = OsIf_GetCounter( OSIF_COUNTER_SYSTEM );
    uint32 ElapsedTime = 0u;
    do
    {
        ElapsedTime += OsIf_GetElapsed( &SeedTick, OSIF_COUNTER_SYSTEM );
    }while( ElapsedTime < Timeout );
}

int main( void )
{
    static Spi_DataBufferType TxMasterBuffer[10] = {11,12,13,14,15,16,17,18,19,20};
    EcuM_Init();
    /* Copy transmitted data to internal buffer */
    Spi_SetupEB( SpiConf_SpiChannel_SpiChannel_0, TxMasterBuffer, NULL, 10 );
    while( 1u )
    {
        /* This sequence of master transferring 10 frames of 8 bits using synchronous method*/
        Spi_SyncTransmit( SpiConf_SpiSequence_SpiSequence_0 );
        Delay( 10u );
    }
    return 0u;
}

void EcuM_Init( void )
{
    /*Init Mcu module, including internal PLL, reference to Mcu Config structure can 
    be found at Mcu_PBcfg.h and PLL defines at Mcu_Cfg.h*/
    Mcu_Init( &Mcu_Config );
    Mcu_InitClock( McuClockSettingConfig_0 );
    Mcu_SetMode( McuModeSettingConf_0 );
    /*Init the internal tick reference Systick Timer*/
    OsIf_Init( NULL_PTR );
    /*enable and setup interrupts*/
    Platform_Init( NULL_PTR );
    /*Apply all the Pin Port microcontroller configuration, for this case
    only Port Pin 96  (D0) is configured as output*/
    Port_Init( &Port_Config );
    /*init the FlexCAN0 with the paramters set in Tresos in loop back mode*/
    Spi_Init( &Spi_Config );
}