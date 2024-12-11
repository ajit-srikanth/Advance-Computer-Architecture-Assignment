#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include <time.h>

#define N 1000000000

float add(float a, float b) {
    return a + b;
}

int main() {
    float *data = (float *)malloc(N * sizeof(float));
    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize data
    for (int i = 0; i < N; ++i) {
        data[i] = (float)i;
    }

    // Perform vectorized floating-point operations using Intel Intrinsics
    __m256 sum = _mm256_setzero_ps();
    for (int i = 0; i < N; i += 8) {
        __m256 a = _mm256_loadu_ps(&data[i]);
        sum = _mm256_add_ps(sum, a);
    }

    // Store the result
    float result[8];
    _mm256_storeu_ps(result, sum);

    float final_sum = 0.0;
    for (int i = 0; i < 8; ++i) {
        final_sum = add(final_sum, result[i]);
    }
    printf("Sum: %f\n", final_sum);

    free(data);

    return 0;
}

