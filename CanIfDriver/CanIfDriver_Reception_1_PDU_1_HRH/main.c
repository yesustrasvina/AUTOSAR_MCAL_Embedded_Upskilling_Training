#include "Mcu.h"
#include "Port.h"
#include "Platform.h"
#include "Osif.h"
#include "Can_43_FLEXCAN.h"
#include "CanIf.h"

/*flags to indicate Transmition*/
boolean CanIf_bTxFlag = FALSE;

/*message to Tx and Rx*/
uint8 Can_au8Sdu8bytes[8U];

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
void CDD_UserRxIndication( PduIdType RxPduId, const PduInfoType* PduInfoPtr )
{
    (void)RxPduId;
    if(PduInfoPtr->SduDataPtr[0] == 0x32)
    {
        /*do soemthing in case the first byte received is equal to 0x32*/
        for(uint8 i = 0; i < 8 ; i++)
        {
            Can_au8Sdu8bytes[i] = PduInfoPtr->SduDataPtr[i];
        }
    }
}

void EcuM_Init( void );

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
    Mcu_Init( &Mcu_Config );
    Mcu_InitClock( McuClockSettingConfig_0 );
    Mcu_SetMode( McuModeSettingConf_0 );
    /*Init the internal tick reference Systick Timer*/
    OsIf_Init( NULL_PTR );
    /*enable and setup interrupts in use by the Can Driver*/
    Platform_Init( NULL_PTR );
    /*Apply all the Pin Port microcontroller configuration*/
    Port_Init( &Port_Config );
    /*init the FlexCAN2 with the paramters set in Tresos in loop back mode*/
    Can_43_FLEXCAN_Init( &Can_43_FLEXCAN_Config );
    CanIf_Init( &CanIf_Config );
}