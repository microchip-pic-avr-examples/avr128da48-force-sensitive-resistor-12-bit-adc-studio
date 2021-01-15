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
#define BAUD_RATE  115200
#include "clock_config.h"

#define USART_BLE_PORT USART0			/* BLE */
#define USART_CDC_PORT USART1          /* CDC Virtual COM port */


/********************************************************************usart_ble_init**************************************************************************************
Initializes USAR0
BLE communication. PA0 TX, PA1 RX
Baud Rate : 115200
***************************************************************************************************************************************************************/
void usart_ble_init()
{
	USART_BLE_PORT.CTRLA =  USART_RXCIE_bm;
	USART_BLE_PORT.CTRLB = USART_TXEN_bm |  USART_RXEN_bm ;
	USART_BLE_PORT.BAUD = (F_CPU * 64.0) / (BAUD_RATE * 16.0);
}
/********************************************************************usart_cdc_init**************************************************************************************
Initializes USART1
CDC Virtual come port is connected to USART1 on AVR128DA48 Curiosity Nano board, PC0:TX,PC1:RX
Baud Rate : 115200
********************************************************************************************************************************************************/
void usart_cdc_init()
{
	USART_CDC_PORT.CTRLB = USART_TXEN_bm |  USART_RXEN_bm ;
	USART_CDC_PORT.BAUD = (F_CPU * 64.0) / (BAUD_RATE * 16.0);	
}

/********************************************************************usart_put_c**************************************************************************************
Transmit data through USART
***************************************************************************************************************************************************************/
void usart_ble_put_c(uint8_t c)
{
	while (!(USART_BLE_PORT.STATUS & USART_DREIF_bm));
	USART_BLE_PORT.TXDATAL = c;
}

void usart_cdc_put_c(uint8_t c)
{
	while (!(USART_CDC_PORT.STATUS & USART_DREIF_bm));
	USART_CDC_PORT.TXDATAL = c;
}

uint8_t usart_ble_get_c()
{
	while (!(USART_BLE_PORT.STATUS & USART_RXCIF_bm))
	;
	return USART_BLE_PORT.RXDATAL;
}

uint8_t usart_cdc_get_c()
{
	while (!(USART_CDC_PORT.STATUS & USART_RXCIF_bm))
	;
	return USART_CDC_PORT.RXDATAL;
}


