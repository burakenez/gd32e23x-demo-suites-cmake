/*!
    \file  main.c
    \brief SPI flash demo

    \version 2024-02-28, V2.2.0, demo for GD32E231
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include <stdio.h>
#include "gd32e23x.h"
#include "systick.h"
#include "gd25qxx.h"
#include "gd32e231k_eval.h"

#define BUFFER_SIZE              256U
#define TX_BUFFER_SIZE           (countof(tx_buffer) - 1)
#define RX_BUFFER_SIZE           0xFFU

#define countof(a)               (sizeof(a) / sizeof(*(a)))

#define SFLASH_ID                0xC84015U
#define FLASH_WRITE_ADDRESS      0x000000U
#define FLASH_READ_ADDRESS       FLASH_WRITE_ADDRESS

uint32_t int_device_serial[3];
uint8_t led_count;

uint8_t tx_buffer[256];
uint8_t rx_buffer[256];
uint32_t flash_id = 0;
uint16_t i = 0;
uint8_t is_successful = 0;

void get_chip_serial_num(void);
ErrStatus memory_compare(uint8_t *src, uint8_t *dst, uint16_t length);
void test_status_led_init(void);

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    /* systick configuration*/
    systick_config();

    /* configure the led GPIO */
    test_status_led_init();

    /* USART parameter configuration */
    gd_eval_com_init(EVAL_COM);

    /* configure SPI1 GPIO and parameter */
    spi_flash_init();

    /* GD32E231K_EVAL_1.0 start up */
    printf("\n\r###############################################################################\n\r");
    printf("\n\rGD32E231K_EVAL_1.0 System is Starting up...\n\r");
    printf("\n\rGD32E231K_EVAL_1.0 Flash:%dK\n\r", *(__IO uint16_t *)(0x1FFFF7E0));

    /* get chip serial number */
    get_chip_serial_num();

    /* printf CPU unique device id */
    printf("\n\rGD32E231K_EVAL_1.0 The CPU Unique Device ID:[%X-%X-%X]\n\r", int_device_serial[2],
           int_device_serial[1], int_device_serial[0]);

    printf("\n\rGD32E231K_EVAL_1.0 SPI Flash:GD25Q16 configured...\n\r");

    /* get flash id */
    flash_id = spi_flash_read_id();
    printf("\n\rThe Flash_ID:0x%X\n\r\n\r", flash_id);

    /* flash id is correct */
    if(SFLASH_ID == flash_id) {
        printf("\n\rWrite to tx_buffer:\n\r\n\r");

        /* printf tx_buffer value */
        for(i = 0; i < BUFFER_SIZE; i++) {
            tx_buffer[i] = i;
            printf("0x%02X ", tx_buffer[i]);

            if(15 == i % 16) {
                printf("\n\r");
            }
        }

        printf("\n\r\n\rRead from rx_buffer:\n\r\n\r");

        /* erase the specified flash sector */
        spi_flash_sector_erase(FLASH_WRITE_ADDRESS);

        /* write tx_buffer data to the flash */
        spi_flash_buffer_write(tx_buffer, FLASH_WRITE_ADDRESS, 256);

        delay_ms(10);
        /* read a block of data from the flash to rx_buffer */
        spi_flash_buffer_read(rx_buffer, FLASH_READ_ADDRESS, 256);

        /* printf rx_buffer value */
        for(i = 0; i < BUFFER_SIZE; i ++) {
            printf("0x%02X ", rx_buffer[i]);
            if(15 == i % 16) {
                printf("\n\r");
            }
        }

        if(ERROR == memory_compare(tx_buffer, rx_buffer, 256)) {
            printf("\n\rErr:Data Read and Write aren't Matching.\n\r");
            is_successful = 1;
        }

        /* spi qspi flash test passed */
        if(0 == is_successful) {
            printf("\n\rSPI-GD25Q16 Test Passed!\n\r");
        }
    } else {
        /* spi flash read id fail */
        printf("\n\rSPI Flash: Read ID Fail!\n\r");
    }

    while(1) {
        /* toggle LED1 every 500ms */
        gd_eval_led_toggle(LED1);
        delay_ms(500);
    }
}

/*!
    \brief      get chip serial number
    \param[in]  none
    \param[out] none
    \retval     none
*/
void get_chip_serial_num(void)
{
    int_device_serial[0] = *(__IO uint32_t *)(0x1FFFF7E8);
    int_device_serial[1] = *(__IO uint32_t *)(0x1FFFF7EC);
    int_device_serial[2] = *(__IO uint32_t *)(0x1FFFF7F0);
}

/*!
    \brief      test status led initialize
    \param[in]  none
    \param[out] none
    \retval     none
*/
void test_status_led_init(void)
{
    /* initialize the led1 */
    gd_eval_led_init(LED1);

    /* turn off led1 */
    gd_eval_led_off(LED1);
}

/*!
    \brief      memory compare function
    \param[in]  src: source data pointer
    \param[in]  dst: destination data pointer
    \param[in]  length: the compare data length
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus memory_compare(uint8_t *src, uint8_t *dst, uint16_t length)
{
    while(length --) {
        if(*src++ != *dst++) {
            return ERROR;
        }
    }
    return SUCCESS;
}

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(EVAL_COM, (uint8_t)ch);
    while(RESET == usart_flag_get(EVAL_COM, USART_FLAG_TBE));
    return ch;
}
