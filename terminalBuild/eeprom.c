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


// functions
void Uart_configuration(void);
void EEPROM(void);
void metateds_ID(void);

void EEPROM(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
    while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0))
    {
    }
    uint32_t RetValue = MAP_EEPROMInit();

    if (RetValue != EEPROMInit())
    {
        UARTprintf("EEPROM not initialized!\n");
    }
    else
    {
        UARTprintf("EEPROM initialized!\n");
    
    }
    //return 0;
}
