#ifndef DFT_H
#define DFT_H

void dft_real_magnitude(
    const float *input,
    int size,
    float sample_rate,
    float *frequencies,
    float *magnitudes);

#endif
