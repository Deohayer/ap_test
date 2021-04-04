#include "digit.hpp"
#include "rng.hpp"
#include <iostream>

char get_digit(digit_base dbase, digit_case dcase)
{
    static const std::string charset = "0123456789abcdef0123456789ABCDEF";
    static const rng<int> index_generator{0, int(charset.size())};
    int indent = (dcase != digit_case::upper) ? 0 : (charset.size() / 2);
    int wrap = (dcase == digit_case::mixed) ? charset.size() : int(dbase);
    std::cout << wrap << '\n';
    return charset[index_generator.get() % wrap + indent];
}

const std::string& get_base_prefix(digit_base dbase)
{
    static const std::string bin = "0b";
    static const std::string oct = "0";
    static const std::string dec = "";
    static const std::string hex = "0x";

    switch (dbase)
    {
    case digit_base::bin:
        return bin;
    case digit_base::oct:
        return oct;
    case digit_base::dec:
        return dec;
    case digit_base::hex:
        return hex;
    default:
        throw "Incorrect base.";
    }
}
