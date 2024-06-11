This is the most up-to-date version for the project of MUS267. New features will be keep adding to the repo.

This is a multitap delay effect with the number of delay taps and the rhythm tempo and amplitudes changable on the fly. The group delay time increases exponentially from 1 toa few seconds, so the sound effect is shifted between a filter with multiple zeros and a delay. The coeffecients of the transfer fucntion of the filter translates to the time and amplitude of the delay line. 

Control parameters:
Knob1 - PA7: Number of tabs
options are from 1 to 8

Knob2 - PA5: total delay length M
the delay time of the last tap bounded by a max delay time of 5 seconds

Knob3 and Knob4 - PA6 and PA4: delay line shape control
These two knobs together controls the position of a point(knob3 as x and knob4 as y) within the range of [1, M], (0, 2]. When the position is decided, it secures the shape of either a peak(connecting points (0, 1) and (M, 0)) when y is above 1, or a valley(connecting points (0, 1) and (M, 1)). The original sample sits at the start of this line with the amplitude of 1. The other taps all find their place and gain by evenly dividing the area beneath the line. It results in denser and louder ticks when the segnment of the shape is high, and sparser and weeker ticks when it's low, especially when it's under 1. 
 

///////////////////////// OUTDATED README FOR MUS267 HOMEWORK 2 (tag homework2) //////////////////////////

This is a audio processing project for Genera Experimenter prototype board with STM32H7 chip. Repo of the board: https://github.com/spiricom/Genera_Experimenter.

The main idea of the project is to control delay lines in a filter design fashion, or reversely implement filter with delay lines. The project aims for exploring the compatibility of the approach of transferfunction based filter design and delay-feedback based echo.

The current version is a all-pass style filter implemented with two delay lines. The tab output of the first delay line directly writes into the second one as the backward feedback.

Transfer function:
(alpha+(1-alpha)*c + (1-alpha) * z^(-n)) / (1 + (1 - alpha) * c * fb * z^(-m))
alpha is the mix parameter
c is the all-pass filter coef
n is the delay time for the audio input
m is the delay time for the feedback
fb is the gain of feedback

Five knobs and two buttons are used for the control.
PA7 - phase shift frequency of the all-pass filter
PA5 - mix, i.e. alpha
PA3 - n, not linear
PA2 - m, not linear
PA6 - fb

PA8 - delay sync, if PA8 is high, then the x and y delay will sync and are controled by n(PA3).
PD12 - mute


