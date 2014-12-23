#ifndef __RANDOMNUMBERS_H__
#define __RANDOMNUMBERS_H__

#include <random>

class RandomNumbers {
  public: 
    RandomNumbers();
    RandomNumbers(int integer_low, int integer_high, 
                  double real_low, double real_high);
    ~RandomNumbers();

    int generate_uniform_integer();
    double generate_uniform_real();

  private:
    std::mt19937 engine;
    std::uniform_int_distribution<int> integer_dist;
    std::uniform_real_distribution<double> real_dist;
};

#endif
