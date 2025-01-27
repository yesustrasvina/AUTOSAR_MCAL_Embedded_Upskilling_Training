#include "Mcu.h"
#include "Port.h"
#include "Platform.h"
#include "Osif.h"
#include "Can_43_FLEXCAN.h"
#include "CanIf.h"

/*flags to indicate Transmition*/
boolean CanIf_bTxFlag = FALSE;

/*message to Tx and Rx*/
uint8 Can_au8Sdu8bytes[8U] = {0x05U, 0x96U, 0xE7U, 0x54U, 0x6DU, 0x58U, 0x00U, 0x6FU};

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

/*Callback function to indicate that the message was transmitted. The reference
to function shall be defined in file Autosar/CanIf/CanIf_Cdd.h, such file
must be created manualy*/
void CDD_UserTxConfirmation( PduIdType TxPduId, Std_ReturnType result )
{
    (void)TxPduId;
    if( result == E_OK )
    {
        CanIf_bTxFlag = TRUE;
    }
}

void EcuM_Init( void );

int main( void )
{
    PduInfoType PduInfo;
    EcuM_Init();
    /*Start the CAN controller and make it active in the CAN bus network*/
    Can_43_FLEXCAN_SetControllerMode( CanController_0, CAN_CS_STARTED );
    /*set the information to transmit*/
    PduInfo.SduDataPtr = Can_au8Sdu8bytes;
    PduInfo.SduLength = 8u;
    PduInfo.MetaDataPtr = NULL_PTR;
    while( 1u )
    {
        /*set the FlexCAN peripheral to transmit the message, the message will be
        transmitted by the CAN interrupt, this function will call the low level
        Can_43_FLEXCAN_Write with the low level data according de PDU configured*/
        CanIf_Transmit( CanIfTxPduCfg_0, &PduInfo );
        /*wait until the CAN interrupt transmit message, waiting is not the
        suitable way, but good enough for ilustration purposes, flag is 
        updated by the callback function CanIf_TxConfirmation*/
        while( CanIf_bTxFlag == FALSE );
        /*Clear the Tx flag*/
        CanIf_bTxFlag = FALSE;
        /*increase some values jus for ilustration purpose*/
        Can_au8Sdu8bytes[0]++;
        Can_au8Sdu8bytes[7]++;
        Delay( 5000u );
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
    /*enable and setup interrupts in use by the Can Driver*/
    Platform_Init( NULL_PTR );
    /*Apply all the Pin Port microcontroller configuration, for this case
    only Port Pin 96  (D0) is configured as output*/
    Port_Init( &Port_Config );
    /*init the FlexCAN0 with the paramters set in Tresos in loop back mode*/
    Can_43_FLEXCAN_Init( &Can_43_FLEXCAN_Config );
    CanIf_Init( &CanIf_Config );
}