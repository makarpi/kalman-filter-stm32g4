#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/matrix_tests/matrix_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/matrix_tests/matrix_test_data.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/templates/test_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/type_abbrev.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/arr_desc/arr_desc.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/jtest.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/inc/ref.h"                /* Reference Functions */
#include "../../../../../../../lib/CMSIS/DSP/Include/arm_math.h"           /* FUTs */

#define JTEST_ARM_MAT_SUB_TEST(suffix)          \
    MATRIX_DEFINE_TEST_TEMPLATE_ELT2(           \
        mat_sub,                                \
        suffix,                                 \
        MATRIX_TEST_CONFIG_ADDITIVE_OUTPUT,     \
        MATRIX_TEST_VALID_ADDITIVE_DIMENSIONS,  \
        MATRIX_COMPARE_INTERFACE)

JTEST_ARM_MAT_SUB_TEST(f32);
JTEST_ARM_MAT_SUB_TEST(q31);
JTEST_ARM_MAT_SUB_TEST(q15);

/*--------------------------------------------------------------------------------*/
/* Collect all tests in a group. */
/*--------------------------------------------------------------------------------*/

JTEST_DEFINE_GROUP(mat_sub_tests)
{
    /*
      To skip a test, comment it out.
    */
    JTEST_TEST_CALL(arm_mat_sub_f32_test);
    JTEST_TEST_CALL(arm_mat_sub_q31_test);
    JTEST_TEST_CALL(arm_mat_sub_q15_test);
}
