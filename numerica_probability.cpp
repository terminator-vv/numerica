#include "numerica_probability.h"

long long Probability::factorial(int n) {
	if (n < 0) {
		throw std::invalid_argument("Factorials cannot be determined for negative integers.");
	}
	else if (n == 0) {
		return 1;
	}

	return n * factorial(n - 1);

}

long long Probability::permutations(int n, int r) {

	if (n < 0 || r < 0 || r > n) {
		throw std::invalid_argument("Invalid values for n and r.");
	}

	return Probability::factorial(n) / Probability::factorial(n - r);
}

long long Probability::combinations(int n, int r) {

	if (n < 0 || r < 0 || r > n) {
		throw std::invalid_argument("Invalid values for n and r.");
	}

	return Probability::factorial(n) / (Probability::factorial(r) * Probability::factorial(n - r));
}

double Probability::probability(int favorable, int total) {
	if (total <= 0) {
		throw std::invalid_argument("Total outcomes must be positive.");
	}

	if (favorable < 0 || favorable > total) {
		throw std::invalid_argument("Favorable outcomes must be between 0 and total outcomes.");
	}

	return static_cast<double>(favorable) / total;
}

double Probability::complement(double probability) {

	if (probability < 0 || probability > 1) {
		throw std::invalid_argument("Probablility must be between 0 and 1.");
	}

	return 1 - probability;
}

double Probability::additionRule(double pA, double pB, double pAB) {

	if (pA < 0 || pA > 1 || pB < 0 || pB > 1 || pAB < 0 || pAB > 1) {
		throw std::invalid_argument("Probabilities must be between 0 and 1.");
	}

	return pA + pB - pAB;
}

double Probability::multiplicationRule(double pA, double pBgivenA) {
	if (pA < 0 || pA > 1 || pBgivenA < 0 || pBgivenA > 1) {
		throw std::invalid_argument("Probabilities must be between 0 and 1.");
	}

	return pA * pBgivenA;
}

double Probability::conditionalProbability(int intersection, int condition) {
	if (condition <= 0) {
		throw std::invalid_argument("Condition outcomes must be positive.");
	}

	if (intersection < 0 || intersection > condition) {
		throw std::invalid_argument("Intersection outcomes must be between 0 and condition outcomes");
	}

	return static_cast<double>(intersection) / condition;
}

double Probability::bayes(double pBgivenA, double pA, double pB) {
	if (pBgivenA < 0 || pBgivenA > 1 || pA < 0 || pA > 1 || pB < 0 || pB > 1) {
		throw std::invalid_argument("Probabilities must be between 0 and 1.");
	}

	if (pB == 0) {
		throw std::invalid_argument("Probability of B must be positive");
	}

	return (pBgivenA * pA) / pB; 
}

