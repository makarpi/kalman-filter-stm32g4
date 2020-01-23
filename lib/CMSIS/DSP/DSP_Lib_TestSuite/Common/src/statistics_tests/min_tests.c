#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/statistics_tests/statistics_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/statistics_tests/statistics_test_data.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/templates/test_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/type_abbrev.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/arr_desc/arr_desc.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/jtest.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/inc/ref.h"                /* Reference Functions */
#include "../../../../../../../lib/CMSIS/DSP/Include/arm_math.h"           /* FUTs */

#define JTEST_ARM_MIN_TEST(suffix)              \
    STATISTICS_DEFINE_TEST_TEMPLATE_BUF1_BLK(   \
        min,                                    \
        suffix,                                 \
        TYPE_FROM_ABBREV(suffix),               \
        TYPE_FROM_ABBREV(suffix),               \
        STATISTICS_COMPARE_INTERFACE)

JTEST_ARM_MIN_TEST(f32);
JTEST_ARM_MIN_TEST(q31);
JTEST_ARM_MIN_TEST(q15);
JTEST_ARM_MIN_TEST(q7);

/*--------------------------------------------------------------------------------*/
/* Collect all tests in a group. */
/*--------------------------------------------------------------------------------*/

JTEST_DEFINE_GROUP(min_tests)
{
    /*
      To skip a test, comment it out.
    */
    JTEST_TEST_CALL(arm_min_f32_test);
    JTEST_TEST_CALL(arm_min_q31_test);
    JTEST_TEST_CALL(arm_min_q15_test);
    JTEST_TEST_CALL(arm_min_q7_test);
}
