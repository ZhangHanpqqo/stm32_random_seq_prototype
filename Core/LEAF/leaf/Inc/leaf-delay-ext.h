/*
 * leaf-delay-ext.h
 *
 *  Created on: May 9, 2024
 *      Author: hanzhang
 *      this is an extension of the leaf delay where an array of pointers are included to allow multistate delay line
 */

#ifndef LEAF_LEAF_INC_LEAF_DELAY_EXT_H_
#define LEAF_LEAF_INC_LEAF_DELAY_EXT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "leaf-math.h"
#include "leaf-mempool.h"
#include "leaf-delay.h"


//==============================================================================

   /*!
    * you know you will write some comments one day
    */

typedef struct _tDelayExt
{
	tDelay tdelay;
	uint32_t numPoint;
	uint32_t* delays;
	Lfloat* lastOuts;
} _tDelayExt;

typedef _tDelayExt* tDelayExt;

void tDelayExt_initToPool (tDelayExt* const, uint32_t* delays, uint32_t maxDelay, uint32_t numPoint, tMempool* const);
void tDelayExt_free (tDelayExt* const);
void tDelayExt_clear (tDelayExt* const);
void tDelayExt_tick(tDelayExt* const, Lfloat input);
void tDelayExt_setDelay(tDelayExt* const, uint32_t* delays);
void tDelayExt_setNumPoint(tDelayExt* const, int numPoint);


//==============================================================================

   /*!
    * you know you will write some comments one day
    */

typedef struct _tTapeDelayExt
{
	_tTapeDelay tdelay;
	uint32_t numPoint;
	uint32_t* delays;
	Lfloat* lastOuts;
} _tTapeDelayExt;

typedef _tTapeDelayExt* tTapeDelayExt;

void tTapeDelayExt_initToPool (tTapeDelayExt* const, uint32_t delay, uint32_t maxDelay, uint32_t numPoint, tMempool* const);
void tTapeDelayExt_free (tTapeDelayExt* const);
void tTapeDelayExt_clear (tTapeDelayExt* const);
void tTapeDelayExt_tick(tTapeDelayExt* const, Lfloat input);
void tTapeDelayExt_setDelay(tTapeDelay* const, uint32_t* delays);


#ifdef __cplusplus
}
#endif

#endif /* LEAF_LEAF_INC_LEAF_DELAY_EXT_H_ */
