// // g++ -O3 -DN=4 matmul_3d.cpp -o matmul_3d.out && sudo /usr/lib/linux-tools/5.4.0-149-generic/perf stat -e task-clock,cycles,instructions,cache-references,cache-misses -d ./matmul_3d.out

#include<bits/stdc++.h>
using namespace std;

# ifndef N
#define N 4
# endif

void multiply(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2, vector<vector<int>>& res) {
   int n = mat1.size();
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         res[i][j] = 0;
         for (int k = 0; k < n; k++)
            res[i][j] += mat1[i][k] * mat2[k][j];
      }
   }
}

int main() {
   srand(time(0));
   vector<vector<int>> mat1(N, vector<int>(N));
   vector<vector<int>> mat2(N, vector<int>(N));

   for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         mat1[i][j] = rand() % 10000;
         mat2[i][j] = rand() % 10000;
      }
   }

   vector<vector<int>> res(N, vector<int>(N)); 

   multiply(mat1, mat2, res);

   // for (int i = 0; i < N; i++) {
   //    for (int j = 0; j < N; j++)
   //       cout << res[i][j] << " ";
   //    cout << "\n";
   // }

   return 0;
}
