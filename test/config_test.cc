#include "config.h"
#include <gtest/gtest.h>

using namespace testing;
using namespace emscchart;

class ConfigTest : public testing::Test {};

TEST_F(ConfigTest, ConstructorShouldWorkAsExpected) {
  // Arrange

  // Act
  Config const config({
      .type = "bubble",
      .data = {.labels = {{"a"}},
               .x_labels = {},
               .y_labels = {},
               .datasets = {{.type = {},
                             .data = {{
                                          {"x", 0U},
                                          {"y", 3U},
                                          {"r", 0U},
                                      },
                                      {

                                          {"x", 1U},
                                          {"y", 3U},
                                          {"r", 2U},
                                      }}}}},
      .option = {},
  });

  // Assert
  EXPECT_EQ(config.Type(), "bubble");
  auto const& data = config.Data();
  EXPECT_EQ(data.labels[0], "a");
  auto const& datasets = data.datasets;
  EXPECT_TRUE(datasets[0].type.empty());
  EXPECT_EQ(datasets[0].data[0]["x"], 0U);
  EXPECT_EQ(datasets[0].data[0]["y"], 3U);
  EXPECT_EQ(datasets[0].data[0]["r"], 0U);
  EXPECT_EQ(datasets[0].data[1]["x"], 1U);
  EXPECT_EQ(datasets[0].data[1]["y"], 3U);
  EXPECT_EQ(datasets[0].data[1]["r"], 2U);
}