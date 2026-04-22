/*
Exercise 1: write a sine wave to a WAV file.

Goal:
- Generate one second of a mono sine wave.

Concepts:
- constants
- loops
- arrays
- math functions from math.h
- calling functions from tinywav

Build:
- cc -std=c99 -Wall -Wextra -pedantic ex01_sine.c libs/tinywav/tinywav.c -lm -o ex01_sine

Run:
- ./ex01_sine

Output:
- ex01_sine.wav
*/

#define _GNU_SOURCE
#include <math.h>
#include <stdio.h>
#include "libs/tinywav/tinywav.h"

int main(void)
{
  const int sample_rate = 48000;
  const int num_frames = sample_rate;
  const float frequency = 440.0f;
  const float amplitude = 0.25f;
  const float two_pi = 2.0f * (float) M_PI;
  float samples[480];
  TinyWav wav;
  int frame_index;

  if (tinywav_open_write(&wav, 1, sample_rate, TW_FLOAT32, TW_INLINE, "ex01_sine.wav") != 0) {
    fprintf(stderr, "Could not open ex01_sine.wav for writing.\n");
    return 1;
  }
	// 1. Use a loop to process the full signal in blocks of 480 samples.
	for(int i = 0; i < num_frames; i = i + 480)
	{
		// 2. For each block, compute how many samples must be written.
     		// Usually this is 480, but the last block may be shorter.
     		int block_size;
     		if((num_frames - i) < 480)
     		{
     			block_size = num_frames - i;
     		}
		else {block_size = 480;} 
		
		// 3. Use another loop to fill the array `samples.
		for(int j = 0; j < block_size; j++)
		{
			int sample_index = i + j;
			// 5. Compute the sine wave sample, 6. Store the result in `samples[i]`.
			samples[j] = amplitude * sinf(two_pi * frequency * sample_index / sample_rate);
		}
		
		//7. After filling a block, write it with `tinywav_write_f(...)`.
		tinywav_write_f(&wav, samples, block_size);
	}
  /*
  CHANGEME:
  Write the main audio-generation part of the program here.

  What your code should do:
  1. Use a loop to process the full signal in blocks of 480 samples.
  2. For each block, compute how many samples must be written.
     Usually this is 480, but the last block may be shorter.
  3. Use another loop to fill the array `samples`.
  4. For each element `samples[i]`, compute its absolute index in the full signal:
     current_block_start + i
  5. Compute the sine wave sample as:

       amplitude * sinf(two_pi * frequency * sample_index / sample_rate)

  6. Store the result in `samples[i]`.
  7. After filling a block, write it with `tinywav_write_f(...)`.
  8. After all blocks have been written, execution will continue below and the file will be closed.
  */

  tinywav_close_write(&wav);
  printf("Wrote ex01_sine.wav\n");

  return 0;
}
