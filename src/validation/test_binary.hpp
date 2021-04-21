#ifndef AP_TEST_VALIDATION_TEST_BINARY
#define AP_TEST_VALIDATION_TEST_BINARY

#include "defs.hpp"

static const construct_val binary_rgens[] = {
    construct_digit_max,
    construct_digit,
    construct_tiny,
    construct_large,
    construct_edge,
    construct_zero,
    construct_one};

static const construct_val binary_lgens[] = {
    construct_digit_max,
    construct_digit,
    construct_tiny,
    construct_large,
    construct_edge,
    construct_zero,
    construct_one,
    construct_segfault,
    construct_half,
    construct_full,
    construct_max};

#define AP_BINARY_TEST_CASE_FULL(r_type, op, test_case_type, test_case_name)                                                                  \
    TYPED_TEST(test_case_type, test_case_name)                                                                                                \
    {                                                                                                                                         \
        const std::size_t left_hex_cap = TypeParam::max_hex_digits;                                                                           \
        const std::size_t right_hex_cap = bit_size_cap / 4;                                                                                   \
        constexpr std::size_t unsafe_index = 7; /* construct_segfault in binary_lgens */                                                      \
        typename TypeParam::ap_t ap_left;                                                                                                     \
        r_type ap_right;                                                                                                                      \
        typename TypeParam::boost_t boost_left;                                                                                               \
        typename TypeParam::boost_t boost_right;                                                                                              \
        test_case_data data;                                                                                                                  \
        data.params.resize(2);                                                                                                                \
        bool passed = true;                                                                                                                   \
        for (int r_sign = 0; r_sign <= int(this->is_signed); ++r_sign)                                                                        \
        {                                                                                                                                     \
            for (int l_sign = 0; l_sign <= int(this->is_signed); ++l_sign)                                                                    \
            {                                                                                                                                 \
                for (std::size_t i = 0; i < (sizeof(binary_rgens) / sizeof(&binary_rgens[0])); ++i)                                           \
                {                                                                                                                             \
                    data.params[1] = binary_rgens[i](right_hex_cap, r_sign);                                                                  \
                    for (std::size_t j = 0; j < (sizeof(binary_lgens) / sizeof(&binary_lgens[0])); ++j)                                       \
                    {                                                                                                                         \
                        passed = true;                                                                                                        \
                        data.params[0] = binary_lgens[j](left_hex_cap, l_sign);                                                               \
                        ap_right = convert::str<r_type, convert::ap_tag>::from(data.params[1]);                                               \
                        ap_left = convert::str<typename TypeParam::ap_t, convert::ap_tag>::from(data.params[0]);                              \
                        if (j < unsafe_index)                                                                                                 \
                        {                                                                                                                     \
                            boost_left = convert::str<typename TypeParam::boost_t, convert::boost_tag>::from(data.params[0]);                 \
                            boost_right = convert::str<typename TypeParam::boost_t, convert::boost_tag>::from(data.params[1]);                \
                            try                                                                                                               \
                            {                                                                                                                 \
                                data.actual = convert::str<decltype(ap_left op ap_right), convert::ap_tag>::to(ap_left op ap_right);          \
                                data.expected = convert::str<typename TypeParam::boost_t, convert::boost_tag>::to(boost_left op boost_right); \
                            }                                                                                                                 \
                            catch (int val)                                                                                                   \
                            {                                                                                                                 \
                                passed = (val == 0);                                                                                          \
                                EXPECT_EQ(val, 0);                                                                                            \
                            }                                                                                                                 \
                            catch (...)                                                                                                       \
                            {                                                                                                                 \
                                for (int s = 0; s < data.params.size(); ++s)                                                                  \
                                {                                                                                                             \
                                    std::cout << "params[" << s << "] = " << data.params[s] << '\n';                                          \
                                }                                                                                                             \
                                passed = false;                                                                                               \
                            }                                                                                                                 \
                                                                                                                                              \
                            EXPECT_TRUE(passed && (passed || data.check()));                                                                  \
                        }                                                                                                                     \
                        else                                                                                                                  \
                        {                                                                                                                     \
                            try                                                                                                               \
                            {                                                                                                                 \
                                data.actual = convert::str<decltype(ap_left op ap_right), convert::ap_tag>::to(ap_left op ap_right);          \
                                data.expected = convert::str<typename TypeParam::boost_t, convert::boost_tag>::to(boost_left op boost_right); \
                            }                                                                                                                 \
                            catch (int val)                                                                                                   \
                            {                                                                                                                 \
                                passed = (val == 0);                                                                                          \
                                EXPECT_EQ(val, 0);                                                                                            \
                            }                                                                                                                 \
                            catch (...)                                                                                                       \
                            {                                                                                                                 \
                                for (int s = 0; s < data.params.size(); ++s)                                                                  \
                                {                                                                                                             \
                                    std::cout << "params[" << s << "] = " << data.params[s] << '\n';                                          \
                                }                                                                                                             \
                                passed = false;                                                                                               \
                            }                                                                                                                 \
                            EXPECT_TRUE(passed && (passed || data.check()));                                                                  \
                        }                                                                                                                     \
                    }                                                                                                                         \
                }                                                                                                                             \
            }                                                                                                                                 \
        }                                                                                                                                     \
    }

#define AP_BINARY_TEST_CASE(op, test_case_type, test_case_name)                           \
    AP_BINARY_TEST_CASE_FULL(ap_dynamic_t, op, test_case_type, test_case_name##_rdynamic) \
    AP_BINARY_TEST_CASE_FULL(ap_fixed_t, op, test_case_type, test_case_name##_rfixed)

#endif
