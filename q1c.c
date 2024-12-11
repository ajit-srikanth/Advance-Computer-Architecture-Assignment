#include <stdio.h>
#include <x86intrin.h>   // most SIMD 

float dot_product_even(float* v1, float* v2, int n) {
    __m256 sum = _mm256_setzero_ps();  // Initialize sum to (0.0 ....)  256bits => 32 (for float) * 8
//    __m256 sum1 = _mm256_setzero_ps();
	
    int ctr = 0;
    for(int i = 0; i < n; i += 16) {
        __m256 a = _mm256_set_ps(v1[2*i+14], v1[2*i+12], v1[2*i+10], v1[2*i+8], v1[2*i+6], v1[2*i+4], v1[2*i+2], v1[2*i]);
        __m256 b = _mm256_set_ps(v2[2*i+14], v2[2*i+12], v2[2*i+10], v2[2*i+8], v2[2*i+6], v2[2*i+4], v2[2*i+2], v2[2*i]);

	__m256 prod = _mm256_mul_ps(a, b);
	sum = _mm256_add_ps(sum,prod);
    }

    //float dot_product[8];
    //_mm256_storeu_ps(dot_product, sum);
    
    //float total = 0.0f;
    //for (int i = 0; i < 8; ++i)
    //    total += dot_product[i];

    //return total;
    

    sum = _mm256_hadd_ps(sum, sum); // horizontal sum... to avoid using the 8 iet loop to add the partial sums commented above
    sum = _mm256_hadd_ps(sum, sum);

    float dot_product[8];
    _mm256_storeu_ps(dot_product, sum);

    return dot_product[0] + dot_product[4];
}

int main() {
    float vector1[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
    float vector2[] = {16.0f, 15.0f, 14.0f, 13.0f, 12.0f, 11.0f, 10.0f, 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    printf("dot product of even indices using vector instructions : %.2f\n", dot_product_even(vector1, vector2, 16));
    return 0;
}


