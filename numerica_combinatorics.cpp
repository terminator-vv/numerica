#include "numerica_combinatorics.h"

long long Combinatorics::derangements(int n) {
    if (n < 0) {
        throw std::invalid_argument("Derangements cannot be determined for negative integers.");
    }

    if (n == 0) {
        return 1;
    }

    if (n == 1) {
        return 0;
    }

    return (n - 1) * (derangements(n - 1) + derangements(n - 2));
}

long long multisetPermutations(const Vector& counts) {
    if (counts.size() == 0) {
        throw std::invalid_argument("Vector may not be empty.");
    } 

    for (int i = 0; i < counts.size(); i++) {
        if (counts[i] <= 0) {
            throw std::invalid_argument("Counts may not be zero or lower.");
        } else if (counts[i] != std::floor(counts[i])) {
            throw std::invalid_argument("Non-integer counts are unacceptable.");
        }
    }

    long long numerator = 0;
    for (int i = 0; i < counts.size(); i++) {
        numerator += counts[i];
    }
    numerator = Probability::factorial(numerator);

    long long denominator = 1;
    for (int i = 0; i < counts.size(); i++) {
        denominator *= Probability::factorial(counts[i]);
    }

    return numerator / denominator; 

}

long long catalanNumber(int n) {

    if (n < 0) {
        throw std::invalid_argument("Input cannot be a negative number.");
    }

    return Probability::combinations(2 * n, n) / (n + 1);
}