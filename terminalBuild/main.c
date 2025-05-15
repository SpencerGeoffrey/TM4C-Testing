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

/*

*/
// variáveis
// MACROS
#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3

short i = 0;

// functions
void Uart_configuration(void);
void EEPROM(void);
void metateds_ID(void);
//void read_file(void);

//estrutura de TEDS_ID ---> META TEDS ----- > esta estrutura talvezz não poderá ser valida, pois Tabela 14 específica, até cinco bytes para TEDSID

/*struct META_TEDS {
    uint8_t type;
    uint8_t length;
    uint8_t family_member;
    uint8_t family_submember;
    uint8_t class;
    uint8_t version;
    uint8_t tuple_length;
}metaTeds;*/

//em alternativa:
// NOTA: 'Length' and 'Checksum' fields are not technically part of the TEDS data block but are shown in the TAble 14 to describe TEDS
//struct TEDS_ID{   //Table 14 - Structure of the META TEDS data block
//    uint8_t field_type;               // 3 for TEDSID
//    uint8_t length[5];          // 5 bytes
//}tedsID;



// The error routine that is called if the driver library encounters an error.
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif



int main(void)
{
    //
    Uart_configuration();
    metateds_ID();
    EEPROM();
}


























//int main(void)
//{
//    Uart_configuration();
//    UARTprintf("\r***************************************************************************************************\n");
//    UARTprintf("\r************************************ META TEDS************************************\n");
//    UARTprintf("\r***************************************************************************************************\n");

    // tamanho de cada campo
//    UARTprintf("\rType size: %u bytes\n", (unsigned int)sizeof(metaTeds.type));
//    UARTprintf("\rLength: %u bytes\n", (unsigned int)sizeof(metaTeds.length));
//    UARTprintf("\rFamily Member size: %u bytes\n", (unsigned int)sizeof(metaTeds.family_member));
//    UARTprintf("\rSize of Family Sub-member size: %u bytes\n", (unsigned int)sizeof(metaTeds.family_submember));
//    UARTprintf("\rSize of Class: %u bytes\n", (unsigned int)sizeof(metaTeds.class));
//    UARTprintf("\rSize of Version: %u bytes\n", (unsigned int)sizeof(metaTeds.version));
//    UARTprintf("\rSize of Tuple Length: %u bytes\n", (unsigned int)sizeof(metaTeds.tuple_length));

        // a função não fuciona de acordo com o desenvolvido em C devido às propriedades do MCU
    //read_file();

    //dito isto, por agora, os valores serão atribuídos manualmente. 

   /*
   while(1)
    {


    }
   */ 
//    metaTeds.type = 0x03;
//    metaTeds.length = 0x05;
//    metaTeds.family_member = 0x00;
//    metaTeds.family_submember = 0x00;
//    metaTeds.class = 0x01;
//    metaTeds.version = 0x02;
//    metaTeds.tuple_length = 0x01;
//    UARTprintf("\r\n");
//    UARTprintf("\rType = 0X%02X\n", metaTeds.type);
//    UARTprintf("\rLength = 0X%02X\n", metaTeds.length);
//    UARTprintf("\rFamily Member = 0X%02X\n", metaTeds.family_member);
//    UARTprintf("\rFamily Sub-member = 0X%02X\n", metaTeds.family_submember);
//    UARTprintf("\rClass = 0X%02X\n", metaTeds.class);
//    UARTprintf("\rVersion = 0X%02X\n", metaTeds.version);
//    UARTprintf("\rTuple Length = 0X%02X\n", metaTeds.tuple_length);
//    UARTprintf("\r\n");
    
    //***************************************************************************************************************************
    // considering the following struct TEDS_ID for the MEta TEDS to save the data in array:
    //***************************************************************************************************************************
//    UARTprintf("\r************************************ META TEDS - according to Table 14 ************************************\n");
    
//    struct TEDS_ID tedsID = {
//        .field_type = 0x03,
//        .length = {0x00, 0x00, 0x01, 0x02, 0x01}  
//    };
//    UARTprintf("\r\n");
//    UARTprintf("\rType = 0X%02X\n", tedsID.field_type);
//    UARTprintf("\rFamily Member: 0x%02X\n", tedsID.length[0]);
//    UARTprintf("\rFamily Sub-member: 0x%02X\n", tedsID.length[1]);
//    UARTprintf("\rClass: 0x%02X\n", tedsID.length[2]);
//    UARTprintf("\rVersion: 0x%02X\n", tedsID.length[3]);
//    UARTprintf("\rTuple Length: 0x%02X\n", tedsID.length[4]);
//    UARTprintf("\r\n");


//    EEPROM();

    
//    return 0;
//}



//void EEPROM(void)
//{
//    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
//    while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0))
//    {
//    }
//    uint32_t RetValue = MAP_EEPROMInit();

//    if (RetValue != EEPROMInit())
//    {
//        UARTprintf("EEPROM not initialized!\n");
//    }
//    else
//    {
//        UARTprintf("EEPROM initialized!\n");
//    
//    }


//}

/*



void read_file(void)
{
    FILE *file;
    file = fopen("teds_ID.txt", "r");
    if(file != NULL)
    {
        UARTprintf("\r\nFile opened successfully!\r\n");
        // Add code here to read and process the file content
        //fclose(file);
    }
    else
    {
        UARTprintf("\rFile not opened!\n");
        return 1;
    }

}
*/
