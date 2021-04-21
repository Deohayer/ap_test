#ifndef AP_TEST_VALIDATION_CONSTRUCT
#define AP_TEST_VALIDATION_CONSTRUCT

#include "../common/int_builder.hpp"
#include <ap/ap_int.h>

using construct_val = std::string (*)(std::size_t, bool);

// Min size two, max size one digit less than quarter, randomly filled
inline std::string construct_tiny(std::size_t max_size, bool is_negative)
{
    int_builder b;
    return b.set_base(digit_base::hex)
        .set_min_digits(2)
        .set_max_digits(std::max(max_size / 4 - 1, std::size_t(2)))
        .set_negative(is_negative)
        .build();
}

// Min size quarter, max size one digit less than half, randomly filled
inline std::string construct_large(std::size_t max_size, bool is_negative)
{
    int_builder b;
    return b.set_base(digit_base::hex)
        .set_min_digits(max_size / 4)
        .set_max_digits(std::max(max_size / 2 - 1, std::size_t(max_size / 4)))
        .set_negative(is_negative)
        .build();
}

// Size is exactly half minus 1, all ones
inline std::string construct_edge(std::size_t max_size, bool is_negative)
{
    int_builder b;
    return b.set_base(digit_base::hex)
        .set_num_digits(max_size / 2 - 1)
        .set_negative(is_negative)
        .build();
}

// Size is exactly half, randomly filled
inline std::string construct_half(std::size_t max_size, bool is_negative)
{
    int_builder b;
    return b.set_base(digit_base::hex)
        .set_num_digits(max_size / 2)
        .set_negative(is_negative)
        .build();
}

// Size is exactly max, randomly filled
inline std::string construct_full(std::size_t max_size, bool is_negative)
{
    int_builder b;
    return b.set_base(digit_base::hex)
        .set_num_digits(max_size)
        .set_negative(is_negative)
        .build();
}

// Size is exactly max, all ones
inline std::string construct_max(std::size_t max_size, bool is_negative)
{
    int_builder b;
    return b.set_base(digit_base::hex)
        .set_num_digits(max_size)
        .set_negative(is_negative)
        .build();
}

// Size is exactly double max
inline std::string construct_segfault(std::size_t max_size, bool is_negative)
{
    int_builder b;
    return b.set_base(digit_base::hex)
        .set_num_digits(max_size * 2)
        .set_negative(is_negative)
        .build();
}


// Size is exactly one ap::digit_t, randomly filled
inline std::string construct_digit(std::size_t max_size, bool is_negative)
{
    int_builder b;
    std::string result;
    
    do 
    {
        result = b.set_base(digit_base::hex)
        .set_num_digits(ap::AP_BYTES_PER_DIGIT * 2)
        .set_negative(is_negative)
        .build();
    } while (result == "0x0");

    return result;
}

// Size is exactly one ap::digit_t, all ones
inline std::string construct_digit_max(std::size_t max_size, bool is_negative)
{
    return std::string("0x") + std::string(ap::AP_BYTES_PER_DIGIT * 2, 'f');
}

// Zero
inline std::string construct_zero(std::size_t max_size, bool is_negative)
{
    return "0x0";
}

// One
inline std::string construct_one(std::size_t max_size, bool is_negative)
{
    int_builder b;
    return "0x1";
}

#endif