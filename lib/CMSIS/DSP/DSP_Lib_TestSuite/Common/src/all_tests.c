#include "../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/basic_math_tests/basic_math_test_group.h"
#include "../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/complex_math_tests/complex_math_test_group.h"
#include "../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/controller_tests/controller_test_group.h"
#include "../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/fast_math_tests/fast_math_test_group.h"
#include "../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/filtering_tests/filtering_test_group.h"
#include "../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/intrinsics_tests/intrinsics_test_group.h"
#include "../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/matrix_tests/matrix_test_group.h"
#include "../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/statistics_tests/statistics_test_group.h"
#include "../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/support_tests/support_test_group.h"
#include "../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/transform_tests/transform_test_group.h"
#include "../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/jtest.h"

JTEST_DEFINE_GROUP(all_tests)
{
    /*
      To skip a test, comment it out
    */
    JTEST_GROUP_CALL(basic_math_tests);
    JTEST_GROUP_CALL(complex_math_tests);
    JTEST_GROUP_CALL(controller_tests);
    JTEST_GROUP_CALL(fast_math_tests);
    JTEST_GROUP_CALL(filtering_tests);
    JTEST_GROUP_CALL(matrix_tests);
    JTEST_GROUP_CALL(statistics_tests);
    JTEST_GROUP_CALL(support_tests);
    JTEST_GROUP_CALL(transform_tests);
    JTEST_GROUP_CALL(intrinsics_tests);

    return;
}
