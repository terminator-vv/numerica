#include "numerica_vector.h"

Vector::Vector(std::initializer_list<double> values) {
	for (double value : values) {
		data.push_back(value);
	}
}

int Vector::size() const {
	return data.size();
}

double& Vector::operator[](int index) {
	return data[index];
}

const double& Vector::operator[](int index) const {
	return data[index];
}

Vector Vector::operator+(const Vector& other) const {
	Vector result{};
	
	if (size() != other.size()) {
		throw std::invalid_argument("Vectors must be of the same size for addition.");
	}

	for (int i = 0; i < size(); i++) {
		result.data.push_back(data[i] + other.data[i]);
	}
	return result;
}

Vector Vector::operator-(const Vector& other) const {
	Vector result{};

	if (size() != other.size()) {
		throw std::invalid_argument("Vectors must be of the same size for subtraction.");
	}
	for (int i = 0; i < size(); i++) {
		result.data.push_back(data[i] - other.data[i]);
	}
	return result;
}

Vector Vector::operator*(double scalar) const {
	Vector result{};
	for (double val : data) {
		result.data.push_back(val * scalar);
	}
	return result; 
}

double Vector::dot(const Vector& other) const {
	if (size() != other.size()) {
		throw std::invalid_argument("Vectors must be of the same size for dot product.");
	}

	Vector result{};
	for (int i = 0; i < size(); i++) {
		result.data.push_back(data[i] * other.data[i]);
	}

	double sum = 0;
	for (double val : result.data) {
		sum += val;
	}

	return sum; 
}

double Vector::magnitude() const {
	double mag = 0;
	double temp = 0;
	for (double val : data) {
		temp = std::pow(val, 2);
		mag += temp;
	}
	return std::sqrt(mag);
}

Vector Vector::cross(const Vector& other) const {
	if (size() != 3 || other.size() != 3) {
		throw std::invalid_argument("Cross product is only defined for 3D vectors.");
	}

	double x = data[1] * other.data[2] - data[2] * other.data[1];
	double y = data[2] * other.data[0] - data[0] * other.data[2];
	double z = data[0] * other.data[1] - data[1] * other.data[0];

	return Vector{x, y, z};
}