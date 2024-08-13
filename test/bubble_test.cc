#include "bubble.h"
#include "config.h"
#include "controller.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace emscchart;

class BubbleControllerTest : public Test {};

TEST_F(BubbleControllerTest, IdShouldBeCorrect) {
  EXPECT_EQ(BubbleController::kId, "bubble");
}

TEST_F(BubbleControllerTest, ConstructorShouldWork) {
  Chart chart{0, Configuration{.type = {},
                               .data = {.datasets = {{.type = {}, .data = {}}},
                                        .labels = {}},
                               .option = {}}};
  EXPECT_NO_THROW(BubbleController const controller(chart, 0));
}
