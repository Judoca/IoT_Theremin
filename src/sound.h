// sound.h

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define __TIMESPEC_DEFINED
#define _USE_MATH_DEFINES

#include    <time.h>
#undef TIMESPEC
#include    <alsa/asoundlib.h>
#include    <math.h>
#include    <unistd.h>
#include    <stdio.h>

// Constants
#define SAMPLE_RATE 44100
#define AMPLITUDE 0.5

float   get_frequency(float distance);  // Obtain frequency from distance

void    play_sound(float frequency, float duratio); // Generate and play
                                                    // sin wave

