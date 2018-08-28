/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Theodor Stana
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "firmware/drivers/mss_gpio/mss_gpio.h"
#include "firmware/CMSIS/system_m2sxxx.h"

static const mss_gpio_id_t LED[8] = {
		MSS_GPIO_0, MSS_GPIO_1, MSS_GPIO_2, MSS_GPIO_3,
		MSS_GPIO_4, MSS_GPIO_5, MSS_GPIO_6, MSS_GPIO_7,
};

void delay()
{
	int d = SystemCoreClock / 128;

	while (d-- > 0)
		;
}

int main(void)
{
	int i, current_val;

	MSS_GPIO_init();

	/* Init & turn on all LEDs */
	for (i = 0; i < 8; i++) {
		MSS_GPIO_config(LED[i], MSS_GPIO_OUTPUT_MODE);
		MSS_GPIO_set_output(LED[i], 0);
	}
	delay();
	delay();
	delay();
	delay();

	/* Blink all LEDs on start up */
	for (i = 0; i < 8; i++) {
		for (current_val = 0; current_val < 8; ++current_val)
			MSS_GPIO_set_output(LED[current_val], 1);
		delay();
		for (current_val = 0; current_val < 8; ++current_val)
			MSS_GPIO_set_output(LED[current_val], 0);
		delay();
	}

	/* Sequence-blink */
	for (;;) {
		for (i = 0; i < 8; i++) {
			current_val = (MSS_GPIO_get_outputs() & (1 << LED[i])) ? 1 : 0;
			MSS_GPIO_set_output(LED[i], current_val ^ 1);
			delay();
		}
	}
}
