#ifndef AP_TEST_MEASUREMENT_CONSTRUCT
#define AP_TEST_MEASUREMENT_CONSTRUCT

#include "../common/int_builder.hpp"
#include <ap/ap_int.h>

inline std::string construct(std::size_t size)
{
    int_builder b;
    return b.set_base(digit_base::hex)
        .set_num_digits(size)
        .build();
}

#endif
