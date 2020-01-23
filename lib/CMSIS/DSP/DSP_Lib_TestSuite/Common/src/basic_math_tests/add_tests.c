#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/basic_math_tests/basic_math_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/basic_math_tests/basic_math_test_data.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/templates/test_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/type_abbrev.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/arr_desc/arr_desc.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/jtest.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/inc/ref.h"                /* Reference Functions */
#include "../../../../../../../lib/CMSIS/DSP/Include/arm_math.h"           /* FUTs */

#define JTEST_ARM_ADD_TEST(suffix)              \
    BASIC_MATH_DEFINE_TEST_TEMPLATE_BUF2_BLK(   \
        add,                                    \
        suffix,                                 \
        TYPE_FROM_ABBREV(suffix),               \
        TYPE_FROM_ABBREV(suffix),               \
        BASIC_MATH_COMPARE_INTERFACE)

JTEST_ARM_ADD_TEST(f32);
JTEST_ARM_ADD_TEST(q31);
JTEST_ARM_ADD_TEST(q15);
JTEST_ARM_ADD_TEST(q7);

/*--------------------------------------------------------------------------------*/
/* Collect all tests in a group. */
/*--------------------------------------------------------------------------------*/

JTEST_DEFINE_GROUP(add_tests)
{
    JTEST_TEST_CALL(arm_add_f32_test);
    JTEST_TEST_CALL(arm_add_q31_test);
    JTEST_TEST_CALL(arm_add_q15_test);
    JTEST_TEST_CALL(arm_add_q7_test);
}
