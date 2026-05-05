/*
Exercise 4: read a WAV file and apply tanh saturation.

Goal:
- Read sample_input.wav, process the samples, and write a new WAV file.

Concepts:
- reading with tinywav
- malloc and free
- loops over sample buffers
- math functions

Build:
- cc -std=c99 -Wall -Wextra -pedantic ex04_saturation.c libs/tinywav/tinywav.c -lm -o ex04_saturation

Run:
- ./ex04_saturation

Input:
- sample_input.wav

Output:
- ex04_saturation.wav
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "libs/tinywav/tinywav.h"

int main(void)
{
	TinyWav input_wav;
	TinyWav output_wav;
	float *samples;
	int num_frames;
	int sample_rate;
	int i;

	if (tinywav_open_read(&input_wav, "sample_input.wav", TW_INLINE) != 0) 
	{
		fprintf(stderr, "Could not open sample_input.wav.\n");
		return 1;
	}

	if (input_wav.numChannels != 1) 
	{
		fprintf(stderr, "This exercise expects a mono input file.\n");
		tinywav_close_read(&input_wav);
		return 1;
	}

	num_frames = input_wav.numFramesInHeader;
	sample_rate = (int) input_wav.h.SampleRate;
	samples = (float *) malloc((size_t) num_frames * sizeof(float));
	if (samples == NULL) 
	{
		fprintf(stderr, "malloc failed.\n");
		tinywav_close_read(&input_wav);
		return 1;
	}

	tinywav_read_f(&input_wav, samples, num_frames);
	tinywav_close_read(&input_wav);
	
	//1. Use a loop that visits all samples from index 0 to `num_frames - 1`.
	for(i = 0; i < num_frames; i++)
	{
		samples[i] = tanhf(samples[i] * 3.0f);
	}
	
  /*
  CHANGEME:
  Process the audio samples in place.

  What your code should do:
  1. Use a loop that visits all samples from index 0 to `num_frames - 1`.
  2. For each sample, apply a saturation function based on `tanhf(...)`.
  3. Multiply the input sample by 3.0 before passing it to `tanhf(...)`.
  4. Store the processed value back into the same position of the array.

  In other words, this exercise modifies the existing buffer instead of creating
  a second buffer.

  After you get it working, compare this nonlinear effect with a plain gain change.
  */

  if (tinywav_open_write(&output_wav, 1, sample_rate, TW_FLOAT32, TW_INLINE, "ex04_saturation.wav") != 0) {
    fprintf(stderr, "Could not open ex04_saturation.wav for writing.\n");
    free(samples);
    return 1;
  }

  tinywav_write_f(&output_wav, samples, num_frames);
  tinywav_close_write(&output_wav);

  free(samples);
  printf("Wrote ex04_saturation.wav\n");
  return 0;
}
