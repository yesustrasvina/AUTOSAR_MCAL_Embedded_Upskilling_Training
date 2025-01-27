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
    Spi_DataBufferType TxBuffer1[4];
    Spi_DataBufferType TxBuffer2[4];
    Spi_DataBufferType RxBuffer1[4];
    Spi_DataBufferType RxBuffer2[4];

    EcuM_Init();
    SEGGER_RTT_Init();

    /*Enable writing instructions in the eeprom memories by sending a 0x06*/
    TxBuffer2[0] = TxBuffer1[0] = 0x06;          /*WREN Instruction value*/
    Spi_SetupEB( SpiConf_SpiChannel_SpiChannel_0, TxBuffer1, NULL, 1 );
    Spi_SetupEB( SpiConf_SpiChannel_SpiChannel_1, TxBuffer2, NULL, 1 );
    Spi_SyncTransmit( SpiConf_SpiSequence_SpiSequence_0 );
    /*Send to write the value 0x35 in the address 0 of the memory*/
    TxBuffer2[0] = TxBuffer1[0] = 0x02;                 /*Write instruction */
    TxBuffer2[1] = TxBuffer1[1] = 0x00;                 /*16 bit - address  */
    TxBuffer2[2] = TxBuffer1[2] = 0x00;                 /*16 bit - address  */
    TxBuffer1[3] = 0x38;                                /*Data byte         */
    TxBuffer2[3] = 0x39;                                /*Data byte         */
    Spi_SetupEB( SpiConf_SpiChannel_SpiChannel_0, TxBuffer1, NULL, 4 );
    Spi_SetupEB( SpiConf_SpiChannel_SpiChannel_1, TxBuffer2, NULL, 4 );
    Spi_SyncTransmit( SpiConf_SpiSequence_SpiSequence_0 );

    /*Wait for the data to be recorded in memory, it is not the best way to
    do it, so it's just for demonstration purposes*/
    Delay( 10 );

    /*Read a byte from direccion 0x00 of each eeprom memory, TransmitReceive() Function needs as parameters structure
    to handle SPI , buffer where data to transmit is stored, buffer where data received is stored, total amount
    of bytes to transmit and receive*/
    TxBuffer2[0] = TxBuffer1[0] = 0x03; 
    TxBuffer2[1] = TxBuffer1[1] = 0x00; 
    TxBuffer2[2] = TxBuffer1[2] = 0x00;
    Spi_SetupEB( SpiConf_SpiChannel_SpiChannel_0, TxBuffer1, RxBuffer1, 4 );
    Spi_SetupEB( SpiConf_SpiChannel_SpiChannel_1, TxBuffer2, RxBuffer2, 4 );
    Spi_SyncTransmit( SpiConf_SpiSequence_SpiSequence_0 );
    
    SEGGER_RTT_printf(0, "Data read from eeprom 1: %x\n", RxBuffer1[3] );
    SEGGER_RTT_printf(0, "Data read from eeprom 2: %x\n", RxBuffer2[3] );
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