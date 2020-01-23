#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/inc/controller_tests/controller_tests.h"
#include "../../../../../../../lib/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc/jtest.h"

JTEST_DEFINE_GROUP(controller_tests)
{
    /*
      To skip a test, comment it out.
    */
    JTEST_GROUP_CALL(pid_reset_tests);
    JTEST_GROUP_CALL(pid_tests);
    JTEST_GROUP_CALL(sin_cos_tests);
    return;
}
