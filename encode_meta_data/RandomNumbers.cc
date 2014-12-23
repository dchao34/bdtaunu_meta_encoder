#include <random>

#include "RandomNumbers.h"

using namespace std;

// Preconfigure random generator to the following:
// `integer_low = 1`, `integer_high = 10`, 
// `real_low = 0.0`, and `real_high = 1.0`.
RandomNumbers::RandomNumbers() {

  // Construct the random engine and seed it with the entropy source. 
  random_device rd;
  engine = mt19937(rd());

  // Define the probability distributions to generate. 
  integer_dist = uniform_int_distribution<int>(1, 10);
  real_dist = uniform_real_distribution<double>(0.0, 1.0);
}

// Constructor for manually configuring the random generator.  
RandomNumbers::RandomNumbers(
    int integer_low, int integer_high, 
    double real_low, double real_high) {
  random_device rd;
  engine = mt19937(rd());
  integer_dist = uniform_int_distribution<int>(integer_low, integer_high);
  real_dist = uniform_real_distribution<double>(real_low, real_high);
}

// Generate a uniformly distributed integer within the constructed range.
int RandomNumbers::generate_uniform_integer() { 
  return integer_dist(engine); 
}

// Generate a uniformly distributed real within the constructed range.
double RandomNumbers::generate_uniform_real() { 
  return real_dist(engine); 
}
