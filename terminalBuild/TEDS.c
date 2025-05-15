/*
cria o projeto ----> ccs-server-cli -noSplash -workspace "C:\Users\TavaresSpencer1\workspace_ccstheia" -application com.ti.ccs.apps.createProject -ccs.name fromTerminal -ccs.device TM4C123GH6PM -ccs.outputType executable -ccs.endianness little -ccs.outputFormat elf

'bilda o project ---->ccs-server-cli -noSplash -workspace "C:\Users\TavaresSpencer1\workspace_ccstheia" -application com.ti.ccs.apps.buildProject -ccs.projects terminalBuild -ccs.buildConfiguration Debug

depois se não tiver opção de compilar no IDe, importar o projecto, com o nome definido
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_adc.h"
#include "inc/hw_types.h"
#include "inc/hw_udma.h"
#include "driverlib/adc.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"
#include "utils/uartstdio.h" //--> criei pasta utils e adicionei on ficheiro uartstdio.c para permitir o uso do 'uartprintf

#define UUID_TYPE_ID    0x04
#define UUID_LENGTH     16


/* 
******************* FUNCTIONS ***********************
*/
void Uart_configuration(void);
void EEPROM(void);
void metateds_ID(void);

/* ------------------ META TEDS Identification -----------------*/

struct META_TEDS_ID
{
    uint8_t type;
    uint8_t length;
    uint8_t family_member;
    uint8_t family_submember;
    uint8_t class;
    uint8_t version;
    uint8_t tuple_length;
}META_TEDS_ID;

struct META_TEDS_ID metatedsID = // encoded using the IEEE 1451 Playground ----> TEDS ID: 0x03 0x05 0x00 0xFF 0x01 0x02 0x01
{
    .type = 0x03,
    .length = 0x05,
    .family_member = 0x00,
    .family_submember = 0xFF, //1451.0
    .class = 0x01,
    .version = 0x02, 
    .tuple_length = 0x01, 
};
struct UUID
{
    uint8_t UUID_type;
    uint8_t UUID_length;
    uint8_t UUID[UUID_LENGTH];
}UUID;

struct UUID uuid =
{
    .UUID_type = UUID_TYPE_ID,
    .UUID_length = UUID_LENGTH,
    .UUID = {0x80, 0x00, 0x27, 0x00, 0x00, 0x70, 0x00, 0x00, 0x10, 0x7D, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x00}
};




// this could also be determined as 
// struct META_TEDS_ID metatedsID = {0x03, 0x05, 0x00, 0xFF, 0x01, 0x02, 0x01}

void Uart_configuration(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);                      //ativa perifereico para ser usado pelo UART
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
    {}
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);                //ativa o UART0
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
    {}
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);                            //UART Rx --> A0
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);                            //UART Tx --> A1
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);  // Tipo de pinos UART pino Rx e Tx
    MAP_UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);           // para usar o oscilador interno a 16MHz como clock source

    UARTStdioConfig(0, 115200, 16000000);
}



void metateds_ID(void)
{
    int j = 0;
    Uart_configuration();
    UARTprintf("\r************************************************************************************************************\n");
    UARTprintf("\r************************************ META TEDS ************************************\n");
    UARTprintf("\r************************************************************************************************************\n");

    // tamanho de cada campo METATEDS
    UARTprintf("\rType size: %u bytes\n", (unsigned int)sizeof(metatedsID.type));
    UARTprintf("\rLength: %u bytes\n", (unsigned int)sizeof(metatedsID.length));
    UARTprintf("\rFamily Member size: %u bytes\n", (unsigned int)sizeof(metatedsID.family_member));
    UARTprintf("\rSize of Family Sub-member size: %u bytes\n", (unsigned int)sizeof(metatedsID.family_submember));
    UARTprintf("\rSize of Class: %u bytes\n", (unsigned int)sizeof(metatedsID.class));
    UARTprintf("\rSize of Version: %u bytes\n", (unsigned int)sizeof(metatedsID.version));
    UARTprintf("\rSize of Tuple Length: %u bytes\n", (unsigned int)sizeof(metatedsID.tuple_length));

  /*
    UARTprintf("\rType = 0X%02X\n", metatedsID.type);
    UARTprintf("\rLength = 0X%02X\n", metatedsID.length);
    UARTprintf("\rFamily Member = 0X%02X\n", metatedsID.family_member);
    UARTprintf("\rFamily Sub-member = 0X%02X\n", metatedsID.family_submember);
    UARTprintf("\rClass = 0X%02X\n", metatedsID.class);
    UARTprintf("\rVersion = 0X%02X\n", metatedsID.version);
    UARTprintf("\rTuple Length = 0X%02X\n", metatedsID.tuple_length);
    UARTprintf("\r\n");
  */  

    // print nome e valor associado, para qu não o faça um a um, agora iteando... AI suggestion!!!!
    const char* field_name[] = {"Type", "Length", "Family Member", "Family Submember", "Class", "Version", "Tuple Length", "UUID Type number", "UUID Length", "UUID"};

    const uint8_t* values[] = {
        &metatedsID.type,
        &metatedsID.length,
        &metatedsID.family_member,
        &metatedsID.family_submember,
        &metatedsID.class,
        &metatedsID.version,
        &metatedsID.tuple_length, 
        &uuid.UUID_type, 
        &uuid.UUID_length

    };

    int field_count = sizeof(values) / sizeof(values[0]);
    UARTprintf("\r************************************************************************************************************\n");
    UARTprintf("\r ********************** Meta TEDS Identfication and Universal Unique Identifier (ID) **********************n");
    UARTprintf("\r************************************************************************************************************\n");

    for(j = 0; j < field_count; j++)
    {
        UARTprintf("\r%s : 0x%02X\n", field_name[j], *values[j]);
        
        
    }

    UARTprintf("\rUUID : ");
    for(j = 0; j < UUID_LENGTH; j++) 
    {
        UARTprintf("0x%02X", uuid.UUID[j]);
        if (j < UUID_LENGTH - 1) UARTprintf(",");
    }
    UARTprintf("\r\n");
}


