#pragma once

#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <cmath>

class Vector {
private: 
	std::vector<double> data;
public:
	Vector(std::initializer_list<double> init); // constructor
	Vector(int size); // empty vector of given size
	int size() const; // returns size 
	double& operator[] (int index); // allows for input and changing the vector
	const double& operator[] (int index) const; // allows for input for constant vectors

	// actual math
	Vector operator+(const Vector& other) const;
	Vector operator-(const Vector& other) const;
	Vector operator*(double scalar) const; // scalar multiplication

	double dot(const Vector& other) const; // dot product
	double magnitude() const; // magnitude  
	Vector cross(const Vector& other) const; // cross product

};