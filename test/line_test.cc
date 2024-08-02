#include "line.h"
#include <gtest/gtest.h>

using namespace testing;
using namespace emscchart;

class LineTest : public Test {};

TEST_F(LineTest, Constructor) { EXPECT_NO_THROW(Line{}); }