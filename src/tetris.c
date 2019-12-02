#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#include <stdio.h>
#include <stdlib.h>

#include <FreeRTOS.h>
#include <task.h>

#define PORT_LED GPIOA
#define PIN_LED GPIO15

void task_blink(void *args __attribute__((unused)))
{
  while (1)
  {
    gpio_toggle(PORT_LED, PIN_LED);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

int main(void)
{
	rcc_clock_setup_in_hsi_out_48mhz();

	rcc_periph_clock_enable(RCC_GPIOA);
	gpio_mode_setup(PORT_LED, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_LED);
	gpio_set(PORT_LED, PIN_LED);
	int *test_var = malloc(sizeof(int));
	*test_var = 5;

	xTaskCreate(task_blink, "blink", 100, NULL, configMAX_PRIORITIES - 1, NULL);
	vTaskStartScheduler();

	while (1);
}


