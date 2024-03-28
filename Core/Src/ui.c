/*
 * ui.c
 *
 *  Created on: Dec 18, 2018
 *      Author: jeffsnyder
 */
#include "main.h"
#include "ui.h"
#include "audiostream.h"
#include "adc.h"
#include "stm32h7xx_hal.h"

#define MUX_SEL_REG GPIOB
#define MUX_SEL_PIN_A GPIO_PIN_12
#define MUX_SEL_PIN_B GPIO_PIN_13
#define MUX_SEL_PIN_C GPIO_PIN_14

uint16_t ADC_values[NUM_ADC_CHANNELS] __ATTR_RAM_D2;

const int mux_sel_pin[3] = {MUX_SEL_PIN_A, MUX_SEL_PIN_B, MUX_SEL_PIN_C};

void mux_select_pin(int pin)
{
	for (int i = 0; i < 3; i++){
		if(pin & (1 << i)){
			HAL_GPIO_WritePin(MUX_SEL_REG, mux_sel_pin[i], GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin(MUX_SEL_REG, mux_sel_pin[i], GPIO_PIN_RESET);
		}
	}
}


void mux_pull_values(float *x, float *y, float *fc, float *vari, float *randomness, int i){

	mux_select_pin(i);
	x[i] = ADC_values[6];
	y[i] = ADC_values[7];
//	fc[i] = ADC_values[i];
//	vari[i] = ADC_values[i + 3];

	fc[0] = ADC_values[0]; fc[1] = ADC_values[1]; fc[2] = ADC_values[2];
	vari[0] = ADC_values[3]; vari[1] = ADC_values[4]; vari[2] = ADC_values[5];

	randomness = ADC_values[8];

}
