#include "bubble.h"
#include "config.h"
#include "controller.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>

using namespace testing;
using namespace emscchart;

class BubbleControllerTest : public Test {};

TEST_F(BubbleControllerTest, IdShouldBeCorrect) {
  EXPECT_EQ(BubbleController::kId, "bubble");
}

TEST_F(BubbleControllerTest, ConstructorShouldNotThrow) {
  // Arrange
  Chart chart{0, Configuration{.type = {},
                               .data = {.labels = {},
                                        .x_labels = {},
                                        .y_labels = {},
                                        .datasets = {{.type = {}, .data = {}}}},
                               .option = {}}};

  // Act & Assert
  EXPECT_NO_THROW(BubbleController const controller(chart, 0));
}

TEST_F(BubbleControllerTest, ConstructorShouldWork) {
  // Arrange
  Chart chart{0, Configuration{.type = std::string(BubbleController::kId),
                               .data = {.labels = {},
                                        .x_labels = {},
                                        .y_labels = {},
                                        .datasets = {{.type = {}, .data = {}}}},
                               .option = {}}};

  // Act
  auto& meta = chart.GetDatasetMeta(0);

  // Assert
  EXPECT_EQ(meta.type, BubbleController::kId);
  EXPECT_EQ(meta.index, 0);
  EXPECT_TRUE(meta.controller);
  // EXPECT_EQ(meta.controller->index_, 0);
  EXPECT_EQ(meta.data.size(), 0);

  meta.controller->UpdateIndex(1);
  // EXPECT_EQ(meta.controller->index_, 1);
}
