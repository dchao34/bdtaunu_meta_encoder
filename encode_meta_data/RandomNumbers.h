#ifndef __RANDOMNUMBERS_H__
#define __RANDOMNUMBERS_H__

#include <random>

/**
 * @brief 
 * Random number generator for meta data assignment. 
 *
 * @detail 
 * This class is a wrapper of C++ random number generators used 
 * to generate specific kinds of random numbers for meta data 
 * assignment. It generates two types of random numbers:
 *
 * + Uniform integers: Samples an integer in the range 
 *   [`integer_low`, `integer_high`] uniformly. 
 *
 * + Uniform reals: Samples a real number in the range 
 *   [`real_low`, `real_high`) uniformly. 
 *
 * The random number engine is the `mt19937`
 * [Mersenne twiser](http://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine) 
 * engine.
 *
 * The entropy source is supposedly a hardware based non-deterministic
 * source, but can apparently be implementation dependent. See 
 * [here](http://en.cppreference.com/w/cpp/numeric/random/random_device) 
 * for more details.
 *
 * Usage Example
 * -------------
 *
 *     // Initialize generator
 *     RandomNumbers rand(1, 10, 0.0, 1.0);
 *
 *     // Get random numbers
 *     int rand_i = rand.generate_uniform_integer();
 *     int rand_r = rand.generate_uniform_real();
 *
 */
class RandomNumbers {
  public: 

    //! Default construction preconfigured.
    /*! Preconfigured to: 
     * `integer_low = 1`, `integer_high = 10`, 
     * `real_low = 0.0`, `real_high = 1.0`. */
    RandomNumbers();

    //! Constructor to specify ranges manually. 
    RandomNumbers(int integer_low, int integer_high, 
                  double real_low, double real_high);

    ~RandomNumbers() = default;

    //! Generate a uniformly random integer in the specified range. 
    int generate_uniform_integer();

    //! Generate a uniformly random real in the specified range. 
    double generate_uniform_real();

  private:

    // Random number engine.
    std::mt19937 engine;

    // Probability distributions to generate. 
    std::uniform_int_distribution<int> integer_dist;
    std::uniform_real_distribution<double> real_dist;
};

#endif
