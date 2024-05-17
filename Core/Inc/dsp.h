/*
 * dsp.h
 *
 *  Created on: May 13, 2024
 *      Author: hanzhang
 */

#ifndef INC_DSP_H_
#define INC_DSP_H_

#define WAVE_WRAP_WINDOW 10
#define INV_WAVE_WRAP_WINDOW 1.0f/WAVE_WRAP_WINDOW

#include "main.h"
#include "leaf.h"
//
//int waveWrapPtn = 0; float ave = 0.0f;
//float waveWrapMem[WAVE_WRAP_WINDOW];
//
////void mydsp_init(tMempool* const mp){
////	_tMempool* m = *mp;
////	waveWrapMem = (Lfloat*) mpool_alloc(sizeof(Lfloat) * WAVE_WRAP_WINDOW, m);
////}
//
//float waveWrap(float in, float low, float high){
//	if(high < low){
//		float a = high;
//		high = low;
//		low = a;
//	}
//
//	// fold
//	float gap = high - low;
//	while(in > high){ in -= gap;}
//	while(in > low){ in += gap;}
//
//	// scale
//	in = (in - low) / gap;
//
//	// sliding window smoothing
//	ave += INV_WAVE_WRAP_WINDOW * (in - waveWrapMem[waveWrapPtn]);
//	waveWrapMem[waveWrapPtn] = in;
//	if((++waveWrapPtn) == WAVE_WRAP_WINDOW) waveWrapPtn = 0;
//
//	return ave;
//}

#endif /* INC_DSP_H_ */
