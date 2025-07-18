/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

static const char *TAG = "example";

/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO CONFIG_BLINK_GPIO

static uint8_t s_led_state = 0;


static void heart_rate_task(void *param) {
    ESP_LOGI(TAG, "Heart rate task started");
    while (1) {
        UBaseType_t watermark = uxTaskGetStackHighWaterMark(NULL);
        ESP_LOGI("TASK_I", "HighWaterMark: %u bytes libres", watermark * sizeof(StackType_t));


        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

static void blink(void *param) 
    {
    ESP_LOGI(TAG, "Heart rate task started");
    while (1) {

        UBaseType_t watermark = uxTaskGetStackHighWaterMark(NULL);
        ESP_LOGI("TASK_B", "HighWaterMark: %u bytes libres", watermark * sizeof(StackType_t));
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

void app_main(void)
{

    /* Configure the peripheral according to the LED type */
    configure_led();
    xTaskCreate(heart_rate_task, "LED ASD", 2034, NULL, 5, NULL);
    xTaskCreate(blink, "LED blink", 2034, NULL, 5, NULL);
}
