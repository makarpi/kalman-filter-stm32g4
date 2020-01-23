#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/support_tests/support_tests.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/jtest.h"

JTEST_DEFINE_GROUP(support_tests)
{
    JTEST_GROUP_CALL(copy_tests);
    JTEST_GROUP_CALL(fill_tests);
    JTEST_GROUP_CALL(x_to_y_tests);
    return;
}
