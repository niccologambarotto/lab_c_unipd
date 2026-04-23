/*
Exercise 3: allocate an audio buffer with malloc.

Goal:
- Allocate a buffer on the heap, fill it with audio samples, write it, and free it.

Concepts:
- malloc
- free
- NULL checks
- pointer indexing

Build:
- cc -std=c99 -Wall -Wextra -pedantic ex03_malloc_buffer.c libs/tinywav/tinywav.c -lm -o ex03_malloc_buffer

Run:
- ./ex03_malloc_buffer

Output:
- ex03_malloc_buffer.wav
*/

#define M_PI 3.14159265358979323846
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "libs/tinywav/tinywav.h"

int main(void)
{
  const int sample_rate = 48000;
  const float duration_seconds = 2.0f;
  const int num_frames = (int) (duration_seconds * (float) sample_rate);
  const float frequency = 330.0f;
  const float amplitude = 0.25f;
  const float two_pi = 2.0f * (float) M_PI;
  float *samples = NULL;
  TinyWav wav;
  int i;
  samples = (float*) malloc(num_frames * sizeof(float));
  /*
  CHANGEME:
  Allocate memory for the audio buffer and store the address in `samples`.

  What your code should do:
  1. Call `malloc(...)`.
  2. Request enough memory for `num_frames` elements of type `float`.
  3. Convert the returned pointer to `float *`.
  4. Store the result in `samples`.

  In other words, you need space for the whole signal, not just one sample.
  */
 
  if (samples == NULL) {
    fprintf(stderr, "malloc failed.\n");
    return 1;
  }

  for (i = 0; i < num_frames; ++i) {
    float time = (float) i / (float) sample_rate;

    /* TODO: try changing the envelope so the sound fades in or fades out differently. */
    float envelope = 1.0f - (time / duration_seconds);
    samples[i] = amplitude * envelope * sinf(two_pi * frequency * time);
  }

  if (tinywav_open_write(&wav, 1, sample_rate, TW_FLOAT32, TW_INLINE, "ex03_malloc_buffer.wav") != 0) {
    fprintf(stderr, "Could not open ex03_malloc_buffer.wav for writing.\n");
    free(samples);
    return 1;
  }

  tinywav_write_f(&wav, samples, num_frames);
  tinywav_close_write(&wav);

  free(samples);
  printf("Wrote ex03_malloc_buffer.wav\n");
  return 0;
}
