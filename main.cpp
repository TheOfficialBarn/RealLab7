#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Matrix {
public:
	int matrix_size;
	double** matrix_data;

	Matrix(int size = 0) : matrix_size(size) {
		matrix_data = new double*[matrix_size];
		for (int i = 0; i < matrix_size; i++) {
			matrix_data[i] = new double[matrix_size];
		}
	}


	Matrix& operator=(const Matrix& other) {
		if (this == &other) {
			return *this;
		}

		for (int i = 0; i < matrix_size; ++i) {
			delete[] matrix_data[i];
		}
		delete[] matrix_data;

		matrix_size = other.matrix_size;

		matrix_data = new double*[matrix_size];
		for (int i = 0; i < matrix_size; ++i) {
			matrix_data[i] = new double[matrix_size];
		for 	(int j = 0; j < matrix_size; ++j) {
				matrix_data[i][j] = other.matrix_data[i][j];
			}
		}

		return *this;
	}

	~Matrix() {
        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;
    }
};
void read_matrix_from_file(const string& file_name, Matrix& matrix_1, Matrix& matrix_2) {
	// TODO: Read matrix data from the file
	// Make sure to handle potential errors and invalid input
	ifstream file(file_name);
	int size;
	if (file.is_open()) {
		file >> size;
		matrix_1 = Matrix(size);
		matrix_2 = Matrix(size);

		for(int i=0; i<size; i++){
			for(int j=0; j<size; j++){
				file >> matrix_1.matrix_data[i][j];
			}
		}
		// Now we do for the second matrix
		for(int i=0; i<size; i++){
			for(int j=0; j<size; j++){
				file >> matrix_2.matrix_data[i][j];
			}
		}
		file.close();
	} else throw runtime_error("Unable to open file");
}
void print_matrix(const Matrix& matrix) {
    for(int i=0; i<matrix.matrix_size; i++) {
		for(int j=0; j <matrix.matrix_size; j++) {
			cout << matrix.matrix_data[i][j] << " ";
		}
		cout << endl;
	}
}
void print_matrix(const Matrix& matrix_1, const Matrix& matrix_2) {
    // TODO: Print both matrices to the console
	cout << "Matrix 1" << endl;
    for(int i=0; i<matrix_1.matrix_size; i++) {
		for(int j=0; j <matrix_1.matrix_size; j++) {
			cout << matrix_1.matrix_data[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Matrix 2" << endl;
    for(int i=0; i<matrix_2.matrix_size; i++) {
		for(int j=0; j <matrix_2.matrix_size; j++) {
			cout << matrix_2.matrix_data[i][j] << " ";
		}
		cout << endl;
	}
}
// Overloaded + operator for matrix addition
Matrix operator+(const Matrix& matrix_1, const Matrix& matrix_2) {
	// TODO: Implement matrix addition
	int size = matrix_1.matrix_size;
	Matrix matrix_3(size);
    for(int i=0; i<size; i++) {
		for(int j=0; j <size; j++) {
			matrix_3.matrix_data[i][j] = matrix_1.matrix_data[i][j] + matrix_2.matrix_data[i][j];
		}
	}
	return matrix_3;
}
// Overloaded * operator for matrix multiplication
Matrix operator*(const Matrix& matrix_1, const Matrix& matrix_2){
	// TODO: Implement matrix multiplication
	int size = matrix_1.matrix_size;
	double runningTotal=0;
	Matrix m3(size);
    for(int i=0; i<size; i++) {
		for(int j=0; j <size; j++) {
			runningTotal=0;
			for(int k=0; k < size; k++) {
				runningTotal += (matrix_1.matrix_data[i][k] * matrix_2.matrix_data[k][j]);
			}
			m3.matrix_data[i][j]=runningTotal;
		}
	}
	return m3;
	// Block i=0
	// (00 * 00) + (01 * 10) + (02 * 20) + (03 * 30) -> 00 j=0
	// (00 * 01) + (01 * 11) + (02 * 21) + (03 * 31) -> 01 j=1
	// (00 * 02) + (01 * 12) + (02 * 22) + (03 * 32) -> 02 j=2
	// (00 * 03) + (01 * 13) + (02 * 23) + (03 * 33) -> 03 j=3
	// ...Block i=1
	// ...Block i=2
	// ...Block i=3
}
Matrix add_matrices(const Matrix& matrix_1, const Matrix& matrix_2) {
	// TODO: Implement matrix addition
	int size = matrix_1.matrix_size;
	Matrix m3(size);
	m3 = matrix_1 + matrix_2;
	return m3;
}
Matrix multiply_matrices(const Matrix& matrix_1, const Matrix& matrix_2) {
	// TODO: Implement matrix multiplication
	int size = matrix_1.matrix_size;
	Matrix m3(size);
	m3 = matrix_1 * matrix_2;
	return m3;
}
void get_diagonal_sum(const Matrix& matrix) {
    // TODO: Calculate and print the sum of the diagonal elements
	int size = matrix.matrix_size;
	double sum=0;
	for(int i=0; i<size; i++){
		sum += matrix.matrix_data[i][i];
	}
	cout << "Sum of matrix: " << sum << endl;
}
void swap_matrix_row(Matrix& matrix, int row1, int row2) {
    // TODO: Swap the rows 'row1' and 'row2' in the matrix
    //    Handle invalid row indices

	if (row1 >= 0 && row1 < matrix.matrix_size && row2 >= 0 && row2 < matrix.matrix_size) {
		swap(matrix.matrix_data[row1], matrix.matrix_data[row2]); // std::swap() swaps two pointers
	} else {
		throw out_of_range("Invalid row indices");
	}
}
int main(int argc, char* argv[]) {
    Matrix matrix_1, matrix_2;
    read_matrix_from_file("matrix.txt", matrix_1, matrix_2);

    cout << "print_matrix" << endl;
    print_matrix(matrix_1, matrix_2);

    cout << "add_matrices result:" << endl;
    Matrix add_result_1 = add_matrices(matrix_1, matrix_2);
    Matrix add_result_2 = matrix_1 + matrix_2;
    print_matrix(add_result_1);
    print_matrix(add_result_2);

    cout << "multiply_matrices result:" << endl;
    Matrix multiply_result_1 = multiply_matrices(matrix_1, matrix_2);
    Matrix multiply_result_2 = matrix_1 * matrix_2;
    print_matrix(multiply_result_1);
    print_matrix(multiply_result_2);

    cout << "get matrix diagonal sum" << endl;
    get_diagonal_sum(matrix_1);

    cout << "swap matrix rows" << endl;
    swap_matrix_row(matrix_1, 0, 1);
	print_matrix(matrix_1);
    return 0;
}