#ifndef AP_TEST_UTILS_DIGIT
#define AP_TEST_UTILS_DIGIT

#include <string>

enum class digit_base
{
    bin = 2,
    oct = 8,
    dec = 10,
    hex = 16
};

enum class digit_case
{
    mixed,
    lower,
    upper
};


char get_digit(digit_base dbase, digit_case dcase);

const std::string& get_base_prefix(digit_base dbase);

#endif
