/*
 * audiostream.c
 *
 *  Created on: Aug 30, 2019
 *      Author: jeffsnyder
 */


/* Includes ------------------------------------------------------------------*/
#include "audiostream.h"
#include "main.h"
#include "leaf.h"
#include "codec.h"
#include "tim.h"
#include "ui.h"

//the audio buffers are put in the D2 RAM area because that is a memory location that the DMA has access to.
int32_t audioOutBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2;
int32_t audioInBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2;

void audioFrame(uint16_t buffer_offset);
float audioTickL(float audioIn);
float audioTickR(float audioIn);
void buttonCheck(void);
void decideState(void);

HAL_StatusTypeDef transmit_status;
HAL_StatusTypeDef receive_status;


uint8_t codecReady = 0;

uint8_t buttonValues[NUM_BUTTONS];
uint8_t buttonValuesPrev[NUM_BUTTONS];
uint32_t buttonCounters[NUM_BUTTONS];
uint32_t buttonPressed[NUM_BUTTONS];

uint32_t buttonCountersHeld[3] = {0, 0, 0};
uint32_t buttonHeld[NUM_BUTTONS]= {0, 0, 0};

uint8_t LED_States[3] = {0,0,0};

float sample = 0.0f;

uint16_t frameCounter = 0;

//audio objects
tRamp adc[6];
tNoise noise;
tCycle mySine[6];
//tTapeDelay delT[2];
//tDelayExt delE;
tTapeDelayExt delTE;

//audio objects for external
tRamp adc_extern[STEPS_MAX * 2];

//MEMPOOLS
#define SMALL_MEM_SIZE 5000
char smallMemory[SMALL_MEM_SIZE];

#define MEDIUM_MEM_SIZE 500000
char mediumMemory[MEDIUM_MEM_SIZE] __ATTR_RAM_D1;

#define LARGE_MEM_SIZE 33554432 //32 MBytes - size of SDRAM IC
char largeMemory[LARGE_MEM_SIZE] __ATTR_SDRAM;

LEAF leaf;

tMempool smallPool;
tMempool largePool;

// interface
static float fc[STEPS_MAX], vari[STEPS_MAX], x[STEPS_MAX], y[STEPS_MAX];
static float randomness = 0.0f;
uint8_t count_knob = 0;
uint8_t method;
static float halls[NUM_HALLS];

// my parameters
static uint8_t state_cur, state_next;
float halls_cali[NUM_HALLS], halls_shift[NUM_HALLS];
uint16_t halls_cali_count = 0, halls_cali_done = 0;

/**********************************************/

typedef enum BOOL {
	FALSE = 0,
	TRUE
} BOOL;




void audioInit(I2C_HandleTypeDef* hi2c, SAI_HandleTypeDef* hsaiOut, SAI_HandleTypeDef* hsaiIn)
{
	// Initialize LEAF.

	LEAF_init(&leaf, SAMPLE_RATE, mediumMemory, MEDIUM_MEM_SIZE, &randomNumber);

	tMempool_init (&smallPool, smallMemory, SMALL_MEM_SIZE, &leaf);
	tMempool_init (&largePool, largeMemory, LARGE_MEM_SIZE, &leaf);


	for (int i = 0; i < 6; i++)
	{
		tRamp_initToPool(&adc[i],7.0f, 1, &smallPool); //set all ramps for knobs to be 7ms ramp time and let the init function know they will be ticked every sample

	}
	/*ramps for the external knobs*/
	for(int i = 0; i < STEPS_MAX * 2; i++)
	{
		tRamp_initToPool(&adc_extern[0],7.0f, 1, &smallPool);
	}

	tNoise_initToPool(&noise, WhiteNoise, &smallPool);
	for (int i = 0; i < 6; i++)
	{
		tCycle_initToPool(&mySine[i], &smallPool);
		tCycle_setFreq(&mySine[i], 440.0f);
	}

//	for(int i = 0; i < 2; i++)
//	{
//		tTapeDelay_initToPool(&delT[i], SAMPLE_RATE, MAX_DELAY, &largePool);
//	}
	uint32_t* temp = (uint32_t *) malloc(sizeof(uint32_t) );
	*temp = SAMPLE_RATE;
//	tDelayExt_initToPool(&delE, temp, MAX_DELAY, 1, &largePool);
	tTapeDelayExt_initToPool(&delTE, temp, MAX_DELAY, 1, &largePool);
	free(temp);


	HAL_Delay(10);

	for (int i = 0; i < AUDIO_BUFFER_SIZE; i++)
	{
		audioOutBuffer[i] = 0;
	}



	HAL_Delay(1);

	// set up the I2S driver to send audio data to the codec (and retrieve input as well)
	transmit_status = HAL_SAI_Transmit_DMA(hsaiOut, (uint8_t *)&audioOutBuffer[0], AUDIO_BUFFER_SIZE);
	receive_status = HAL_SAI_Receive_DMA(hsaiIn, (uint8_t *)&audioInBuffer[0], AUDIO_BUFFER_SIZE);

	// with the CS4271 codec IC, the SAI Transmit and Receive must be happening before the chip will respond to
	// I2C setup messages (it seems to use the masterclock input as it's own internal clock for i2c data, etc)
	// so while we used to set up codec before starting SAI, now we need to set up codec afterwards, and set a flag to make sure it's ready

	//now to send all the necessary messages to the codec
	AudioCodec_init(hi2c);

	// init variables
	for(int i = 0; i < STEPS_MAX; i++){
		fc[i] = 0; vari[i] = 0; x[i] = 0; y[i] = 0;
	}

}

void audioFrame(uint16_t buffer_offset)
{
	int i;
	int32_t current_sample = 0;

	frameCounter++;
	if (frameCounter > 1)
	{
		frameCounter = 0;
		buttonCheck();
	}

	for (i = 0; i < 6; i++)
	{
		tRamp_setDest(&adc[i], (ADC_values[i] * INV_TWO_TO_16));
	}

	/** read the inputs of the external knobs with multiplex **/
//	if (count_knob < STEPS_MAX - 1){
//		mux_pull_values(&randomness, &halls, &fc, &vari, count_knob);
//		count_knob++;
//	}
//	else{
//		mux_pull_values(&randomness, &halls, &fc, &vari, 7);
//		count_knob = 0;
//	}
	/*>-<*/


	/** check if button[2] is held for hall calibration **/
//	if(buttonHeld[0] == 1){
//		for(int j = 0; j < NUM_HALLS; j++){
//			halls_cali[j] = halls_cali[j] * ((float)halls_cali_count / (float)(halls_cali_count+1)) + halls[j] / (halls_cali_count+1);
//		}
//		halls_cali_count++;
//		halls_cali_done = 2; // 0: cali never happened, 1: cali done, 2: cali in progress
//	}
//	else {
//		halls_cali_count = 0;
//		if(halls_cali_done == 2){
//			halls_cali_done = 1;
//		}
//	}
	/*>-<*/

	/** find xs and ys **/
//	if (halls_cali_done){
//		for (int j = 0; j < NUM_HALLS; j++){
//			halls_shift[j] = halls[j] - halls_cali[j];
//		}
//	}

	/*>-<*/

//	/** decide the next state **/
//	if(buttonPressed[1] == 1){
//		decideState();
//		state_cur = state_next;
//		buttonPressed[1] = 0;
//	}
//	tRamp_setDest(&adc[0], (fc[state_cur] * INV_TWO_TO_16));
	/*>-<*/



	//if the codec isn't ready, keep the buffer as all zeros
	//otherwise, start computing audio!

	if (codecReady)
	{
		for (i = 0; i < (HALF_BUFFER_SIZE); i++)
		{

			if ((i & 1) == 0)
			{
				current_sample = (int32_t)(audioTickR(((float) (audioInBuffer[buffer_offset + i] << 8)) * INV_TWO_TO_31) * TWO_TO_23);
			}
			else
			{
				current_sample = (int32_t)(audioTickL(((float) (audioInBuffer[buffer_offset + i] << 8)) * INV_TWO_TO_31) * TWO_TO_23);
			}

			if (LED_States[2] == 1){		//mute
				current_sample *= 0;
			}

			audioOutBuffer[buffer_offset + i] = current_sample;

		}
	}
}


float sampleL = 0.0f, y0L = 0.0f, y1L = 0.0f, y2L = 0.0f, y3L = 0.0f, y4L = 0.0f, y1lastL = 0.0f, y2lastL = 0.0f, y3lastL = 0.0f, x1L = 0.0f, x2L = 0.0f;
float sampleR = 0.0f, y0R = 0.0f, y1R = 0.0f, y2R = 0.0f, y3R = 0.0f, y4R = 0.0f, y1lastR = 0.0f, y2lastR = 0.0f, y3lastR = 0.0f, x1R = 0.0f, x2R = 0.0f;
float filter_fc = 0.0f, filter_k = 0.0f, filter_p = 0.0f, filter_res = 0.0f, filter_r = 0.0f, filter_c = 0.0f;
float filter_4p_para1 = 7.2f, filter_4p_para2 = 6.4f, filter_4p_para3 = 1.386249;

float del_mix = 0.5f, del_fb = 1.0f;
int del_lenX = SAMPLE_RATE, del_lenY = SAMPLE_RATE;
int num_delX = 4, num_delY = 4;
//int* delaysX, delaysY;
float a0 = 0.0f, a1 = 0.0f, a2 = 0.0f, b1 = 0.0f, b2 = 0.0f;

uint16_t wc = 0, hc = 0; // multitap delay uneven peak, width center, height center
uint16_t del_len_old = 0;
uint32_t delaysX[8];
float delaysXdis[8], delaysXamp[8];

float audioTickL(float audioIn)
{

//	sampleL = audioIn;
	 /* sin output */
//	sampleL = 0.0f;
//	for (int i = 0; i < 6; i = i+2) // even numbered knobs (left side of board)
//	{
//		tCycle_setFreq(&mySine[i], (tRamp_tick(&adc[i]) * 500.0f) + 100.0f); // use knob to set frequency between 100 and 600 Hz
//		sampleL += tCycle_tick(&mySine[i]); // tick the oscillator
//	}
//
//	sampleL *= 0.33f; // drop the gain because we've got three full volume sine waves summing here
	/*>-<*/

	/* simple filters*/
//	moog_filter(audioIn, &sampleL);
//	first_allpass_filter(audioIn, &sampleL);
	/*>-<*/

	/* delay */
	/* tape delter */
//	filter_fc = tRamp_tick(&adc[0]) * 4950.0f + 50.0f;
//	filter_k = tan(PI * filter_fc * INV_SAMPLE_RATE);
//	filter_c = (filter_k - 1.0f) / (filter_k + 1.0f);
//	del_mix = 1.0f - tRamp_tick(&adc[1]);
//	del_lenX = (int)(pow(8, (9 * tRamp_tick(&adc[2]) - 3)) + 1);
//	del_lenY = LED_States[0] == 1 ? del_lenX : (int)(pow(8, (9 * tRamp_tick(&adc[5]) - 3)) + 1);
//	del_fb = tRamp_tick(&adc[3]);
//
//	a0 = del_mix + (1 - del_mix) * filter_c;
//	a1 = 1 - del_mix;
//	b1 = filter_c  * (1 - del_mix) * del_fb;
//
//	filter_fc = tRamp_tick(&adc[0]) * 4950.0f + 50.0f;
//	filter_k = tan(PI * filter_fc * INV_SAMPLE_RATE);
//	filter_c = (filter_k - 1.0f) / (filter_k + 1.0f);
//	del_mix = 1.0f - tRamp_tick(&adc[1]);
//	del_lenX = (int)(pow(8, (9 * tRamp_tick(&adc[2]) - 3)) + 1);
//	del_lenY = LED_States[0] == 1 ? del_lenX : (int)(pow(8, (9 * tRamp_tick(&adc[5]) - 3)) + 1);
////	del_len = tRamp_tick(&adc[2]) * SAMPLE_RATE * 3;
//	del_fb = tRamp_tick(&adc[3]);
//
//	a0 = del_mix + (1 - del_mix) * filter_c;
//	a1 = 1 - del_mix;
//	b1 = filter_c  * (1 - del_mix) * del_fb;
//
//	tTapeDelay_setDelay(&delT[0], del_lenX);
//	tTapeDelay_setDelay(&delT[1], del_lenY-1);
//
//	x1L = tTapeDelay_tick(&delT[0], audioIn);
//	sampleL = a0 * audioIn + a1 * x1L - b1 * y1L;
//	y1L = tTapeDelay_tick(&delT[1], sampleL);

	/*>-<*/

	/* multi delay */
//	num_delX = (int) (ADC_values[0] * INV_TWO_TO_16 * 8) + 1;
//	if (num_delX != delE->numPoint)
//	{
//		tDelayExt_setNumPoint(&delE, num_delX);
//	}
//
//	del_lenX = (int)(pow(8, (9 * tRamp_tick(&adc[1]) - 1)) + 1);
//	uint32_t delaysX[num_delX];
//	for(int i = 0; i < num_delX; i++) delaysX[i] = (uint32_t)(i+1) * del_lenX;
//	tDelayExt_setDelay(&delE, &delaysX[0]);
//
//	tDelayExt_tick(&delE, audioIn);
//	sampleL = 0.0f;
//	for(int i = 0; i < num_delX; i++) sampleL += delE->lastOuts[i] / num_delX;

	/* multi tape delay */
	int flag = 0;
	num_delX = (int) (ADC_values[0] * INV_TWO_TO_16 * 8) + 1;
	if (num_delX != delTE->numPoint)
	{
		tTapeDelayExt_setNumPoint(&delTE, num_delX);
		flag = 1;
	}

	// decide the delay pattern
	if(abs(ADC_values[1] - del_len_old) > 200){
		del_lenX = (int)(pow(8, (9 * (ADC_values[1] * INV_TWO_TO_16) - 1)) * 4 + num_delX);
//		del_lenX = (int)(pow(8, (9 * tRamp_tick(&adc[1]) - 1)) * 4 + num_delX); // the whole length of the delay line
		del_len_old = ADC_values[1];
	}

	if (flag == 1 || abs(ADC_values[3] - wc) > 200 || abs(ADC_values[4] - hc) > 200){
		wc = ADC_values[3];
		hc = ADC_values[4];
		float wcf = wc * INV_TWO_TO_16 * 2;
		float hcf = hc * INV_TWO_TO_16 * 2;
		float area = hcf > 1.0f ? hcf + wcf / 2.0f : 1 + hcf;
		area /= num_delX + 1;
		float inc1 = (hcf - 1) / wcf * 0.0004; // increment for the first segment, 100 division
		float inc2 = hcf > 1.0f ? hcf / (wcf - 2) * 0.0004 : (1 - hcf) / (2 - wcf) * 0.0004;

		float area_accum = 0.0f, area_cur_frame = 0.02f-inc1/2.0f, cur_frame = 0.0f;
		for (int i = 0; i < num_delX; i++){
			while(area_accum < area && cur_frame < 1.99f){
				area_cur_frame += cur_frame <= wcf ? inc1 : inc2;
				area_accum += area_cur_frame;
				cur_frame += 0.02;
			}

			delaysXdis[i] = cur_frame;
			delaysXamp[i] = area_cur_frame / 0.02;
			area_accum = 0.0f;
		}
	}

//
	for(int i = 0; i < num_delX; i++)
	{
//		delaysX[i] = (uint32_t)(i+1) * del_lenX;
		int j = (int)(delaysXdis[i] / 2.0f * (float)del_lenX) + 1;
		if (abs(delaysX[i] - j) > 80) delaysX[i] = j;
	}

	tTapeDelayExt_setDelay(&delTE, &delaysX[0]);
	tTapeDelayExt_tick(&delTE, audioIn);
	sampleL = 0.0f;
	for(int i = 0; i < num_delX; i++) sampleL += delTE->lastOuts[i] / num_delX * delaysXamp[i];
	/*>-<*/

	return sampleL;
}


uint32_t myCounter = 0;


float rightIn = 0.0f;
float audioTickR(float audioIn)
{
//	audioIn = tCycle_tick(&mySine[1]);
//	audioIn -= 1.0f;
//	sampleR = audioIn * (1 - coef1) + sampleR * coef1 ;

//	sampleR = abs(sampleR) > 1 ? sampleR/abs(sampleR) : sampleR;
//	sampleR += 1.0f;

//
//	for (int i = 0; i < 6; i = i+2) // odd numbered knobs (right side of board)
//	{
//		tCycle_setFreq(&mySine[i+1], (tRamp_tick(&adc[i+1]) * 500.0f) + 100.0f); // use knob to set frequency between 100 and 600 Hz
//		sample += tCycle_tick(&mySine[i+1]); // tick the oscillator
//	}
//	tCycle_setFreq(&mySine[0], (tRamp_tick(&adc[0]) * 500.0f) + 100.0f);
//	sample += tCycle_tick(&mySine[0]);
//	sample *= 0.33f; // drop the gain because we've got three full volume sine waves summing here


	//sample = tNoise_tick(&noise); // or uncomment this to try white noise

//	sampleR = audioIn;
	sampleR = 0.0f;
	return sampleR;
}

/* methods in audioTick for simple filters */
void moog_filter(float audioIn, float* sample){
	float sam = 0.0f;

	filter_fc = tRamp_tick(&adc[0]) * 4950.0f + 50.0f;
	filter_res = tRamp_tick(&adc[1]);
	filter_4p_para1 = tRamp_tick(&adc[3]) * 20.0f;
	filter_4p_para2 = tRamp_tick(&adc[4]) * 15.0f;
	filter_4p_para3 = tRamp_tick(&adc[5]) * 5.0f;

	filter_k = 7.2f * filter_fc * INV_SAMPLE_RATE - 6.4f * filter_fc * filter_fc * INV_SAMPLE_RATE * INV_SAMPLE_RATE - 1.0f;
//	filter_k = filter_4p_para1 * filter_fc / SAMPLE_RATE - filter_4p_para2 * filter_fc * filter_fc / SAMPLE_RATE / SAMPLE_RATE - 1.0f;
	filter_p = (filter_k + 1.0f) * 0.5f;
	filter_r = filter_res * exp((1.0f - filter_p) * 1.386249);
//	filter_r = filter_res * exp((1.0f - filter_p) * filter_4p_para3);

	sam = audioIn - filter_r * y4L;
	y1L = sam * filter_p + x1L * filter_p - filter_k * y1L;
	y2L = y1L * filter_p + y1lastL * filter_p - filter_k * y2L;
	y3L = y2L * filter_p + y2lastL * filter_p - filter_k * y3L;
	y4L = y3L * filter_p + y3lastL * filter_p - filter_k * y4L;
	y4L = y4L - y4L * y4L * y4L / 6;

	x1L = sam;
	y1lastL = y1L;
	y2lastL = y2L;
	y3lastL = y3L;
	*sample = y4L;
}

void first_allpass_filter(float audioIn, float* sample){
	filter_fc = tRamp_tick(&adc[0]) * 1550.0f + 50.0f;
	filter_k = tan(PI * filter_fc * INV_SAMPLE_RATE);
	filter_c = (filter_k - 1.0f) / (filter_k + 1.0f);

	y1L = filter_c * audioIn + x1L - filter_c * y1L;
	*sample = y1L + audioIn;
	x1L = audioIn;
}

void delter_tape(float audioIn, float* sample){

}
/*>-<*/


void buttonCheck(void)
{
	buttonValues[0] = !HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_6);
	buttonValues[1] = !HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_7);
	buttonValues[2] = !HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_11);

	for (int i = 0; i < NUM_BUTTONS; i++)
	{
	  if ((buttonValues[i] != buttonValuesPrev[i]) && (buttonCounters[i] < 10))
	  {
		  buttonCounters[i]++;
	  }
	  if ((buttonValues[i] != buttonValuesPrev[i]) && (buttonCounters[i] >= 10))
	  {
		  if (buttonValues[i] == 1)
		  {
			  buttonPressed[i] = 1;
		  }
		  buttonValuesPrev[i] = buttonValues[i];
		  buttonCounters[i] = 0;
	  }

	  if (buttonHeld[i] == 0)
	  {
	  if ((buttonValues[i] != 0) && (buttonCountersHeld[i] < 1000))
	  {
		  buttonCountersHeld[i]++;
	  }
	  if ((buttonValues[i] != 0) && (buttonCountersHeld[i] >= 1000))
	  {
	 	  buttonHeld[i] = 1;
	 	  buttonCountersHeld[i] = 0;
	  }
	  }
	  else
	  {
		  if ((buttonValues[i] == 0) && buttonCountersHeld[i] < 50)
		  {
			  buttonCountersHeld[i]++;
	  	  }
		  else if (buttonValues[i] == 0)
	  	  {
	  	 	  buttonHeld[i] = 0;
	  	 	  buttonCountersHeld[i] = 0;
	  	  }
	  }


	}

	if (buttonPressed[0] == 1)
	{
		if (LED_States[0] == 0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
			LED_States[0] = 1;
		}
		else
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
			LED_States[0] = 0;
		}
		buttonPressed[0] = 0;
	}

	if (buttonPressed[1] == 1)
	{
		if (LED_States[1] == 0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
			LED_States[1] = 1;
		}
		else
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
			LED_States[1] = 0;
		}
//		buttonPressed[1] = 0;
	}

	if (buttonPressed[2] == 1)
	{
		if (LED_States[2] == 0)
		{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
			LED_States[2] = 1;
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
			LED_States[2] = 0;
		}
		buttonPressed[2] = 0;
	}

	if (buttonHeld[0] == 1)
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
}


void decideState(){
	method = LED_States[0];
	float prob[STEPS_MAX], prob_accum[STEPS_MAX];

	if((method & 1) == 0){ //method: distance
		for(int i=0; i < STEPS_MAX; i++){
			prob[i] = sqrt((x[i]-x[state_cur]) * INV_TWO_TO_16 * (x[i]-x[state_cur]) * INV_TWO_TO_16 + (y[i]-y[state_cur]) * INV_TWO_TO_16 * (y[i]-y[state_cur]) * INV_TWO_TO_16);
			if(i == 0) {prob_accum[i] = prob[i];}
			else{prob_accum[i] = prob_accum[i - 1] + prob[i];}
		}
	}
	else{ // method: y
		for(int i=0; i < STEPS_MAX; i++){
			prob[i] = y[i] * INV_TWO_TO_16;
			if(i == 0) {prob_accum[i] = prob[i];}
			else{prob_accum[i] = prob_accum[i - 1] + prob[i];}
		}
	}

	float numrand = randomNumber() * prob_accum[STEPS_MAX - 1];

	for(int i=0; i < STEPS_MAX; i++){
		if(prob_accum[i] > numrand){
			state_next = i;
			break;
		}
	}
}

void HAL_SAI_ErrorCallback(SAI_HandleTypeDef *hsai)
{
	;
}

void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai)
{
	;
}

void HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
  ;
}


void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai)
{
	audioFrame(HALF_BUFFER_SIZE);
}

void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
	audioFrame(0);
}
