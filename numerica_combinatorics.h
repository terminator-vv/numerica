#pragma once

#include "numerica_probability.h"

class Combinatorics {
public: 
    static long long derangements(int n);
    static long long multisetPermutations(const Vector& counts);
    static long long catalanNumber(int n);
};