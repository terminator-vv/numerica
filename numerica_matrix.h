#pragma once

#include <vector>
#include <stdexcept>
#include <initializer_list>
#include <utility>
#include "numerica_vector.h"

class Matrix {
private: 
	std::vector<std::vector<double>> data;
public:
	Matrix(std::initializer_list<std::vector<double>> values);
	Matrix(int row, int col);
	int rows() const; int cols() const; // construction

	double& operator()(int row, int col);
	const double& operator()(int row, int col) const; 
	void swapRows(int row1, int row2); // access

	// basic math
	Matrix operator+(const Matrix& other) const;
	Matrix operator-(const Matrix& other) const;
	Matrix operator*(double scalar) const; // scalar multiplication

	// advanced math
	Vector operator*(const Vector& other) const; // matrix-vector multiplication
	Matrix operator*(const Matrix& other) const; // matrix-matrix multiplication
	Matrix transpose() const;

	// linear algebra
	double trace() const; // sum of diagonal elements
	double determinant() const; // determinant of the matrix
	Matrix minor(int row, int col) const;
	double cofactor(int row, int col) const; 
	static Matrix identity(int size);
	Matrix augment(const Matrix& other) const;
	Matrix inverse() const; // inverse of the matrix

	// row reduction and solving
	Matrix rowEchelon() const;
	Matrix reducedRowEchelon() const;
	Vector solve(const Vector& b) const;
};