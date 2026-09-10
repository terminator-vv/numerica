#pragma once

#include "numerica_vector.h"

class Probability {
public:
	static long long factorial(int n);
	
	static long long permutations(int n, int r);
	static long long combinations(int n, int r);

	static double probability(int favorable, int total);
	static double complement(double probability);
	static double additionRule(double pA, double pB, double pAB);
	static double multiplicationRule(double pA, double pBgivenA);

	static double conditionalProbability(int intersection, int condition);

	static double bayes(double pBgivenA, double pA, double pB);
};