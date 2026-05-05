/*
Exercise 5: build a small effect chain with function pointers.

Goal:
- Apply more than one effect to the same input signal.

Concepts:
- function pointers
- small context structs
- arrays of structs
- processing samples in sequence

Build:
- cc -std=c99 -Wall -Wextra -pedantic ex05_effect_chain.c libs/tinywav/tinywav.c -lm -o ex05_effect_chain

Run:
- ./ex05_effect_chain

Input:
- sample_input.wav

Output:
- ex05_effect_chain.wav
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "libs/tinywav/tinywav.h"

typedef float (*EffectFn)(float in, void *ctx);

typedef struct EffectStage {
  EffectFn fn;
  void *ctx;
} EffectStage;

typedef struct SaturationContext {
  float drive;
} SaturationContext;

typedef struct BitCrusherContext {
  int steps;
} BitCrusherContext;

float saturation(float in, void *ctx)
{
  /*
  CHANGEME:
  Implement this effect function.

  What your code should do:
  1. Convert `ctx` to a pointer to `SaturationContext`.
  2. Read the `drive` value from that struct.
  3. Return a saturated version of the input sample `in`.
  4. Use the same idea as in exercise 4:
     multiply the input by the drive, then pass the result to `tanhf(...)`.

  Look at `bitcrusher(...)` to see how a context pointer is used.
  */

  (void) ctx; // <- ignore this, it's just to suppress warnings until you implement the code, and you can remove it later.
  return in;
}

float bitcrusher(float in, void *ctx)
{
  BitCrusherContext *bitcrusher_ctx = (BitCrusherContext *) ctx;
  float scaled = in * (float) bitcrusher_ctx->steps;
  float rounded = roundf(scaled);

  return rounded / (float) bitcrusher_ctx->steps;
}

float process_chain(float in, EffectStage *stages, int num_stages)
{
  float sample = in;
  int i;

  /*
  CHANGEME:
  Apply all effects in order.

  What your code should do:
  1. Use a loop from 0 to `num_stages - 1`.
  2. At each step, call the function stored in `stages[i].fn`.
  3. Pass two arguments to that function:
     - the current value of `sample`
     - the context pointer `stages[i].ctx`
  4. Store the returned value back into `sample`.

  This means the output of one effect becomes the input of the next one.
  */

  return sample;
}

int main(void)
{
  TinyWav input_wav;
  TinyWav output_wav;
  float *samples;
  int num_frames;
  int sample_rate;
  int i;
  SaturationContext saturation_ctx;
  BitCrusherContext bitcrusher_ctx;
  EffectStage stages[2];

  if (tinywav_open_read(&input_wav, "sample_input.wav", TW_INLINE) != 0) {
    fprintf(stderr, "Could not open sample_input.wav.\n");
    return 1;
  }

  if (input_wav.numChannels != 1) {
    fprintf(stderr, "This exercise expects a mono input file.\n");
    tinywav_close_read(&input_wav);
    return 1;
  }

  num_frames = input_wav.numFramesInHeader;
  sample_rate = (int) input_wav.h.SampleRate;
  samples = (float *) malloc((size_t) num_frames * sizeof(float));
  if (samples == NULL) {
    fprintf(stderr, "malloc failed.\n");
    tinywav_close_read(&input_wav);
    return 1;
  }

  tinywav_read_f(&input_wav, samples, num_frames);
  tinywav_close_read(&input_wav);

  /*
  CHANGEME:
  Set up the effect contexts, build the chain, and process the samples.

  What your code should do:
  1. Give a value to `saturation_ctx.drive`.
     A good starting point is 2.5.
  2. Give a value to `bitcrusher_ctx.steps`.
     A good starting point is 16.
  3. Fill the `stages` array:
     - one stage should use the `saturation` function with `&saturation_ctx`
     - one stage should use the `bitcrusher` function with `&bitcrusher_ctx`
  4. Loop over all samples in the buffer.
  5. For each sample, call `process_chain(...)` and store the result back into `samples[i]`.

  Suggested experiment:
  After the program works, swap the order of the two effects and listen to the difference.
  */

  if (tinywav_open_write(&output_wav, 1, sample_rate, TW_FLOAT32, TW_INLINE, "ex05_effect_chain.wav") != 0) {
    fprintf(stderr, "Could not open ex05_effect_chain.wav for writing.\n");
    free(samples);
    return 1;
  }

  tinywav_write_f(&output_wav, samples, num_frames);
  tinywav_close_write(&output_wav);

  free(samples);
  printf("Wrote ex05_effect_chain.wav\n");
  return 0;
}
