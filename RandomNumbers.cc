#include <random>

#include "RandomNumbers.h"

using namespace std;

RandomNumbers::RandomNumbers() {
  random_device rd;
  engine = mt19937(rd());
  integer_dist = uniform_int_distribution<int>(1, 10);
  real_dist = uniform_real_distribution<double>(0.0, 1.0);
}

RandomNumbers::RandomNumbers(
    int integer_low, int integer_high, 
    double real_low, double real_high) {
  random_device rd;
  engine = mt19937(rd());
  integer_dist = uniform_int_distribution<int>(integer_low, integer_high);
  real_dist = uniform_real_distribution<double>(real_low, real_high);
}

RandomNumbers::~RandomNumbers() {
}

int RandomNumbers::generate_uniform_integer() { 
  return integer_dist(engine); 
}

double RandomNumbers::generate_uniform_real() { 
  return real_dist(engine); 
}
