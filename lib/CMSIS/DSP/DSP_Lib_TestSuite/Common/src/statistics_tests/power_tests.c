#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/statistics_tests/statistics_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/statistics_tests/statistics_test_data.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/templates/test_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/type_abbrev.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/arr_desc/arr_desc.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/jtest.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/inc/ref.h"                /* Reference Functions */
#include "../../../../../../../lib/CMSIS/DSP/Include/arm_math.h"           /* FUTs */

#define JTEST_ARM_POWER_TEST(suffix, output_type)   \
    STATISTICS_DEFINE_TEST_TEMPLATE_BUF1_BLK(       \
        power,                                      \
        suffix,                                     \
        TYPE_FROM_ABBREV(suffix),                   \
        TYPE_FROM_ABBREV(suffix),                   \
        STATISTICS_SNR_COMPARE_INTERFACE)

JTEST_ARM_POWER_TEST(f32, float32_t);
JTEST_ARM_POWER_TEST(q31, q63_t);
JTEST_ARM_POWER_TEST(q15, q63_t);
JTEST_ARM_POWER_TEST(q7,  q31_t);

/*--------------------------------------------------------------------------------*/
/* Collect all tests in a group. */
/*--------------------------------------------------------------------------------*/

JTEST_DEFINE_GROUP(power_tests)
{
    /*
      To skip a test, comment it out.
    */
    JTEST_TEST_CALL(arm_power_f32_test);
    JTEST_TEST_CALL(arm_power_q31_test);
    JTEST_TEST_CALL(arm_power_q15_test);
    JTEST_TEST_CALL(arm_power_q7_test);
}
