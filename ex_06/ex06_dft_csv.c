/*
Exercise 6: use a provided DFT and export a CSV file.

Goal:
- Read a short WAV file, analyze one window of audio, and write a CSV file.

Concepts:
- using a helper library
- file I/O with stdio
- arrays
- simple spectral analysis

Build:
- cc -std=c99 -Wall -Wextra -pedantic ex06_dft_csv.c dft.c libs/tinywav/tinywav.c -lm -o ex06_dft_csv

Run:
- ./ex06_dft_csv

Input:
- sample_input.wav

Output:
- ex06_spectrum.csv
*/

#include <stdio.h>
#include <stdlib.h>
#include "dft.h"
#include "libs/tinywav/tinywav.h"

int main(void)
{
  const int window_size = 1024;
  const int num_bins = window_size / 2 + 1;
  TinyWav input_wav;
  float *samples;
  float *window;
  float *frequencies;
  float *magnitudes;
  FILE *csv_file;
  int num_frames;
  int i;

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
  if (num_frames < window_size) {
    fprintf(stderr, "The input file is too short for this exercise.\n");
    tinywav_close_read(&input_wav);
    return 1;
  }

  samples = (float *) malloc((size_t) num_frames * sizeof(float));
  window = (float *) malloc((size_t) window_size * sizeof(float));
  frequencies = (float *) malloc((size_t) num_bins * sizeof(float));
  magnitudes = (float *) malloc((size_t) num_bins * sizeof(float));
  if (samples == NULL || window == NULL || frequencies == NULL || magnitudes == NULL) {
    fprintf(stderr, "malloc failed.\n");
    free(samples);
    free(window);
    free(frequencies);
    free(magnitudes);
    tinywav_close_read(&input_wav);
    return 1;
  }

  tinywav_read_f(&input_wav, samples, num_frames);
  tinywav_close_read(&input_wav);

  /*
  CHANGEME:
  Prepare the input window and run the DFT.

  What your code should do:
  1. Use a loop from 0 to `window_size - 1`.
  2. Copy one sample at a time from `samples` into `window`.
     Start from index 0 for now, so the first window contains the first 1024 samples.
  3. After filling `window`, call `dft_real_magnitude(...)`.
  4. Pass:
     - `window`
     - `window_size`
     - the sample rate from the WAV file
     - `frequencies`
     - `magnitudes`

  Suggested experiment:
  After it works, try a different starting index for the window and compare the CSV output.
  */

  csv_file = fopen("ex06_spectrum.csv", "w");
  if (csv_file == NULL) {
    fprintf(stderr, "Could not open ex06_spectrum.csv for writing.\n");
    free(samples);
    free(window);
    free(frequencies);
    free(magnitudes);
    return 1;
  }

  /*
  CHANGEME:
  Write the spectrum data to the CSV file.

  What your code should do:
  1. Write the header line:
     frequency_hz,magnitude
  2. Use a loop from 0 to `num_bins - 1`.
  3. On each iteration, write one line with:
     - `frequencies[i]`
     - `magnitudes[i]`
  4. Separate the two values with a comma.

  Use `fprintf(...)` for both the header and the data lines.
  */

  fclose(csv_file);
  free(samples);
  free(window);
  free(frequencies);
  free(magnitudes);

  printf("Wrote ex06_spectrum.csv\n");
  return 0;
}
