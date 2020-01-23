#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/complex_math_tests/complex_math_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/complex_math_tests/complex_math_test_data.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/templates/test_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/type_abbrev.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/arr_desc/arr_desc.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/jtest.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/inc/ref.h"                /* Reference Functions */
#include "../../../../../../../lib/CMSIS/DSP/Include/arm_math.h"           /* FUTs */

#define JTEST_ARM_CMPLX_DOT_PROD_TEST(suffix, comparison_interface) \
    COMPLEX_MATH_DEFINE_TEST_TEMPLATE_BUF2_BLK(                     \
        cmplx_dot_prod,                                             \
        suffix,                                                     \
        TYPE_FROM_ABBREV(suffix),                                   \
        TYPE_FROM_ABBREV(suffix),                                   \
        comparison_interface)

JTEST_ARM_CMPLX_DOT_PROD_TEST(f32, COMPLEX_MATH_SNR_COMPARE_SPLIT_INTERFACE);
JTEST_ARM_CMPLX_DOT_PROD_TEST(q31, COMPLEX_MATH_SNR_COMPARE_SPLIT_INTERFACE);
JTEST_ARM_CMPLX_DOT_PROD_TEST(q15, COMPLEX_MATH_SNR_COMPARE_SPLIT_INTERFACE);

/*--------------------------------------------------------------------------------*/
/* Collect all tests in a group. */
/*--------------------------------------------------------------------------------*/

JTEST_DEFINE_GROUP(cmplx_dot_prod_tests)
{
    JTEST_TEST_CALL(arm_cmplx_dot_prod_f32_test);
    JTEST_TEST_CALL(arm_cmplx_dot_prod_q31_test);
    JTEST_TEST_CALL(arm_cmplx_dot_prod_q15_test);
}
