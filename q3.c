# include<stdlib.h>
# include<stdio.h>
# include<time.h>
# include <sys/mman.h>


int main(){
    int i, j , n = 4000;
    srand(time(0));
    float *A = (float *)malloc(n * sizeof(float));
    float *X = (float *)malloc(n * sizeof(float));
    // float **B = (float **)malloc(n * sizeof(float *));
    // for (i = 0; i < n; ++i) {
    //     B[i] = (float *)malloc(n * sizeof(float));
    // }
     float **B = (float **)mmap(NULL, n * sizeof(float *), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (B == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    for (i = 0; i < n; ++i) {
        B[i] = (float *)mmap(NULL, n * sizeof(float), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        if (B[i] == MAP_FAILED) {
            perror("mmap");
            return 1;
        }
    }

    if (A == NULL || X == NULL || B == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }


    for (i = 0; i < n; i++){
         X[i] = rand() / 10000;

        for (j = 0; j < n; j++)
            B[i][j] = rand() / 1000;

    }

    for (i = 0; i < n - 1; i++) {
        S1: A[i] = 0;
        for (j = 1; j < n - 1; j++)
            S2: A[i] += 0.33*(B[i][j] * X[j]);
    }


    return 0;
}