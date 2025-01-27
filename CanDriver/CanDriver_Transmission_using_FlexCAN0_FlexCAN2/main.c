#include "Mcu.h"
#include "OsIf.h"
#include "Platform.h"
#include "Port.h"
#include "Can_43_FLEXCAN.h"

/*Global data.*/
boolean CanIf_bTxFlag;   /*Flag for transmission.*/

/*Functions.*/
/*This function is a delay in ms using the osif timer.
ms --> Delay in ms.*/
void Delay( uint32 ms )
{
    uint32 Timeout = OsIf_MicrosToTicks( ms * 1000u, OSIF_COUNTER_SYSTEM );
    uint32 SeedTick = OsIf_GetCounter( OSIF_COUNTER_SYSTEM );
    uint32 ElapsedTime = 0u;
    do 
    {
        ElapsedTime += OsIf_GetElapsed( &SeedTick, OSIF_COUNTER_SYSTEM );
    } while( ElapsedTime < Timeout );
}

/*This function initialices the microcontroller and the peripherals*/
void EcuM_Init( void ) 
{   
    /*Init Mcu module, including internal PLL, reference to Mcu Config structure can 
    be found at Mcu_PBcfg.h and PLL defines at Mcu_Cfg.h*/
    Mcu_Init( &Mcu_Config );
    Mcu_InitClock( McuClockSettingConfig_0 );
    Mcu_SetMode( McuModeSettingConf_0 );
    OsIf_Init( NULL_PTR );  /*Init Osif timer.*/
    Platform_Init( NULL_PTR );  /*Init platform driver and configuration.*/
    Port_Init( &Port_Config );  /*Init port driver and configuration.*/
    Can_43_FLEXCAN_Init( &Can_43_FLEXCAN_Config );  /*Init FlexCan driver*/
}

/*CanIf callback function implementation, just to avoid compiler errors 
in reality this function is already implemented in CanIf layer*/
void CanIf_ControllerBusOff( uint8 ControllerId ) 
{
    (void)ControllerId;
}

/*CanIf callback function implementation, just to avoid compiler errors 
in reality this function is already implemented in CanIf layer.*/
void CanIf_ControllerModeIndication( uint8 ControllerId, Can_ControllerStateType ControllerMode ) 
{
    (void)ControllerId;
    (void)ControllerMode;
}

/*CanIf callback function for the complete transmit of a message, 
In reality this function is already implemented in CanIf layer. 
CanTxPduId --> Id of the message (PDU) transmited.*/
void CanIf_TxConfirmation( PduIdType CanTxPduId ) 
{
    /*local data.*/
    static uint8 count = 0;
    (void)CanTxPduId;
    count++;
    if ( count == 2 ) 
    { /*All messages were transmitted.*/
        CanIf_bTxFlag = TRUE;
        count = 0; 
    }
}

/*CanIf callback function for the reception of a message of interest.
In reality this function is already implemented in CanIf layer. 
Mailbox --> Pointer to mailbox.
PduInfoPtr --> Pointer to message received (PDU).*/
void CanIf_RxIndication( const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr ) 
{
    (void)Mailbox;
    (void)PduInfoPtr;
}

/*This is the main function of the project. This example uses FlexCan0 and FlexCan2, 
each Can controller transmits a single 4 byte data message every 5s.*/
int main( void ) 
{
    /*local data.*/
    /*Transmit message 0 for Can 0 controller.*/
    uint8 Message0_Can0_SDU[4] = { 0x01, 0x02, 0x03, 0x04 }; /*Data payload for message.*/
    Can_PduType Message0_Can0 = {
        .id  = 0x100,
        .length = 4,
        .sdu = Message0_Can0_SDU,
        .swPduHandle = 0
    };
    /*Transmit message 0 for Can 2 controller.*/
    uint8 Message0_Can2_SDU[4] = { 0x10, 0x20, 0x30, 0x40 }; /*Data payload for message.*/
    Can_PduType Message0_Can2 = {
        .id  = 0x200,
        .length = 4,
        .sdu = Message0_Can2_SDU,
        .swPduHandle = 0
    };
    EcuM_Init();    /*MCU configuration.*/
    Can_43_FLEXCAN_SetControllerMode( CanController_0, CAN_CS_STARTED );   /*Can 0 controller active in Can Bus.*/
    Can_43_FLEXCAN_SetControllerMode( CanController_1, CAN_CS_STARTED );   /*Can 2 controller active in Can Bus.*/
    while( 1u ) 
    {
        /*Transmit messages every 5s.*/
        Can_43_FLEXCAN_Write( CanHardwareObject_0, &Message0_Can0 );  /*Writing in Can 0 message buffer 0.*/
        Can_43_FLEXCAN_Write( CanHardwareObject_1, &Message0_Can2 );  /*Writing in Can 2 message buffer 0.*/
        while( CanIf_bTxFlag == FALSE ); /*Waiting until messages are transmitted.*/
        CanIf_bTxFlag = FALSE;  /*Clearing transmit flag.*/
        /*Changing SDUs.*/
        Message0_Can0_SDU[0]++;
        Message0_Can0_SDU[3]++;
        Message0_Can2_SDU[0]++;
        Message0_Can2_SDU[3]++;
        Delay( 5000 );  /*Waiting 5s for next transmission.*/
    }
    return 0u;
}