#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"


//variables to store the switches value
uint8_t sw1;
uint8_t sw2;
//flags for when switch button are clicked
bool sw1_flag = false;
bool sw2_flag = false;
// counter for LED control
uint8_t counter = 0;
/*-----------------------------*/
int i, j = 0;  

void control_Led(void);

//! \addtogroup example_list
//! <h1>Blinky (blinky)</h1>
//!
//! A very simple example that blinks the on-board LED using direct register
//! access.

// The error routine that is called if the driver library encounters an error.
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

int main(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);                                                                    // Enable the GPIO port that is used for the on-board LED.

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))                                                              // Check if the peripheral access is enabled.
    {
    }
    GPIOUnlockPin(GPIO_PORTF_BASE, GPIO_PIN_0);                                                                     // To use the switch button 2 it must be unlocked through the following line

    // configuring LED pins as output 
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);                                                             // In user guide, schematic LED_R(ed) also presented in table 2.2
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);                                                             // In user guide, schematic LED_B(lue) also presented in table 2.2
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);                                                             // In user guide, schematic LED_G(reen) also presented in table 2.2
    
    // Configuring switch buttons as inputs and with weak pull-up internal resistors
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);                                                              // in User guide, schematic USR_SW1
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);                                                              // in User guide, schematic USR_SW2
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);           //configuring pull-up resistors for switch_1 (weak pull-up)
   
    while(1)
    {
        sw1 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
        sw2 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
        /*
        SysCtlDelay(1000000);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2|GPIO_PIN_3, 0x00| 0x00);
        SysCtlDelay(1000000);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_3, 0x00| 0x00);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
        SysCtlDelay(1000000);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2, 0x00| 0x00);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
        SysCtlDelay(1000000);
*/

       if (sw1 == 0 && !sw1_flag) 
        {
            sw1_flag = true;
            counter++;
            if (counter > 8)
            {
                counter = 0;
            }
            for(i=0; i < 500000; i++){}
        }
        else if(sw1 == GPIO_PIN_4)
        {
            sw1_flag = false;
        }

        if(sw2 == 0 && !sw2_flag)
        {
            sw2_flag = true;
            counter--;
            if(counter < 1)
            {
                counter = 0;
            }
            for(i=0; i < 500000; i++){}
        }
        else if(sw2 == 1)
        {
            sw2_flag = false;
        }

        control_Led();
    }
}

void control_Led(void)
{
    switch (counter)
    {
        case 0:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
            break;
        case 1:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2|GPIO_PIN_3, 0x00);
            break;
        case 2:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_3, 0x00|0x00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
            break;
        case 3:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2, 0x00|0x00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            break;
        case 4: 
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_1|GPIO_PIN_2);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
            break;
        case 5:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_3, GPIO_PIN_1|GPIO_PIN_3);    
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
            break;
        case 6:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_2|GPIO_PIN_3);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
            break;
        case 7: 
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
            break;
        case 8:
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
           SysCtlDelay(1000000);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
           SysCtlDelay(1000000);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_3, 0x00|0x00);
           SysCtlDelay(1000000);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
           SysCtlDelay(1000000);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2, 0x00|0x00);
           SysCtlDelay(1000000);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
           SysCtlDelay(1000000);
            break;
        default:
            break;
   }
}
