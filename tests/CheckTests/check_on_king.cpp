#define APPROVALS_GOOGLETEST
#include "ApprovalTests.hpp"
#include "../test_chess.h"

TEST_F(WindowsApprovalTest, SampleTest) {
    std::string output = "Test output";
    verifyWithWindowsCompatibility(output, "SampleTest");
}