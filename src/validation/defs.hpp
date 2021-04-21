#ifndef AP_TEST_VALIDATION_DEFS
#define AP_TEST_VALIDATION_DEFS

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <sstream>
#include <ap/ap_int.h>
#include <boost/multiprecision/cpp_int.hpp>
#include "../common/convert.hpp"
#include "construct.hpp"

template <typename _Int_ap, typename _Int_boost, std::size_t _Max_hex_digits>
struct test_config
{
    using ap_t = _Int_ap;
    using boost_t = _Int_boost;
    static constexpr std::size_t max_hex_digits = _Max_hex_digits;
};


struct test_case_data
{
    std::string expected;
    std::string actual;
    std::vector<std::string> params;

    ::testing::AssertionResult check() const
    {
        if (this->expected == this->actual)
        {
            return ::testing::AssertionSuccess();
        }
        else
        {
            std::stringstream sstr;
            sstr << "\nExpected: " << this->expected
                 << "\nActual: " << this->actual;
            for (std::size_t i = 0; i < this->params.size(); ++i)
            {
                sstr << "\nparam[" << i << "] = " << this->params[i];
            }
            return ::testing::AssertionFailure() << sstr.str() << '\n';
        }
    }
};


constexpr std::size_t bit_size_cap = 4096; 
using signed_boost_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<bit_size_cap, bit_size_cap, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void> >;
using unsigned_boost_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<bit_size_cap, bit_size_cap, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void> >;
using ap_fixed_t = ap::int_f<bit_size_cap / __CHAR_BIT__>;
using ap_dynamic_t = ap::int_d;

using test_suite_signed = testing::Types<
test_config<ap_dynamic_t, signed_boost_t, bit_size_cap / 4>,
test_config<ap_fixed_t, signed_boost_t, bit_size_cap / 4>
>;

using test_suite_unsigned = testing::Types<
test_config<ap_dynamic_t, unsigned_boost_t, bit_size_cap / 4>,
test_config<ap_fixed_t, unsigned_boost_t, bit_size_cap / 4>
>;

template <typename _Config>
struct test_case_signed : public testing::Test
{
    test_case_data data;
    static constexpr bool is_signed = true;
};

template <typename _Config>
struct test_case_unsigned : public testing::Test
{
    test_case_data data;
    static constexpr bool is_signed = false;
};


TYPED_TEST_SUITE(test_case_signed, test_suite_signed);
TYPED_TEST_SUITE(test_case_unsigned, test_suite_unsigned);

#endif
