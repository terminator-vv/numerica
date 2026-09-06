#pragma once

#include <vector>
#include <stdexcept>
#include <initializer_list>
#include <utility>
#include <algorithm>
#include <cmath>
#include "numerica_vector.h"

class Statistics {

public: 
	static double mean(const Vector& data);
	static double median(const Vector& data);
	static double populationVariance(const Vector& data);
	static double sampleVariance(const Vector& data);
	static double standardDeviation(const Vector& data);

	static double populationCovariance(const Vector& x, const Vector& y);
	static double sampleCovariance(const Vector& x, const Vector& y);
	static double correlationCoefficient(const Vector& x, const Vector& y);
	static double coefficientOfDetermination(const Vector& x, const Vector& y);
};