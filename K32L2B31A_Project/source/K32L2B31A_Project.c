/*! @file : K32L2B31A_Project.c
 * @author  Ernesto Andres Rincon Cruz
 * @version 0.0.000
 * @date    23/08/2021
 * @brief   Funcion principal main
 * @details
 *			v0.0.000	Proyecto base creado usando MCUXpresso
 *
 *
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "K32L2B31A.h"
#include "fsl_debug_console.h"
#include <limits.h>
#include <float.h>

#include <iot_sdk_peripherals_leds.h>
#include <iot_sdk_peripherals_light.h>
#include "iot_sdk_peripherals_buttons.h"
#include "iot_sdk_peripheral_temperature.h"

#include "iot_sdk_ irq_lptimer0.h"


int main(void) {
	float light_value;
	float temperature_value;
	bool switch1;
	bool switch2;

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    /* Activa LPTMR0 para que iniciar contador y posterior IRQ cada 1 segundo*/
    LPTMR_StartTimer(LPTMR0);



    while(1) {

    	if(lptmr0_ticks!=0){
    		lptmr0_ticks=0;
    		 switch1 = leerswitch1();
    		 switch2 = leerswitch2();
    		 if (switch1!=true){

    			 temperature_value=getTemperatureValue();
    			 printf("Temp(°C): %f\r\n", temperature_value);
    			  printf("\r\n");

    		 }

    		 if (switch2!=true){

    			 light_value=getLightADC();
    			 printf("Luminosidad(LUX): %d\r\n", light_value);
    			  printf("\r\n");
    		    		 }


    	}
    }
    return 0 ;
}
