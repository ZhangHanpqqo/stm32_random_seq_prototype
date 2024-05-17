/*
 * leaf-delay-ext.c
 *
 *  Created on: May 9, 2024
 *      Author: hanzhang
 */
#if _WIN32 || _WIN64

#include "..\Inc\leaf-delay.h"
#include "..\Inc\leaf-delay-ext.h"
#include "..\leaf.h"

#else

#include "../Inc/leaf-delay.h"
#include "../Inc/leaf-delay-ext.h"
#include "../Inc/leaf-math.h"
#include "../leaf.h"

#endif


//==============================================================================

   /*!
    * you know you will write some comments one day, right
    */


void    tDelayExt_initToPool   (tDelayExt* const dlext, uint32_t* delays, uint32_t maxDelay, uint32_t numPoint, tMempool* const mp)
{
//	_tMempool* m = *mp;
    _tDelayExt* d = *dlext = (_tDelayExt*) malloc(sizeof(_tDelayExt));

    tDelay_initToPool(&(d->tdelay), delays[0], maxDelay, mp);
    d->numPoint = numPoint;
    d->delays = (uint32_t *) malloc(sizeof(uint32_t) * numPoint);
    d->lastOuts = (Lfloat *) malloc(sizeof(Lfloat) * numPoint);

    for (int i = 0; i < numPoint; i++){
    	d->delays[i] = delays[i];
    	d->lastOuts[i] = 0.0f;
    }

}

void tDelayExt_free (tDelayExt* const dlext){
	_tDelayExt* d = *dlext;
	_tDelay* dt = d->tdelay;
	mpool_free((char*) dt->buff, dt->mempool);
	mpool_free((char*) dt, dt->mempool);
	free(d);
}

void tDelayExt_clear (tDelayExt* const dlext){
	_tDelayExt* d = *dlext;
//	_tDelay* dt = &(d->tdelay);
	for (unsigned i = 0; i < (d->tdelay)->maxDelay; i++) (d->tdelay)->buff[i] = 0;
}

void tDelayExt_tick(tDelayExt* const dlext, Lfloat input){
	_tDelayExt* d = *dlext;
//	_tDelay* dt = (d->tdelay);
	tDelay_tick(&(d->tdelay), input);
	d->lastOuts[0] = (d->tdelay)->lastOut;

	for(int i = 1; i < d->numPoint; i++){
		d->lastOuts[i] = tDelay_tapOut(&(d->tdelay), d->delays[i]);
	}
}

void tDelayExt_setDelay(tDelayExt* const dlext, uint32_t* delays){
	_tDelayExt* d = *dlext;
//	_tDelay* dt = &(d->tdelay);
	tDelay_setDelay(&(d->tdelay), delays[0]);
	for (int i = 0; i < d->numPoint; i++){
	    	d->delays[i] = delays[i];
	    }
}

void tDelayExt_setNumPoint(tDelayExt* const dlext, int numPoint){
	_tDelayExt* d = *dlext;
	uint32_t* t = &(d->tdelay);
	d->delays = (uint32_t *) malloc(sizeof(uint32_t) * numPoint);
	memcpy( &(d->tdelay), t, ((numPoint < d->numPoint) ? numPoint:d->numPoint) * sizeof(uint32_t));
	d->numPoint = numPoint;
	free(t);
}

//==============================================================================

   /*!
    * you know you will write some comments one day, right
    */
//
//void    tTapeDelayExt_initToPool   (tTapeDelayExt* const dlext, uint32_t* delays, uint32_t maxDelay, uint32_t numPoint, tMempool* const mp)
//{
////	_tMempool* m = *mp;
//    _tTapeDelayExt* d = *dlext = (_tTapeDelayExt*) malloc(sizeof(_tTapeDelayExt));
//
//    tTapeDelay_initToPool(&(d->tdelay), delays[0], maxDelay, mp);
//    d->numPoint = numPoint;
//    d->delays = (uint32_t *) malloc(sizeof(uint32_t) * numPoint);
//    d->lastOuts = (Lfloat *) malloc(sizeof(Lfloat) * numPoint);
//
//    for (int i = 0; i < numPoint; i++){
//    	d->delays[i] = delays[i];
//    	d->lastOuts[i] = 0.0f;
//    }
//
//}
//
//void tDelayExt_free (tDelayExt* const dlext){
//	_tDelayExt* d = *dlext;
//	_tDelay* dt = d->tdelay;
//	mpool_free((char*) dt->buff, dt->mempool);
//	mpool_free((char*) dt, dt->mempool);
//	free(d);
//}
//
//void tDelayExt_clear (tDelayExt* const dlext){
//	_tDelayExt* d = *dlext;
////	_tDelay* dt = &(d->tdelay);
//	for (unsigned i = 0; i < (d->tdelay)->maxDelay; i++) (d->tdelay)->buff[i] = 0;
//}
//
//void tDelayExt_tick(tDelayExt* const dlext, Lfloat input){
//	_tDelayExt* d = *dlext;
////	_tDelay* dt = (d->tdelay);
//	tDelay_tick(&(d->tdelay), input);
//	d->lastOuts[0] = (d->tdelay)->lastOut;
//
//	for(int i = 1; i < d->numPoint; i++){
//		d->lastOuts[i] = tDelay_tapOut(&(d->tdelay), d->delays[i]);
//	}
//}
//
//void tDelayExt_setDelay(tDelayExt* const dlext, uint32_t* delays){
//	_tDelayExt* d = *dlext;
////	_tDelay* dt = &(d->tdelay);
//	tDelay_setDelay(&(d->tdelay), delays[0]);
//	for (int i = 0; i < d->numPoint; i++){
//	    	d->delays[i] = delays[i];
//	    }
//}
