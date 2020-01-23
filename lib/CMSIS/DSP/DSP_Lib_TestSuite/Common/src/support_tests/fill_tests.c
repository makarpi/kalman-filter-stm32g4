#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/support_tests/support_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/support_tests/support_test_data.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/templates/test_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/type_abbrev.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/arr_desc/arr_desc.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/jtest.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/inc/ref.h"                /* Reference Functions */
#include "../../../../../../../lib/CMSIS/DSP/Include/arm_math.h"           /* FUTs */

#define JTEST_ARM_FILL_TEST(suffix)             \
    SUPPORT_DEFINE_TEST_TEMPLATE_ELT1_BLK(      \
        fill,                                   \
        suffix,                                 \
        TYPE_FROM_ABBREV(suffix),               \
        TYPE_FROM_ABBREV(suffix),               \
        SUPPORT_COMPARE_INTERFACE)

JTEST_ARM_FILL_TEST(f32);
JTEST_ARM_FILL_TEST(q31);
JTEST_ARM_FILL_TEST(q15);
JTEST_ARM_FILL_TEST(q7);

/*--------------------------------------------------------------------------------*/
/* Collect all tests in a group. */
/*--------------------------------------------------------------------------------*/

JTEST_DEFINE_GROUP(fill_tests)
{
    /*
      To skip a test, comment it out.
    */
    JTEST_TEST_CALL(arm_fill_f32_test);
    JTEST_TEST_CALL(arm_fill_q31_test);
    JTEST_TEST_CALL(arm_fill_q15_test);
    JTEST_TEST_CALL(arm_fill_q7_test);
}
