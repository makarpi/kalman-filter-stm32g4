#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/statistics_tests/statistics_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/statistics_tests/statistics_test_data.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/templates/test_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/type_abbrev.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/arr_desc/arr_desc.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/jtest.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/inc/ref.h"                /* Reference Functions */
#include "../../../../../../../lib/CMSIS/DSP/Include/arm_math.h"           /* FUTs */

#define JTEST_ARM_VAR_TEST(suffix)              \
    STATISTICS_DEFINE_TEST_TEMPLATE_BUF1_BLK(   \
        var,                                    \
        suffix,                                 \
        TYPE_FROM_ABBREV(suffix),               \
        TYPE_FROM_ABBREV(suffix),               \
        STATISTICS_SNR_COMPARE_INTERFACE)

JTEST_ARM_VAR_TEST(f32);
JTEST_ARM_VAR_TEST(q31);
JTEST_ARM_VAR_TEST(q15);

/*--------------------------------------------------------------------------------*/
/* Collect all tests in a group. */
/*--------------------------------------------------------------------------------*/

JTEST_DEFINE_GROUP(var_tests)
{
    /*
      To skip a test, comment it out.
    */
    JTEST_TEST_CALL(arm_var_f32_test);
    JTEST_TEST_CALL(arm_var_q31_test);
    JTEST_TEST_CALL(arm_var_q15_test);
}
