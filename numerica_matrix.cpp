#include "numerica_matrix.h"

Matrix::Matrix(std::initializer_list<std::vector<double>> values) {
	if (values.size() == 0) {
		throw std::invalid_argument("Matrix cannot be empty");
	}

	int expected_cols = values.begin()->size();
	if (expected_cols == 0) {
		throw std::invalid_argument("Matrix cannot have empty rows");
	}
		
	for (const std::vector<double>& row : values) {
		if (row.size() != expected_cols) {
			throw std::invalid_argument("All rows must have the same number of columns");
		}
		data.push_back(row);
	}
}

Matrix::Matrix(int row, int col) {
	if (row <= 0 || col <= 0) {
		throw std::invalid_argument("Matrix dimensions must be positive");
	}
	
	for (int i = 0; i < row; ++i) {
		data.push_back(std::vector<double>(col, 0.0));
	}
}

int Matrix::rows() const {
	return data.size();
}

int Matrix::cols() const {
	if (data.empty()) {
		return 0;
	}

	return data[0].size();
}

double& Matrix::operator() (int row, int col) {
	if (row < 0 || row >= rows() || col < 0 || col >= cols()) {
		throw std::out_of_range("Index out of range");
	}

	return data[row][col];
}

const double& Matrix::operator() (int row, int col) const {
	if (row < 0 || row >= rows() || col < 0 || col >= cols()) {
		throw std::out_of_range("Index out of range");
	}
	return data[row][col];
}

Matrix Matrix::operator+(const Matrix& other) const {
	if (rows() != other.rows() || cols() != other.cols()) {
		throw std::invalid_argument("Matrices must have the same dimensions for addition");
	}
	Matrix result(rows(), cols());
	
	for (int i = 0; i < rows(); ++i) {
		for (int j = 0; j < cols(); ++j) {
			result(i, j) = (*this)(i, j) + other(i, j);
		}
	}
	return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
	if (rows() != other.rows() || cols() != other.cols()) {
		throw std::invalid_argument("Matrices must have the same dimensions for subtraction");
	}
	Matrix result(rows(), cols());

	for (int i = 0; i < rows(); ++i) {
		for (int j = 0; j < cols(); ++j) {
			result(i, j) = (*this)(i, j) - other(i, j);
		}
	}
	return result;
}

Matrix Matrix::operator*(double scalar) const {
	Matrix result(rows(), cols());
	for (int i = 0; i < rows(); ++i) {
		for (int j = 0; j < cols(); ++j) {
			result(i, j) = (*this)(i, j) * scalar;
		}
	}
	return result;
}

Vector Matrix::operator*(const Vector& other) const {
	if (cols() != other.size()) {
		throw std::invalid_argument("Matrix columns must match vector size for multiplication");
	}

	Vector result(rows());

	for (int i = 0; i < rows(); i++) {
		double sum = 0.0;
		for (int j = 0; j < cols(); j++) {
			sum += (*this)(i, j) * other[j];
		}
		result[i] = sum; 
	}

	return result; 
}

Matrix Matrix::operator*(const Matrix& other) const {
	if (cols() != other.rows()) {
		throw std::invalid_argument("First matrix's total columns must match second matrix's total rows for multiplication.");
	}

	Matrix result(rows(), other.cols());
		for (int i = 0; i < rows(); i++) {
			for (int j = 0; j < other.cols(); j++) {
				double sum = 0;
				for (int k = 0; k < cols(); k++) {
					sum += (*this)(i, k) * other(k, j);
				}
				result(i, j) = sum;
			}
		}

		return result; 
}

Matrix Matrix::transpose() const {

	if (rows() == 0 || cols() == 0) {
		throw std::invalid_argument("Cannot transpose an empty matrix.");
	}

	Matrix result(cols(), rows());

	for (int j = 0; j < cols(); j++) {
		for (int i = 0; i < rows(); i++) {
			result(j, i) = (*this)(i, j);
		}
	}

	return result; 
}

double Matrix::trace() const {

	if (rows() != cols()) {
		throw std::invalid_argument("Trace cannot be determined for non-square matrices.");
	}

	double sum = 0; 
	for (int i = 0; i < rows(); i++) {
		sum += (*this)(i, i);
	}

	return sum; 
}

double Matrix::determinant() const {
	if (rows() != cols()) {
		throw std::invalid_argument("Determinant cannot be determined for non-square matrices.");
	}

	double determinant = 0; 
	if (rows() == 1) {
		determinant = (*this)(0, 0);
	}
	else if (rows() == 2) {
		determinant = (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
	}
	else {
		for (int j = 0; j < cols(); j++) {
			determinant += (*this)(0, j) * (*this).cofactor(0, j);
		}
	}

	return determinant;
}

Matrix Matrix::minor(int row, int col) const {

	if (row < 0 || row >= rows() || col < 0 || col >= cols()) {
		throw std::out_of_range("Neither can the row and column to be deleted be out of range.");
	}


	Matrix result(rows() - 1, cols() - 1);
	int resultRow = 0;
	for (int i = 0; i < rows(); i++) {
		if (i == row) {continue;}
		int resultCol = 0;

		for (int j = 0; j < cols(); j++) {
			if (j == col) { continue; }
			result(resultRow, resultCol) = (*this)(i, j);
			resultCol++;
		}
		resultRow++; 
	}
	return result;
}

double Matrix::cofactor(int row, int col) const {

	if (row < 0 || row >= rows() || col < 0 || col >= cols()) {
		throw std::out_of_range("Index out of range");
	}

	if (rows() == 1 && cols() == 1) {
		return 1;
	}

	Matrix Minor = (*this).minor(row, col);
	double det = Minor.determinant();
	if ((row + col) % 2 == 0) {
		return det; 
	}
	else {
		return -1 * det; 
	}

}

void Matrix::swapRows(int row1, int row2) {
	if (row1 < 0 || row1 >= rows() ||
		row2 < 0 || row2 >= rows()) {
		throw std::out_of_range("Row index out of range");
	}

	std::swap(data[row1], data[row2]);
}

Matrix Matrix::rowEchelon() const {
	Matrix result = *this;

	int pivotRow = 0;
	int pivotCol = 0;

	while (pivotRow < result.rows() && pivotCol < result.cols()) {

		int pivot = -1;

		for (int i = pivotRow; i < result.rows(); i++) {
			if (result(i, pivotCol) != 0) {
				pivot = i;
				break;
			}
		}

		if (pivot == -1) {
			pivotCol++;
			continue;
		}

		if (pivot != pivotRow) {
			result.swapRows(pivot, pivotRow);
		}

		for (int i = pivotRow + 1; i < result.rows(); i++) {
			double factor = result(i, pivotCol) / result(pivotRow, pivotCol);

			for (int j = pivotCol; j < result.cols(); j++) {
				result(i, j) -= factor * result(pivotRow, j);
			}
		}

		pivotRow++;
		pivotCol++;
	}

	return result;
}

Matrix Matrix::reducedRowEchelon() const {
	Matrix result = rowEchelon(); 

	for (int i = result.rows() - 1; i >= 0; i--) {

		int pivotCol = -1;

		for (int j = 0; j < result.cols(); j++) {
			if (result(i, j) != 0) {
				pivotCol = j;
				break;
			}
		}

		if (pivotCol == -1) {
			continue;
		}

		double pivotValue = result(i, pivotCol);

		for (int j = 0; j < result.cols(); j++) {
			result(i, j) /= pivotValue;
		}

		for (int k = 0; k < i; k++) {
			double factor = result(k, pivotCol);

			for (int j = 0; j < result.cols(); j++) {
				result(k, j) -= factor * result(i, j);
			}
		}
	}

	return result;
}

Matrix Matrix::identity(int size) {
	Matrix result(size, size);

	for (int i = 0; i < size; i++) {
		result(i, i) = 1;
	}
	return result;
}

Matrix Matrix::augment(const Matrix& other) const {
	if (rows() != other.rows()) {
		throw std::invalid_argument("Matrices must have the same number of rows for augmentation.");
	}

	Matrix result(rows(), cols() + other.cols());

	for (int i = 0; i < rows(); i++) {
		for (int j = 0; j < cols(); j++) {
			result(i, j) = (*this)(i, j);
		}
	}

	for (int i = 0; i < rows(); i++) {
		for (int j = 0; j < other.cols(); j++) {
			result(i, cols() + j) = (other)(i, j);
		}
	}

	return result; 
}

Matrix Matrix::inverse() const {
	if (rows() != cols()) {
		throw std::invalid_argument("Only square matrices can be inverted.");
	}

	Matrix identityMatrix = Matrix::identity(rows());
	Matrix augmented = augment(identityMatrix);
	Matrix rref = augmented.reducedRowEchelon();

	for (int i = 0; i < rows(); i++) {
		for (int j = 0; j < cols(); j++) {
			if (i == j) {
				if (rref(i, j) != 1) {
					throw std::invalid_argument("Matrix is singular and has no inverse.");
				}
			}
			else {
				if (rref(i, j) != 0) {
					throw std::invalid_argument("Matrix is singular and has no inverse.");
				}
			}
		}
	}

	Matrix result(rows(), cols());

	for (int i = 0; i < rows(); i++) {
		for (int j = 0; j < cols(); j++) {
			result(i, j) = rref(i, j + cols());
		}
	}

	return result;
}

Vector Matrix::solve(const Vector& b) const {
	if (rows() != cols()) {
		throw std::invalid_argument("Matrix must be square to solve this system.");
	}

	if (b.size() != rows()) {
		throw std::invalid_argument("Vector size must match the number of matrix rows.");
	}

	Matrix augmented(rows(), cols() + 1);

	for (int i = 0; i < rows(); i++) {
		for (int j = 0; j < cols(); j++) {
			augmented(i, j) = (*this)(i, j);
		}

		augmented(i, cols()) = b[i];
	}

	Matrix rref = augmented.reducedRowEchelon();

	for (int i = 0; i < rows(); i++) {
		for (int j = 0; j < cols(); j++) {
			if (i == j) {
				if (rref(i, j) != 1) {
					throw std::invalid_argument("System does not have a unique solution.");
				}
			}
			else {
				if (rref(i, j) != 0) {
					throw std::invalid_argument("System does not have a unique solution.");
				}
			}
		}
	}

	Vector result(rows());

	for (int i = 0; i < rows(); i++) {
		result[i] = rref(i, cols());
	}

	return result;
}