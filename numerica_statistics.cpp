#include "numerica_statistics.h"

double Statistics::mean(const Vector& data) {

    if (data.size() == 0) {
    throw std::invalid_argument("Cannot find mean of empty data.");
}

	double sum = 0;
	for (int i = 0; i < data.size(); i++) {
		sum += data[i];
	}

	return sum / data.size();
}

double Statistics::median(const Vector& data) {
    if (data.size() == 0) {
        throw std::invalid_argument("Cannot find median of empty data.");
    }

    std::vector<double> sortedData;

    for (int i = 0; i < data.size(); i++) {
        sortedData.push_back(data[i]);
    }

    std::sort(sortedData.begin(), sortedData.end());

    if (sortedData.size() % 2 == 1) {
        return sortedData[sortedData.size() / 2];
    }
    else {
        double a = sortedData[sortedData.size() / 2 - 1];
        double b = sortedData[sortedData.size() / 2];

        return (a + b) / 2;
    }
}

double Statistics::populationVariance(const Vector& data) {

    if (data.size() == 0) {
        throw std::invalid_argument("Cannot find population variance of empty data.");
    }

    double sum = 0; 
    double avg = Statistics::mean(data);
    for (int i = 0; i < data.size(); i++) {
        sum += std::pow(data[i] - avg, 2);
    }
    return sum / data.size();
}

double Statistics::sampleVariance(const Vector& data) {

    if (data.size() == 0) {
        throw std::invalid_argument("Cannot find sample variance of empty data.");
    }

    double sum = 0;
    double avg = Statistics::mean(data);
    for (int i = 0; i < data.size(); i++) {
        sum += std::pow(data[i] - avg, 2);
    }
    return sum / (data.size() - 1);
}

double Statistics::standardDeviation(const Vector& data) {

    if (data.size() == 0) {
        throw std::invalid_argument("Cannot find standard deviation of empty data.");
    }

    return std::sqrt(Statistics::populationVariance(data));
}

double Statistics::populationCovariance(const Vector& x, const Vector& y) {

    if (x.size() != y.size()) {
        throw std::invalid_argument("Vectors must have the same size.");
    }

    double sum = 0;
    double meanX = Statistics::mean(x);
    double meanY = Statistics::mean(y);

    for (int i = 0; i < x.size(); i++) {
        sum += (x[i] - meanX) * (y[i] - meanY);
    }

    return sum / x.size();
}

double Statistics::sampleCovariance(const Vector& x, const Vector& y) {

    if (x.size() != y.size()) {
        throw std::invalid_argument("Vectors must have the same size.");
    }

    double sum = 0;
    double meanX = Statistics::mean(x);
    double meanY = Statistics::mean(y);

    for (int i = 0; i < x.size(); i++) {
        sum += (x[i] - meanX) * (y[i] - meanY);
    }

    return sum / (x.size() - 1);
}

double Statistics::correlationCoefficient(const Vector& x, const Vector& y) {

    if (x.size() != y.size()) {
        throw std::invalid_argument("Vectors must have the same size.");
    }
    else if (x.size() == 0 || y.size() == 0) {
        throw std::invalid_argument("Cannot find correlation coefficient of empty data.");
    }

    double a = 0; 
    double b = 0; 
    double c = 0; 
    for (int i = 0; i < x.size(); i++) {
        a += x[i]; b += y[i];
        c += x[i] * y[i];
    }

    c = x.size() * c;
    c -= a * b;

    double d = 0; 
    double e = 0; 
    for (int i = 0; i < x.size(); i++) {
        d += std::pow(x[i], 2);
        e += std::pow(y[i], 2);
    }

    d = x.size() * d;
    e = x.size() * e;

    d -= std::pow(a, 2);
    e -= std::pow(b, 2);

    if (d == 0 || e == 0) {
        throw std::invalid_argument("Correlation is undefined for constant data.");
    }


    return c / std::sqrt(d * e);
}

double Statistics::coefficientOfDetermination(const Vector& x, const Vector& y) {

    if (x.size() != y.size()) {
        throw std::invalid_argument("Vectors must have the same size.");
    }
    else if (x.size() == 0 || y.size() == 0) {
        throw std::invalid_argument("Cannot find coefficient of determinaton of empty data.");
    }

    return std::pow(Statistics::correlationCoefficient(x, y), 2);
}