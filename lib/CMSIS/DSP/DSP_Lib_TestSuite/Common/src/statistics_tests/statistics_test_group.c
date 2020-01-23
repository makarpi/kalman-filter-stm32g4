#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/statistics_tests/statistics_tests.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/jtest.h"

JTEST_DEFINE_GROUP(statistics_tests)
{
    JTEST_GROUP_CALL(max_tests);
    JTEST_GROUP_CALL(mean_tests);
    JTEST_GROUP_CALL(min_tests);
    JTEST_GROUP_CALL(power_tests);
    JTEST_GROUP_CALL(rms_tests);
    JTEST_GROUP_CALL(std_tests);
    JTEST_GROUP_CALL(var_tests);
    return;
}
