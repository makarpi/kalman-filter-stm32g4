#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/basic_math_tests/basic_math_tests.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/jtest.h"

JTEST_DEFINE_GROUP(basic_math_tests)
{
    JTEST_GROUP_CALL(abs_tests);
    JTEST_GROUP_CALL(add_tests);
    JTEST_GROUP_CALL(dot_prod_tests);
    JTEST_GROUP_CALL(mult_tests);
    JTEST_GROUP_CALL(negate_tests);
    JTEST_GROUP_CALL(offset_tests);
    JTEST_GROUP_CALL(scale_tests); 
    JTEST_GROUP_CALL(shift_tests);
    JTEST_GROUP_CALL(sub_tests);

    return;
}
