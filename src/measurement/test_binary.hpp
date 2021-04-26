#ifndef AP_TEST_MEASUREMENT_TEST_BINARY
#define AP_TEST_MEASUREMENT_TEST_BINARY

#include "defs.hpp"

#define AP_BINARY_TEST(op, test_case_type, test_case_name)                      \
    TYPED_TEST(test_case_type, test_case_name)                                  \
    {                                                                           \
        const std::vector<std::size_t> sizes = {                                \
            TypeParam::left_size / 8,                                           \
            TypeParam::left_size / 4,                                           \
            TypeParam::left_size / 2,                                           \
            TypeParam::left_size};                                              \
        unsigned long long int ap_time = 0;                                     \
        unsigned long long int boost_time = 0;                                  \
                                                                                \
        for (int i = 0; i < LOOP_COUNT; ++i)                                    \
        {                                                                       \
            for (int j = 0; j < sizes.size(); ++j)                              \
            {                                                                   \
                this->gen_left(TypeParam::left_size);                           \
                this->gen_right(sizes[j]);                                      \
                ap_time += measure_execution_time([&]() {                       \
                    this->ap_result = this->ap_left op this->ap_right;          \
                });                                                             \
                boost_time += measure_execution_time([&]() {                    \
                    this->boost_result = this->boost_left op this->boost_right; \
                });                                                             \
            }                                                                   \
        }                                                                       \
        print_result(TypeParam::left_size, ap_time, boost_time);                \
    }

#endif
