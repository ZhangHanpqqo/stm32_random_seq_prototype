This is the most up-to-date version for the project of MUS267. New features will be keep adding to the repo.

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


