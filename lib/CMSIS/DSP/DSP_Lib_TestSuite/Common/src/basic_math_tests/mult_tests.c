#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/basic_math_tests/basic_math_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/basic_math_tests/basic_math_test_data.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/templates/test_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/type_abbrev.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/arr_desc/arr_desc.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/jtest.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/inc/ref.h"                /* Reference Functions */
#include "../../../../../../../lib/CMSIS/DSP/Include/arm_math.h"           /* FUTs */

#define JTEST_ARM_MULT_TEST(suffix, compare_interface)  \
    BASIC_MATH_DEFINE_TEST_TEMPLATE_BUF2_BLK(   \
        mult,                                   \
        suffix,                                 \
        TYPE_FROM_ABBREV(suffix),               \
        TYPE_FROM_ABBREV(suffix),               \
        compare_interface)

JTEST_ARM_MULT_TEST(f32, BASIC_MATH_COMPARE_INTERFACE);
JTEST_ARM_MULT_TEST(q31, BASIC_MATH_SNR_COMPARE_INTERFACE);
JTEST_ARM_MULT_TEST(q15, BASIC_MATH_COMPARE_INTERFACE);
JTEST_ARM_MULT_TEST(q7 , BASIC_MATH_COMPARE_INTERFACE);

/*--------------------------------------------------------------------------------*/
/* Collect all tests in a group. */
/*--------------------------------------------------------------------------------*/

JTEST_DEFINE_GROUP(mult_tests)
{
    JTEST_TEST_CALL(arm_mult_f32_test);
    JTEST_TEST_CALL(arm_mult_q31_test);
    JTEST_TEST_CALL(arm_mult_q15_test);
    JTEST_TEST_CALL(arm_mult_q7_test);
}
