#ifndef AP_TEST_UTILS_RNG
#define AP_TEST_UTILS_RNG

#include <random>

template <typename T>
class rng
{
public:
    rng(T min, T max) : min(min), max(max)
    {
        this->reset_distribution();
    }

    void set_min(T min)
    {
        this->min = min;
        this->reset_distribution();
    }

    void set_max(T max)
    {
        this->max = max;
        this->reset_distribution();
    }

    T get() const
    {
        return this->distribution(this->engine);
    }

private:
    T min;
    T max;
    mutable std::random_device entropy;
    mutable std::default_random_engine engine;
    mutable std::uniform_int_distribution<T> distribution;
    
    void reset_distribution() const
    {
        if (this->min <= this->max)
        {
            this->engine.seed(this->entropy());
            this->distribution = std::uniform_int_distribution<T>(this->min, this->max);
        }
    }
};

#endif
