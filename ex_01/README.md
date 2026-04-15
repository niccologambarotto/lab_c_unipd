# C language exercises (Dati e Algoritmi per Ingegneria Elettronica, UniPD)

This repository contains six small C exercises about audio synthesis and audio processing.
The code is written to stay close to basic C99 syntax and the standard library.

The only vendored dependency is [`libs/tinywav/`](./libs/tinywav), which is used to read and write `.wav` files.
Everything else lives in the repository root as plain C source files.

# git

To obtain a local copy copy of this repository, this is the command:

```sh
$ git clone <repository>
```

So in this case:

```sh
$ git clone https://github.com/Morpheu5/DatiEAlgoritmi_C_Lab.git
```

This creates a directory called `DatiEAlgoritmi_C_Lab` in the current working directory. To check the current directory, `pwd` is the command to use:

```sh
$ pwd
/home/username
``` 

## Files

- `ex01_sine.c`: write a sine wave to a WAV file
- `ex02_additive.c`: use a small `struct Oscillator` for additive synthesis
- `ex03_malloc_buffer.c`: allocate an audio buffer with `malloc` and free it
- `ex04_saturation.c`: read a WAV file and apply `tanh` saturation
- `ex05_effect_chain.c`: chain effects with function pointers
- `ex06_dft_csv.c`: compute a spectrum with a provided naive DFT and write a CSV file
- `dft.c` and `dft.h`: a tiny DFT helper used only by exercise 6
- `sample_input.wav`: shared mono input file for the processing and DFT exercises

## Build

You can build each exercise directly with `cc`:

```sh
cc -std=c99 -Wall -Wextra -pedantic ex01_sine.c libs/tinywav/tinywav.c -lm -o ex01_sine
cc -std=c99 -Wall -Wextra -pedantic ex02_additive.c libs/tinywav/tinywav.c -lm -o ex02_additive
cc -std=c99 -Wall -Wextra -pedantic ex03_malloc_buffer.c libs/tinywav/tinywav.c -lm -o ex03_malloc_buffer
cc -std=c99 -Wall -Wextra -pedantic ex04_saturation.c libs/tinywav/tinywav.c -lm -o ex04_saturation
cc -std=c99 -Wall -Wextra -pedantic ex05_effect_chain.c libs/tinywav/tinywav.c -lm -o ex05_effect_chain
cc -std=c99 -Wall -Wextra -pedantic ex06_dft_csv.c dft.c libs/tinywav/tinywav.c -lm -o ex06_dft_csv
```

There is also a top-level `Makefile`:

```sh
$ make
$ ./bin/ex01_sine
$ # ...
```
