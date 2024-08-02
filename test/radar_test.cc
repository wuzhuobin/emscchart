
#include "radar.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace emscchart;

class RadarControllerTest : public Test {};

TEST_F(RadarControllerTest, IdShouldBeCorrect) {
  EXPECT_EQ(RadarController::kId, "radar");
}