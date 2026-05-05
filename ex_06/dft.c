#define M_PI 3.14159265358979323846
#include <math.h>
#include "dft.h"

void dft_real_magnitude(
    const float *input,
    int size,
    float sample_rate,
    float *frequencies,
    float *magnitudes)
{
  int k;
  const float two_pi = 2.0f * (float) M_PI;

  for (k = 0; k <= size / 2; ++k) {
    float real_part = 0.0f;
    float imag_part = 0.0f;
    int n;

    frequencies[k] = ((float) k * sample_rate) / (float) size;

    for (n = 0; n < size; ++n) {
      float angle = two_pi * (float) k * (float) n / (float) size;
      real_part += input[n] * cosf(angle);
      imag_part -= input[n] * sinf(angle);
    }

    magnitudes[k] = sqrtf(real_part * real_part + imag_part * imag_part);
  }
}
