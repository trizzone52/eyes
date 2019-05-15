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
#include "esp_spi_flash.h"
#include "wifiPassword.h"

#define DebugLED 2

//LEDs
#define IR1 16
#define IR2 18

//IRSensors
#define IRS1 17
#define IRS2 19

//Display stuff
#define SSD1306_HEIGHT 32
#include "ssd1306.h"

//I2C values
#define I2C_EXAMPLE_MASTER_SCL_IO    22    /*!< gpio number for I2C master clock */
#define I2C_EXAMPLE_MASTER_SDA_IO    21    /*!< gpio number for I2C master data  */
#define I2C_EXAMPLE_MASTER_NUM I2C_NUM_1   /*!< I2C port number for master dev */
#define I2C_EXAMPLE_MASTER_TX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_EXAMPLE_MASTER_RX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_EXAMPLE_MASTER_FREQ_HZ    100000     /*!< I2C master clock frequency */

void initLed(int led);
void ledOn(int led);
void ledOff(int led);

void initDisplay(void);

xSemaphoreHandle print_mux;

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

	//Setup LEDS
	initLed(DebugLED);
	initLed(IR1);
	initLed(IR2);

	//Setup Display
    print_mux = xSemaphoreCreateMutex();
	initDisplay();
    SSD1306_Init();

	//Display initial values
	//printf("Placing ESP"); 
	//SSD1306_GotoXY(0, 0);
    //SSD1306_Puts("ESP32", &Font_7x10, SSD1306_COLOR_WHITE);
	//printf("Placed ESP"); 
    //SSD1306_UpdateScreen();
	SSD1306_Fill(SSD1306_COLOR_BLACK);
    SSD1306_UpdateScreen();
	SSD1306_DrawCircle(64, 16, 30, SSD1306_COLOR_WHITE);
    SSD1306_UpdateScreen();

	for (int i = 3; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        ledOn(DebugLED);
        ledOff(IR1);
		SSD1306_ToggleInvert();
		SSD1306_UpdateScreen();
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
void initDisplay()
{
    int i2c_master_port = I2C_EXAMPLE_MASTER_NUM;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_EXAMPLE_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = I2C_EXAMPLE_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_EXAMPLE_MASTER_FREQ_HZ;
    i2c_param_config(i2c_master_port, &conf);
    i2c_driver_install(i2c_master_port, conf.mode,
                       I2C_EXAMPLE_MASTER_RX_BUF_DISABLE,
                       I2C_EXAMPLE_MASTER_TX_BUF_DISABLE, 0);
}
