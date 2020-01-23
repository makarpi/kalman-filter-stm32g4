#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/matrix_tests/matrix_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/matrix_tests/matrix_test_data.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/templates/test_templates.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/type_abbrev.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/arr_desc/arr_desc.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/jtest.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/inc/ref.h"                /* Reference Functions */
#include "../../../../../../../lib/CMSIS/DSP/Include/arm_math.h"           /* FUTs */

#define JTEST_ARM_MAT_INIT_TEST(suffix)                     \
    JTEST_DEFINE_TEST(arm_mat_init_##suffix##_test,         \
                      arm_mat_init_##suffix)                \
    {                                                       \
        const uint16_t rows = 4;                            \
        const uint16_t cols = 2;                            \
        arm_matrix_instance_##suffix  matrix = {0};         \
        /*  TYPE_FROM_ABBREV(suffix) data[rows*cols] = {0}; */ \
            TYPE_FROM_ABBREV(suffix) data[4*2] = {0}; \
                                                            \
            arm_mat_init_##suffix(&matrix,                  \
                                  rows,                     \
                                  cols,                     \
                                  data);                    \
                                                            \
                JTEST_DUMP_STRF("Matrix Dimensions: %dx%d\n", \
                     (int)matrix.numRows,                   \
                     (int)matrix.numCols);                  \
                                                            \
                if ((matrix.numRows == rows) &&             \
                    (matrix.numCols == cols) &&             \
                    (matrix.pData == data))                 \
                {                                           \
                    return JTEST_TEST_PASSED;               \
                }                                           \
                else                                        \
                {                                           \
                    return JTEST_TEST_FAILED;               \
                }                                           \
                                                            \
    }

JTEST_ARM_MAT_INIT_TEST(f32);
JTEST_ARM_MAT_INIT_TEST(q31);
JTEST_ARM_MAT_INIT_TEST(q15);

/*--------------------------------------------------------------------------------*/
/* Collect all tests in a group. */
/*--------------------------------------------------------------------------------*/

JTEST_DEFINE_GROUP(mat_init_tests)
{
    /*
      To skip a test, comment it out.
    */
    JTEST_TEST_CALL(arm_mat_init_f32_test);
    JTEST_TEST_CALL(arm_mat_init_q31_test);
    JTEST_TEST_CALL(arm_mat_init_q15_test);
}
