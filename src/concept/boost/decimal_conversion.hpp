#ifndef AP_TEST_CONCEPT_BOOST_DECIMAL_CONVERSION
#define AP_TEST_CONCEPT_BOOST_DECIMAL_CONVERSION

#include "../decimal_conversion.hpp"
#include "family.hpp"

template <typename T>
class decimal_conversion<T, boost_family_int>
{
public:
    T from_decimal(const std::string& value) = delete;

    std::string to_decimal(const T& value) = delete;
};


#endif
