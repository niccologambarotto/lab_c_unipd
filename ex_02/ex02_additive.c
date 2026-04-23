/*
Exercise 2: additive synthesis with a struct.

Goal:
- Use several oscillators and add their outputs together.

Concepts:
- struct definitions
- pointers to structs
- simple functions
- loops

Build:
- cc -std=c99 -Wall -Wextra -pedantic ex02_additive.c libs/tinywav/tinywav.c -lm -o ex02_additive

Run:
- ./ex02_additive

Output:
- ex02_additive.wav
*/
#define M_PI 3.14159265358979323846
#include <math.h>
#include <stdio.h>
#include "libs/tinywav/tinywav.h"

typedef struct Oscillator {
  float phase;
  float frequency;
  float amplitude;
  float sample_rate;
} Oscillator;

float oscillator_next(Oscillator *osc)
{
	float sample = osc->amplitude * sinf(osc->phase);
	// 1. Increase `osc->phase` by one step. The step depends on frequency and sample rate.
	float step = 2 * M_PI * osc->frequency / osc->sample_rate;
	osc->phase += step;
	// 3. If the phase becomes greater than or equal to one full turn (`2 * pi`), subtract one full turn so that the phase stays in a small range.
	if(osc->phase > 2 * M_PI)
	{ osc->phase -= 2 * M_PI;}
	return sample;
}

int main(void)
{
	const int sample_rate = 48000;
	const int num_frames = sample_rate;
	float samples[480];
	TinyWav wav;
	Oscillator oscillators[3];
	//int frame_index;

  /*
  Initialize all three oscillators.

  One example is already given below for oscillator 0.
  Use the same pattern for oscillators 1 and 2.
  Give them different frequencies and amplitudes so that the final sound
  is the sum of three sine waves.

  Example:
  oscillators[0].phase = 0.0f;
  oscillators[0].frequency = 220.0f;
  oscillators[0].amplitude = 0.30f;
  oscillators[0].sample_rate = (float) sample_rate;

  Suggested values:
  - oscillator 1: frequency 440 Hz, amplitude 0.15
  - oscillator 2: frequency 660 Hz, amplitude 0.10
  */
	// Oscillator 0
	oscillators[0].phase = 0.0f;
	oscillators[0].frequency = 440.0f;
	oscillators[0].amplitude = 0.30f;
	oscillators[0].sample_rate = (float) sample_rate;
	// Oscillator 1
	oscillators[1].phase = 0.0f;
	oscillators[1].frequency = 220.0f;
	oscillators[1].amplitude = 0.15;
	oscillators[1].sample_rate = (float) sample_rate;
	// Oscillator 2
	oscillators[2].phase = 0.0f;
	oscillators[2].frequency = 660.0f;
	oscillators[2].amplitude = 0.10;
	oscillators[2].sample_rate = (float) sample_rate;
	
	if (tinywav_open_write(&wav, 1, sample_rate, TW_FLOAT32, TW_INLINE, "ex02_additive.wav") != 0) 
	{
		fprintf(stderr, "Could not open ex02_additive.wav for writing.\n");
		return 1;
	}
	
	for(int i = 0; i < num_frames; i = i + 480)
	{
		// 1. Process the full signal in blocks of 480 samples, as in exercise 1.
     		int block_size;
     		// 2. Compute the correct block size, especially for the last block.
     		if((num_frames - i) < 480)
     		{
     			block_size = num_frames - i;
     		}
		else {block_size = 480;} 
		
		/* 3. For each sample in the block:
		     - start from `sample = 0.0f`
		     - call `oscillator_next(&oscillators[j])` for each of the three oscillators
		     - add the three values together
		     - store the result in `samples[i]`*/
		for(int j = 0; j < block_size; j++)
		{
			samples[j] = oscillator_next(&oscillators[0]) + oscillator_next(&oscillators[1]) + oscillator_next(&oscillators[2]);
		}
		
		//4. After filling a block, write it with `tinywav_write_f(...)`.
		tinywav_write_f(&wav, samples, block_size);
	}
  /*
  Write the main synthesis loop here.

  What your code should do:
  1. Process the full signal in blocks of 480 samples, as in exercise 1.
  2. Compute the correct block size, especially for the last block.
  3. For each sample in the block:
     - start from `sample = 0.0f`
     - call `oscillator_next(&oscillators[j])` for each of the three oscillators
     - add the three values together
     - store the result in `samples[i]`
  4. After filling one block, write it with `tinywav_write_f(...)`.

  The important idea is that additive synthesis means:
  final sample = oscillator 0 + oscillator 1 + oscillator 2
  */

  tinywav_close_write(&wav);
  printf("Wrote ex02_additive.wav\n");
  return 0;
}
