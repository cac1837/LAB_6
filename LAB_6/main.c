
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.c"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"
#include "driverlib/sysctl.h"

/**
 * main.c
 */
uint32_t segundos = 0 ;

int main(void)
{
    //configuracion del cristal/reloj
    SysCtlClockSet ( SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ ) ;
    //habilito los perifericos
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIOF ) ;
//configuracion del boton 1 de la tiva como entrada como pull up
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE , GPIO_PIN_4 ) ;
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4, GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU ) ;
//configuracion del led RGB para encender y ver el color y estan como salidas
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE,GPIO_PIN_1) ;//led rojo
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_2) ;//led azul
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_3) ;//led verde

    segundos = SysCtlClockGet() / 3 ;//funcion para determinar el segundo
    while(1){
        if((GPIOPinRead (GPIO_PORTF_BASE,GPIO_PIN_4 ) & 0x16)==0){//lee siempre 1 si es 0 entra al if y pasa el while hasta que deje de presioanr ejecuta la secuencia de lo contrario no hace nada
        while((GPIOPinRead (GPIO_PORTF_BASE,GPIO_PIN_4 ) & 0x16)==0){}//antirebote
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);//verde; 08 enciende solo el pin 3
        SysCtlDelay (segundos) ;//la funcion de SysCtlDelay lo mide en nanosegundos
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);//00 apaga los 3 pines
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);//verde parapadeante
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x0A);//amarillo; 0A enciende el pin 1 y 3
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x02);//rojo; 02 enciende el pin 1
    }
    }
}
