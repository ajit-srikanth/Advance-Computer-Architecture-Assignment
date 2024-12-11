// https://codearcana.com/posts/2013/05/18/achieving-maximum-memory-bandwidth.html

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>
#include <time.h>


#define SAMPLES 25
#define TIMES 10
#define BYTES_PER_GB (1024*1024*1024LL)
#define SIZE (1*BYTES_PER_GB)
#define PAGE_SIZE (1<<12)


#define NANOS_PER_SECF 1000000000.0
#define USECS_PER_SEC 1000000


double monotonic_time() {
    struct timespec time;
    // Note: Make sure to link with -lrt to define clock_gettime.
    clock_gettime(CLOCK_MONOTONIC, &time);
    return ((double) time.tv_sec) + ((double) time.tv_nsec / (NANOS_PER_SECF));
  }


// Have PAGE_SIZE buffering so we don't have to do math for prefetching.
char array[SIZE + PAGE_SIZE] ;

// Compute the bandwidth in GiB/s.
static inline double to_bw(size_t bytes, double secs) {
  double size_bytes = (double) bytes;
  double size_gb = size_bytes / ((double) BYTES_PER_GB);
  return size_gb / secs;
}


// Time a function, printing out time to perform the memory operation and the computed memory bandwidth.
#define timefun(f) timeit(f, #f)
void timeit(void (*function)(void*, size_t), char* name) {
  double min = INFINITY;
  size_t i;
  for (i = 0; i < SAMPLES; i++) {
    double before, after, total;

    before = monotonic_time();
    int j;
    for (j = 0; j < TIMES; j++) {
      function(array, SIZE);
    }
    after = monotonic_time();

    total = after - before;
    if (total < min) {
      min = total;
    }
  }

  printf("%32s: %5.2f GiB/s\n", name, to_bw(SIZE * TIMES, min));
}


void write_memory_rep_stosq(void* buffer, size_t size) {
  asm("cld\n"
      "rep stosq"
      : : "D" (buffer), "c" (size / 8), "a" (0) );
}


int main() {
  memset(array, 0xFF, SIZE);  // un-ZFOD the page.
  * ((uint64_t *) &array[SIZE]) = 0;

  // TODO(awreece) iopl(0) and cli/sti?

  timefun(write_memory_rep_stosq);

  return 0;
}



