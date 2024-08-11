#include "controller.h"
#include "bubble.h"
#include "radar.h"
#include <gtest/gtest.h>
#include <functional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>

using namespace testing;
using namespace emscchart;

class ChartTest : public Test {};

TEST_F(ChartTest, GetDatasetMetaShouldReturnNewMetaWhenDatasetIndexIsInvalid) {
  // Arrange
  Chart chart{0, Configuration()};
  // Act
  auto& meta = chart.GetDatasetMeta(0);
  // Assert
  EXPECT_FALSE(meta._dataset);
}

TEST_F(ChartTest, BuildOrUpdateControllersShouldNoControllerWhenDatasetIs0) {
  // Arrange
  Chart chart{0, Configuration()};

  // Act
  auto new_controllers = chart.BuildOrUpdateControllers();

  // Assert
  EXPECT_EQ(new_controllers.size(), 0);
}

TEST_F(
    ChartTest,
    BuildOrUpdateControllersShouldBuildRadarControllerWhenConfigurationIsNotValidDatasetTypeIsEmpty) {
  // Arrange
  Chart chart{0, Configuration{.type = "abc",
                               .data = {.datasets = {{}}, .labels = {}},
                               .option = {}}};

  // Act & Assert
  EXPECT_THROW(auto new_controllers = chart.BuildOrUpdateControllers(),
               std::runtime_error);
}

TEST_F(ChartTest,
       BuildOrUpdateControllersShouldThrowExceptionWhenDatasetIsNotValid) {
  // Arrange
  Chart chart{
      0, Configuration{
             .type = {},
             .data = {.datasets = {{.type = "abc", .data = {}}}, .labels = {}},
             .option = {}}};

  // Act & Assert
  EXPECT_THROW(auto new_controllers = chart.BuildOrUpdateControllers(),
               std::runtime_error);
}

using ControllerCast = std::function<DatasetController&(DatasetController&)>;
using ChartTestWithConfigTypeParam =
    std::tuple<std::string_view, ControllerCast>;
class ChartTestWithConfigType
    : public TestWithParam<ChartTestWithConfigTypeParam> {};

INSTANTIATE_TEST_SUITE_P(
    , ChartTestWithConfigType,
    Values(std::make_tuple(RadarController::kId,
                           [](DatasetController& controller)
                               -> DatasetController& {
                             return dynamic_cast<RadarController&>(controller);
                           }),
           std::make_tuple(BubbleController::kId,
                           [](DatasetController& controller)
                               -> DatasetController& {
                             return dynamic_cast<BubbleController&>(controller);
                           })));

TEST_P(
    ChartTestWithConfigType,
    BuildOrUpdateControllersShouldBuildValidControllerWhenConfigurationTypeIsValidAndDatasetTypeIsEmpty) {
  // Arrange
  auto [type, cast] = GetParam();
  Chart chart{0, Configuration{.type = std::string(type),
                               .data = {.datasets = {{}}, .labels = {}},
                               .option = {}}};

  // Act
  auto new_controllers = chart.BuildOrUpdateControllers();

  // Assert
  EXPECT_EQ(new_controllers.size(), 1);
  auto& new_controller = new_controllers[0].get();
  EXPECT_NO_THROW(cast(new_controller));
}

TEST_P(
    ChartTestWithConfigType,
    BuildOrUpdateControllersShouldBuildValidControllerWhenDatasetTypeIsValid) {
  // Arrange
  auto [type, cast] = GetParam();
  Chart chart{
      0, Configuration{
             .type = {},
             .data = {.datasets = {{.type = std::string(type), .data = {}}},
                      .labels = {}},
             .option = {}}};

  // Act
  auto new_controllers = chart.BuildOrUpdateControllers();

  // Assert
  EXPECT_EQ(new_controllers.size(), 1);
  auto& new_controller = new_controllers[0].get();
  EXPECT_NO_THROW(cast(new_controller));
}