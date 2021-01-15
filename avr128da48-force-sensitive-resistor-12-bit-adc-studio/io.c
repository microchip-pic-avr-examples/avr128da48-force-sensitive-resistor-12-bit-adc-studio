/**
 * \file
 *
 *
 (c) 2021 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

#include <avr/io.h>
#include <stdbool.h>

/**************************************IO_init*****************************************************
    Initializes IO pin directions.
    PA1:    USART0 RXD:             input
    PA0:    USART0 TXD:             output
    PD4:    Analog channel 4:       digital input buffer disabled .AN2 on Curiosity Nano Adapter
    PC0:    USART1 TXD (CDC):       output
    PD7:    rn4871 reset signal:    output  
    PE3:    RGBLED:                 output. IN2 on 4x4 RGB Click board, CS3 on Curiosity Nano Adapter
**************************************************************************************************/
void io_init(void)
{
	PORTC.DIRSET = PIN0_bm ;  
	PORTE.DIRSET = PIN3_bm;  /* PE3 : CS3, RGBLED */
	
	PORTD.PIN4CTRL |= PORT_ISC_INPUT_DISABLE_gc; /* PD4 analog */
	
	PORTD.DIRSET|= PIN7_bm; /* PD7, rn4871 HWreset */
	
	PORTA.DIRSET |= PIN0_bm; 
	PORTA.DIRCLR &= PIN1_bm; 
	
}

void HWRESET_PIN_set_level(bool state)
{
	if(state)
	{
		PORTD.OUTSET |= PIN7_bm;
	}
	else
	{
		PORTD.OUTCLR |= PIN7_bm;
	}
}