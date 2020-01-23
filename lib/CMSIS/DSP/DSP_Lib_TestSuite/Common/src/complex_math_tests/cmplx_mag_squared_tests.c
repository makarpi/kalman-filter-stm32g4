#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/complex_math_tests/complex_math_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/complex_math_tests/complex_math_test_data.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/templates/test_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/type_abbrev.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/arr_desc/arr_desc.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/jtest.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/inc/ref.h"                /* Reference Functions */
#include "../../../../../../../lib/CMSIS/DSP/Include/arm_math.h"           /* FUTs */

#define JTEST_ARM_CMPLX_MAG_SQUARED_TEST(suffix)    \
    COMPLEX_MATH_DEFINE_TEST_TEMPLATE_BUF1_BLK(     \
        cmplx_mag_squared,                          \
        suffix,                                     \
        TYPE_FROM_ABBREV(suffix),                   \
        TYPE_FROM_ABBREV(suffix),                   \
        COMPLEX_MATH_COMPARE_RE_INTERFACE)

JTEST_ARM_CMPLX_MAG_SQUARED_TEST(f32);
JTEST_ARM_CMPLX_MAG_SQUARED_TEST(q31);
JTEST_ARM_CMPLX_MAG_SQUARED_TEST(q15);

/*--------------------------------------------------------------------------------*/
/* Collect all tests in a group. */
/*--------------------------------------------------------------------------------*/

JTEST_DEFINE_GROUP(cmplx_mag_squared_tests)
{
    JTEST_TEST_CALL(arm_cmplx_mag_squared_f32_test);
    JTEST_TEST_CALL(arm_cmplx_mag_squared_q31_test);
    JTEST_TEST_CALL(arm_cmplx_mag_squared_q15_test);
}
