#ifndef AP_TEST_UTILS_INT_BUILDER
#define AP_TEST_UTILS_INT_BUILDER

#include <string>
#include "rng.hpp"
#include "digit.hpp"


class int_builder
{
public:
    int_builder();

    int_builder(unsigned int min_digits, unsigned int max_digits, bool is_negative = false);

    int_builder& set_min_digits(unsigned int value);

    int_builder& set_max_digits(unsigned int value);

    int_builder& set_num_digits(unsigned int value);

    int_builder& set_negative(bool is_negative);

    int_builder& set_prefixed(bool is_prefixed);

    int_builder& set_base(digit_base dbase);

    int_builder& set_case(digit_case dbase);

    std::string build() const;

private:
    digit_base dbase;
    digit_case dcase;
    bool is_prefixed;
    bool is_negative;
    rng<unsigned int> generator;
};

#endif
