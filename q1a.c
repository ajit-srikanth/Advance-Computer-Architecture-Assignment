#include <stdio.h>

float dot_product(float* v1, float* v2, int n){
	float dot_product = 0.0f;

	for(int i=0;i<n;i++){
	 dot_product += v1[i] * v2[i];	
	}

	return dot_product;
}



int main() {
    float vector1[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
    float vector2[] = {16.0f, 15.0f, 14.0f, 13.0f, 12.0f, 11.0f, 10.0f, 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f,
1.0f};
    printf("dot product: %.2f\n", dot_product(vector1, vector2, 16));
    return 0;
}
