/*
 * ui.h
 *
 *  Created on: Aug 30, 2019
 *      Author: jeffsnyder
 */

#ifndef UI_H_
#define UI_H_
#define NUM_ADC_CHANNELS 8
extern uint16_t ADC_values[NUM_ADC_CHANNELS];

void mux_select_pin(int pin);

void mux_pull_values(float *x, float *y, float *fc, float *vari, int i);

#endif /* UI_H_ */

