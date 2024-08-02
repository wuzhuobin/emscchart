#include "bubble.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace emscchart;

class BubbleControllerTest : public Test {};

TEST_F(BubbleControllerTest, IdShouldBeCorrect) {
  EXPECT_EQ(BubbleController::kId, "bubble");
}