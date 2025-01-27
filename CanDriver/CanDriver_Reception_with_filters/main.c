#include "Mcu.h"
#include "Port.h"
#include "Platform.h"
#include "Can_43_FLEXCAN.h"

/*message to Tx and Rx*/
uint8 Can_au8Sdu8bytes[8U];

void EcuM_Init( void );

/*CanIf callback function implementation, just to avoid compiler errors
in reality this function is already implemented in CanIf layer*/
void CanIf_ControllerBusOff(uint8 ControllerId)
{
    (void)ControllerId;
}

/*CanIf callback function implementation, just to avoid compiler errors
in reality this function is already implemented in CanIf layer*/
void CanIf_ControllerModeIndication(uint8 ControllerId, Can_ControllerStateType ControllerMode )
{
    (void)ControllerId;
    (void)ControllerMode;
}

/*CanIf callback function implementation to set the flag when a message is transmited
this function is called by the CAN interrupt.
In reality this function is already implemented in CanIf layer*/
void CanIf_TxConfirmation( PduIdType CanTxPduId )
{
    (void)CanTxPduId;
}

/*CanIf callback function implementation to set the flag when a message is received
this function is called by the CAN interrupt.
In reality this function is already implemented in CanIf layer*/
void CanIf_RxIndication(const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr )
{
    (void)Mailbox;
    if(PduInfoPtr->SduDataPtr[0] == 0x32)
    {
        /*do soemthing in case the first byte received is equal to 0x32*/
        for(uint8 i = 0; i < 8 ; i++)
        {
            Can_au8Sdu8bytes[i] = PduInfoPtr->SduDataPtr[i];
        }
    }
    //CanId is stored in Mailbox->CanId
}

int main( void )
{
    EcuM_Init();

    /*Start the CAN controller and make it active in the CAN bus network*/
    Can_43_FLEXCAN_SetControllerMode( CanController_0, CAN_CS_STARTED );

    while( 1u )
    {
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
}