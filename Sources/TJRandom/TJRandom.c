// TJRandom - A Swift package for generating random numbers.
// Copyright (C) 2017  Tjienta Vara
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "TJRandom.h"
#include <immintrin.h>
#include <pthread.h>
#include <stdio.h>

static int TJRandom_cpuHasRdrnd(void) {
  uint32_t  regs[4];
  int       in_a = 1;
  int       in_c = 0;
  uint32_t  out_a;
  uint32_t  out_b;
  uint32_t  out_c;
  uint32_t  out_d;

    asm volatile
      ("cpuid" : "=a" (out_a), "=b" (out_b), "=c" (out_c), "=d" (out_d)
       : "a" (in_a), "c" (in_c));

    // Bit 30 or ECX says if rdrand exists.
    uint64_t mask = 1 << 30;
    return (out_c & mask) > 0;
}

#if defined(__RDRND__)
static void TJRandom_getUInt64Array_rdrand(uint64_t *values, size_t nrValues) {
    for (int i = 0; i < nrValues; i++) {
        int retryCount = 0;

        while (!_rdrand64_step(&values[i])) {
            if (retryCount++ >= 10) {
                fprintf(stderr, "_rdrand64_step failed after 10 retries.\n");
                abort();
            }
            _mm_pause();
        }
    }
}
#endif

#if defined(__APPLE__) && defined(__MACH__)
static void TJRandom_getUInt64Array_arc4random(uint64_t *values, size_t nrValues) {
    // Interestingly, this call no longer uses the RC4 algorithm.
    arc4random_buf(values, nrValues * sizeof (uint64_t));
}
#endif

#if defined(__gnu_linux__)
static void TJRandom_getUInt64Array_getrandom(uint64_t *values, size_t nrValues) {
retry:
    // On linux this will read data from the /dev/urandom pool, without using a file descriptor.
    // However this call will block if the /dev/urandom pool does not yet have enough entropy.
    if (getrandom(values, nrValues * sizeof (uint64_t), 0) == -1) {
        switch (errno) {
        case EAGAIN:
            goto retry;
        default:
            perror("Could not use getrandom()");
            abort();
        }
    }
}
#endif

void TJRandom_getUInt64Array(uint64_t *values, size_t nrValues) {
#if defined(__RDRND__)
    if (TJRandom_cpuHasRdrnd()) {
        return TJRandom_getUInt64Array_rdrand(values, nrValues);
    }
#endif

#if defined(__APPLE__) && defined(__MACH__)
    return TJRandom_getUInt64Array_arc4random(values, nrValues);
#elif defined(__gnu_linux__)
    return TJRandom_getUInt64Array_getrandom(values, nrValues);
#else
#warning "No good quality random number generator found."
    fprintf(stderr, "No good random number generator found.\n");
    abort();
#endif
}



