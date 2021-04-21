#include "int_builder.hpp"
#include <limits>
#include <iostream>

int_builder::int_builder()
    : dbase(digit_base::dec),
      dcase(digit_case::lower),
      is_prefixed(true),
      is_negative(false),
      generator(1, std::numeric_limits<unsigned int>::max())
{
}

int_builder::int_builder(unsigned int min_digits, unsigned int max_digits, bool is_negative)
    : dbase(digit_base::dec),
      dcase(digit_case::lower),
      is_prefixed(true),
      is_negative(is_negative),
      generator(min_digits, max_digits)
{
}

int_builder& int_builder::set_min_digits(unsigned int value)
{
    this->generator.set_min(value);
    return *this;
}

int_builder& int_builder::set_max_digits(unsigned int value)
{
    this->generator.set_max(value);
    return *this;
}

int_builder& int_builder::set_num_digits(unsigned int value)
{
    this->set_min_digits(value);
    this->set_max_digits(value);
    return *this;
}

int_builder& int_builder::set_negative(bool is_negative)
{
    this->is_negative = is_negative;
    return *this;
}

int_builder& int_builder::set_prefixed(bool is_prefixed)
{
    this->is_prefixed = is_prefixed;
    return *this;
}

int_builder& int_builder::set_base(digit_base dbase)
{
    this->dbase = dbase;
    return *this;
}

int_builder& int_builder::set_case(digit_case dcase)
{
    this->dcase = dcase;
    return *this;
}

std::string int_builder::build() const
{
    std::string result;
    const std::string& prefix = get_base_prefix(this->dbase);
    std::size_t digit_count = this->generator.get();
    result.reserve(prefix.size() + digit_count + (this->is_negative ? 1 : 0));

    if (this->is_negative)
    {
        result.push_back('-');
    }
    if (this->is_prefixed)
    {
        for (char c : prefix)
        {
            result.push_back(c);
        }
    }
    // First digit can be 0 only for non-negative numbers with exactly one digit.
    char first_digit = get_digit(this->dbase, this->dcase);
    if (first_digit == '0' && (this->is_negative || digit_count != 1))
    {
        do
        {
            first_digit = get_digit(this->dbase, this->dcase);
        } while (first_digit == '0');
    }
    result.push_back(first_digit);
    for (std::size_t i = 1; i < digit_count; ++i)
    {
        result.push_back(get_digit(this->dbase, this->dcase));
    }
    return result;
}
