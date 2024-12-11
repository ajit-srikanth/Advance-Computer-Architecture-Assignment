// g++ -O3 -DN=4 matmul_recursive_strassen.cpp -o matmul_recursive_strassen.out && sudo /usr/lib/linux-tools/5.4.0-149-generic/perf stat -e task-clock,cycles,instructions,cache-references,cache-misses -d ./matmul_recursive_strassen.out

#include <bits/stdc++.h>
using namespace std;


# ifndef N
#define N 4
# endif

void print(vector<vector<int> > matrix) {
	for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}


vector<vector<int>> add(vector<vector<int> > A, vector<vector<int> > B, int split_index, int multiplier = 1) {
	for (auto i = 0; i < split_index; i++)
		for (auto j = 0; j < split_index; j++)
			A[i][j] = A[i][j] + (multiplier * B[i][j]);
	return A;
}

vector<vector<int> >
strassen_multiplication(vector<vector<int> > A, vector<vector<int> > B) {
	
	
	int col_1 = A[0].size();
	int row_1 = A.size();
	int col_2 = B[0].size();
	int row_2 = B.size();


	vector<int> result_row(col_2, 0);
	vector<vector<int> > result(row_1, result_row);

	// Base case 
	// if size of matrix is 1
	if (col_1 == 1)
		result[0][0]
			= A[0][0] * B[0][0];
	else {

		// split index
		int split_index = col_1 / 2;

		vector<int> row_vector(split_index, 0);

		// Splitting the matrices in sub matrices
		vector<vector<int> > a00(split_index, row_vector);
		vector<vector<int> > a01(split_index, row_vector);
		vector<vector<int> > a10(split_index, row_vector);
		vector<vector<int> > a11(split_index, row_vector);
		vector<vector<int> > b00(split_index, row_vector);
		vector<vector<int> > b01(split_index, row_vector);
		vector<vector<int> > b10(split_index, row_vector);
		vector<vector<int> > b11(split_index, row_vector);

		// calculating and storing the result
		// inside our quadrants
		for (auto i = 0; i < split_index; i++)
			for (auto j = 0; j < split_index; j++) {
				a00[i][j] = A[i][j];
				a01[i][j] = A[i][j + split_index];
				a10[i][j] = A[split_index + i][j];
				a11[i][j] = A[i + split_index]
									[j + split_index];
				b00[i][j] = B[i][j];
				b01[i][j] = B[i][j + split_index];
				b10[i][j] = B[split_index + i][j];
				b11[i][j] = B[i + split_index]
									[j + split_index];
			}

		// Calculating the multiplication using the formula
		// given by strassent algorithm
		vector<vector<int>> p1(
			strassen_multiplication(a00, add(b01, b11, split_index, -1))
		);
		vector<vector<int>> p2(
			strassen_multiplication(add(a00, a01, split_index), b11)
		);
		vector<vector<int>> p3(
			strassen_multiplication(add(a10, a11, split_index), b00)
		);
		vector<vector<int>> p4(
			strassen_multiplication(a11, add(b10, b00, split_index, -1))
		);
		vector<vector<int>> p5(
			strassen_multiplication(add(a00, a11, split_index),add(b00, b11, split_index))
		);
		vector<vector<int>> p6(
			strassen_multiplication(add(a01, a11, split_index, -1),add(b10, b11, split_index))
		);
		vector<vector<int>> p7(
			strassen_multiplication(
				add(a00, a10, split_index, -1),
				add(b00, b01, split_index)
			)
		);

		// calculating the result
		vector<vector<int> > result_00(
			add(add(add(p5, p4, split_index), p6, split_index), p2, split_index, -1)
		);
		vector<vector<int> > result_01(
			add(p1, p2, split_index)
		);
		vector<vector<int> > result_10(	
			add(p3, p4, split_index)
		);
		vector<vector<int> > result_11(
			add(add(add(p5, p1, split_index), p3, split_index, -1), p7, split_index, -1)
		);

		// calulating and storing the result
		// inside matrix
		for (auto i = 0; i < split_index; i++){
			for (auto j = 0; j < split_index; j++) {
				result[i][j] = result_00[i][j];
				result[i][j + split_index] = result_01[i][j];
				result[split_index + i][j] = result_10[i][j];
				result[i + split_index][j + split_index] = result_11[i][j];
			}
		}

		// clearing all the arrays
		a00.clear();
		a01.clear();
		a10.clear();
		a11.clear();
		b00.clear();
		b01.clear();
		b10.clear();
		b11.clear();
		p1.clear();
		p2.clear();
		p3.clear();
		p4.clear();
		p5.clear();
		p6.clear();
		p7.clear();
		result_00.clear();
		result_01.clear();
		result_10.clear();
		result_11.clear();
	}
	return result;
}

int main() {
    srand(time(0));
	vector<vector<int>> A(N, vector<int>(N));
    vector<vector<int>> B(N, vector<int>(N));

      for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         A[i][j] = rand() % 10000;
         B[i][j] = rand() % 10000;
      }
   }
    
	
	vector<vector<int> > result(strassen_multiplication(A, B));

	// print(result);
}