#include "test_binary.hpp"
#include "test_shift.hpp"

AP_BINARY_TEST(+, test_case_fixed, add)
AP_BINARY_TEST(-, test_case_fixed, sub)
AP_BINARY_TEST(*, test_case_fixed, mul)
AP_BINARY_TEST(/, test_case_fixed, div)
AP_BINARY_TEST(%, test_case_fixed, rem)
AP_SHIFT_TEST(>>, test_case_fixed, rshift)
AP_SHIFT_TEST(<<, test_case_fixed, lshift)

AP_BINARY_TEST(+, test_case_dynamic, add)
AP_BINARY_TEST(-, test_case_dynamic, sub)
AP_BINARY_TEST(*, test_case_dynamic, mul)
AP_BINARY_TEST(/, test_case_dynamic, div)
AP_BINARY_TEST(%, test_case_dynamic, rem)
AP_SHIFT_TEST(>>, test_case_dynamic, rshift)
AP_SHIFT_TEST(<<, test_case_dynamic, lshift)
