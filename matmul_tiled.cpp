// g++ -O3 -DTILE_SIZE=16 -DN=512 matmul_tiled.cpp -o matmul_tiled.out && sudo /usr/lib/linux-tools/5.4.0-149-generic/perf stat -e task-clock,cycles,instructions,cache-references,cache-misses -d ./matmul_tiled.out
# include<bits/stdc++.h>
using namespace std;

# ifndef TILE_SIZE
# define TILE_SIZE 16
# endif

# ifndef N
#define N 2048
# endif

void multiply_tiled(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size();
    for (int i = 0; i < n; i += TILE_SIZE) {
        for (int j = 0; j < n; j += TILE_SIZE) {
            for (int k = 0; k < n; k += TILE_SIZE) {
                
                for (int ii = i; ii < min(i + TILE_SIZE, n); ++ii)
                    for (int jj = j; jj < min(j + TILE_SIZE, n); ++jj)
                        for (int kk = k; kk < min(k + TILE_SIZE, n); ++kk)
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
            }
        }
    }
}

int main() {
    srand(time(0));
    vector<vector<int>> A(N, vector<int>(N));
    vector<vector<int>> B(N, vector<int>(N));
    vector<vector<int>> res(N, vector<int>(N));


    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         A[i][j] = rand() % 10000;
         B[i][j] = rand() % 10000;
      }
   }

    // A * B = C
    multiply_tiled(A, B, res);

    
//    for (int i = 0; i < N; i++) {
//       for (int j = 0; j < N; j++)
//          cout << res[i][j] << " ";
//       cout << "\n";
//    }


    return 0;
}
