#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/matrix_tests/matrix_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/matrix_tests/matrix_test_data.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/templates/test_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/type_abbrev.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/arr_desc/arr_desc.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/jtest.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/inc/ref.h"                /* Reference Functions */
#include "../../../../../../../lib/CMSIS/DSP/Include/arm_math.h"           /* FUTs */

#define JTEST_ARM_MAT_TRANS_TEST(suffix)        \
    MATRIX_DEFINE_TEST_TEMPLATE_ELT1(           \
        mat_trans,                              \
        suffix,                                 \
        MATRIX_TEST_CONFIG_TRANSPOSE_OUTPUT,    \
        MATRIX_TEST_VALID_DIMENSIONS_ALWAYS)

JTEST_ARM_MAT_TRANS_TEST(f32);
JTEST_ARM_MAT_TRANS_TEST(q31);
JTEST_ARM_MAT_TRANS_TEST(q15);

/*--------------------------------------------------------------------------------*/
/* Collect all tests in a group. */
/*--------------------------------------------------------------------------------*/

JTEST_DEFINE_GROUP(mat_trans_tests)
{
    /*
      To skip a test, comment it out.
    */
    JTEST_TEST_CALL(arm_mat_trans_f32_test);
    JTEST_TEST_CALL(arm_mat_trans_q31_test);
    JTEST_TEST_CALL(arm_mat_trans_q15_test);
}
