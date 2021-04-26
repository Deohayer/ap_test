#ifndef AP_TEST_MEASUREMENT_DEFS
#define AP_TEST_MEASUREMENT_DEFS

#include "../common/convert.hpp"
#include "construct.hpp"
#include <ap/ap_int.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <gtest/gtest.h>
#include <iomanip>
#include <iostream>
#include <time_metric/time_metric.hpp>

static constexpr std::size_t LOOP_COUNT = 50000;

static inline void print_result(std::size_t size, unsigned long long int ap_result, unsigned long long int boost_result)
{
    static constexpr std::size_t column_width = 20;
    ap_result /= 1000;
    boost_result /= 1000;
    double ap_val = ap_result;
    double boost_val = boost_result;
    std::cout << '|' << std::setw(column_width) << "Size"
              << '|' << std::setw(column_width) << "AP"
              << '|' << std::setw(column_width) << "Boost"
              << '|' << std::setw(column_width) << "AP / Boost"
              << '|' << '\n';
    std::cout << '|' << std::setw(column_width) << size
              << '|' << std::setw(column_width) << ap_result
              << '|' << std::setw(column_width) << boost_result
              << '|' << std::setw(column_width) << std::fixed << std::setprecision(4) << (ap_val) / (boost_val)
              << '|' << '\n';
}

template <std::size_t _Bits>
using boost_f = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<_Bits, _Bits, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void> >;

template <std::size_t _Bits>
using ap_f = ap::int_f<_Bits / 8>;

template <std::size_t _Left_size>
struct test_config_fixed
{
    static constexpr std::size_t left_size = _Left_size;
    using ap_t = ap_f<left_size>;
    using boost_t = boost_f<left_size>;
};

template <std::size_t _Left_size>
struct test_config_dynamic
{
    using ap_t = ap::int_d;
    using boost_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<> >;
    static constexpr std::size_t left_size = _Left_size;
};

template <typename _Config>
struct test_case : public testing::Test
{
    typename _Config::ap_t ap_left;
    typename _Config::ap_t ap_right;
    typename _Config::ap_t ap_result;
    typename _Config::boost_t boost_left;
    typename _Config::boost_t boost_right;
    typename _Config::boost_t boost_result;
    std::string left;
    std::string right;

    void gen_left(std::size_t bit_size)
    {
        this->left = construct(bit_size / 4);
        this->ap_left = this->left;
        this->boost_left.assign(this->left);
    }

    void gen_right(std::size_t bit_size)
    {
        this->right = construct(bit_size / 4);
        this->ap_right = this->right;
        this->boost_right.assign(this->right);
    }
};

template <typename _Config>
struct test_case_fixed : public test_case<_Config>
{
};

template <typename _Config>
struct test_case_dynamic : public test_case<_Config>
{
};

using test_suite_fixed = testing::Types<
test_config_fixed<128>,
test_config_fixed<256>,
test_config_fixed<512>,
test_config_fixed<1024>,
test_config_fixed<5120>,
test_config_fixed<10240>
>;

using test_suite_dynamic = testing::Types<
test_config_dynamic<128>,
test_config_dynamic<256>,
test_config_dynamic<512>,
test_config_dynamic<1024>,
test_config_dynamic<5120>,
test_config_dynamic<10240>
>;

TYPED_TEST_SUITE(test_case_fixed, test_suite_fixed);
TYPED_TEST_SUITE(test_case_dynamic, test_suite_dynamic);

#endif
