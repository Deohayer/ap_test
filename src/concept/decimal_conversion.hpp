#ifndef AP_TEST_CONCEPT_AP_DECIMAL_CONVERSION
#define AP_TEST_CONCEPT_AP_DECIMAL_CONVERSION

#include <string>

template <typename T, typename _Family>
class decimal_conversion
{
public:
    T from_decimal(const std::string& value) = delete;

    std::string to_decimal(const T& value) = delete;
};

#endif
