/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "xi2c.h"
#include "fonts.h"
#include "ssd1306.h"
#include "esp_spi_flash.h"

#define DebugLED 2

//LEDs
#define IR1 16
#define IR2 18

//IRSensors
#define IRS1 17
#define IRS2 19

void initLed(int led);
void ledOn(int led);
void ledOff(int led);

void app_main()
{
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

	initLed(DebugLED);
	initLed(IR1);
	initLed(IR2);

    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        ledOn(DebugLED);
        ledOff(IR1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        ledOff(DebugLED);
        ledOn(IR1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}

void initLed(int led)
{
    gpio_pad_select_gpio(led);
    gpio_set_direction(led, GPIO_MODE_OUTPUT);
}
void ledOn(int led)
{
    gpio_set_level(led, 1);
}
void ledOff(int led)
{
    gpio_set_level(led, 0);
}
