#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Platform.h"
#include "Osif.h"
#include "Spi.h"
#include "SEGGER_RTT.h"

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
    Spi_DataBufferType TxBuffer[4] = { 0x00, 0x01, 0x02, 0x03 };
    Spi_DataBufferType RxBuffer[4];
    uint8 Wren, Cmd;
    uint16 Address;

    EcuM_Init();
    SEGGER_RTT_Init();

    /*Enable writing instructions in the eeprom memories by sending a 0x06
    and send it in the first Job*/
    Wren = 0x06;
    Spi_SetupEB( SpiConf_SpiChannel_SpiChannel_Wren, &Wren, NULL, 1 );

    /*Set up the buffer for the Write command + Memoery Address and four bytes of data
    in the second job*/
    Cmd = 0x02;                 /*WREN Instruction value*/
    Address = 0x00A0;       /*Memory address to write data*/    
    Spi_SetupEB( SpiConf_SpiChannel_SpiChannel_Cmd, &Cmd, NULL, 1 );
    Spi_SetupEB( SpiConf_SpiChannel_SpiChannel_Addr, (Spi_DataBufferType*)&Address, NULL, 1 );
    Spi_SetupEB( SpiConf_SpiChannel_SpiChannel_Data, TxBuffer, NULL, 4 );

    /*Send the data to the eeprom memory, two jobs*/
    Spi_SyncTransmit( SpiConf_SpiSequence_SpiSequence_Write );

    /*Wait for the data to be recorded in memory, it is not the best way to
    do it, so it's just for demonstration purposes*/
    Delay( 5 );

    /*Set up the buffer with the read command + address to read and the buffer to store
    the read data in one job*/
    Cmd = 0x03;                 /*READ Instruction value*/
    Address = 0x00A0;           /*Memory address to read data*/
    TxBuffer[0] = 0x33;
    TxBuffer[3] = 0x33;
    Spi_SetupEB( SpiConf_SpiChannel_SpiChannel_Cmd, &Cmd, NULL, 1 );
    Spi_SetupEB( SpiConf_SpiChannel_SpiChannel_Addr, (Spi_DataBufferType*)&Address, NULL, 1 );
    Spi_SetupEB( SpiConf_SpiChannel_SpiChannel_Data, NULL, RxBuffer, 4 );
    Spi_SyncTransmit( SpiConf_SpiSequence_SpiSequence_Read );

    SEGGER_RTT_printf(0, "Data read from eeprom 1: %x\n", RxBuffer[0] );
    while( 1u )
    {
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
    /*Apply all the Pin Port microcontroller configuration*/
    Port_Init( &Port_Config );
    /*init the FlexCAN0 with the paramters set in Tresos in loop back mode*/
    Spi_Init( &Spi_Config );
}