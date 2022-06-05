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
#include "sys/param.h"
#include "sdkconfig.h"

static const char *TAG = "example";

/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO CONFIG_BLINK_GPIO

static uint8_t s_led_state = 0;
static int64_t time = 0;
static int64_t old_time = 0;
static int64_t duration = 0;
static int64_t duration_min = 100000000;
static int64_t duration_max = 0;


static void blink_led(void)
{
    /* Set the GPIO level according to the state (LOW or HIGH)*/
    gpio_set_level(BLINK_GPIO, s_led_state);
}

static void measure_time(void)
{
	time = esp_timer_get_time();
	duration = time - old_time;
	old_time = time;
}



static void time_statistic(void)
{
	duration_min = MIN(duration_min, duration);
	duration_max = MAX(duration_max, duration);
}

static void print_statistic(void)
{
    ESP_LOGI(TAG, "duration_min/max %lli/%lli microseconds", duration_min, duration_max);
    duration_min = 100000000;
    duration_max = 0;
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
    measure_time();

    while (1) {
    	for (int i = 0; i < 5000; ++i) {
            vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
        	measure_time();
        	time_statistic();
            blink_led();
            /* Toggle the LED state */
            s_led_state = !s_led_state;
		}
    	print_statistic();
    }
}
