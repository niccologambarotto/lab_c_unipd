CC = cc
CFLAGS = -std=c99 -Wall -Wextra -pedantic
LDFLAGS = -lm

BINS = \
	bin/ex01_sine \
	bin/ex02_additive \
	bin/ex03_malloc_buffer \
	bin/ex04_saturation \
	bin/ex05_effect_chain \
	bin/ex06_dft_csv

.PHONY: all clean

all: $(BINS)

bin:
	mkdir -p bin

bin/ex01_sine: ex01_sine.c libs/tinywav/tinywav.c libs/tinywav/tinywav.h | bin
	$(CC) $(CFLAGS) ex01_sine.c libs/tinywav/tinywav.c $(LDFLAGS) -o $@

bin/ex02_additive: ex02_additive.c libs/tinywav/tinywav.c libs/tinywav/tinywav.h | bin
	$(CC) $(CFLAGS) ex02_additive.c libs/tinywav/tinywav.c $(LDFLAGS) -o $@

bin/ex03_malloc_buffer: ex03_malloc_buffer.c libs/tinywav/tinywav.c libs/tinywav/tinywav.h | bin
	$(CC) $(CFLAGS) ex03_malloc_buffer.c libs/tinywav/tinywav.c $(LDFLAGS) -o $@

bin/ex04_saturation: ex04_saturation.c libs/tinywav/tinywav.c libs/tinywav/tinywav.h | bin
	$(CC) $(CFLAGS) ex04_saturation.c libs/tinywav/tinywav.c $(LDFLAGS) -o $@

bin/ex05_effect_chain: ex05_effect_chain.c libs/tinywav/tinywav.c libs/tinywav/tinywav.h | bin
	$(CC) $(CFLAGS) ex05_effect_chain.c libs/tinywav/tinywav.c $(LDFLAGS) -o $@

bin/ex06_dft_csv: ex06_dft_csv.c dft.c dft.h libs/tinywav/tinywav.c libs/tinywav/tinywav.h | bin
	$(CC) $(CFLAGS) ex06_dft_csv.c dft.c libs/tinywav/tinywav.c $(LDFLAGS) -o $@

clean:
	rm -rf bin
