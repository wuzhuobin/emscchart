#include "controller.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include "radar.h"

using namespace testing;
using namespace emscchart;

class ControllerTest : public Test {};

TEST_F(ControllerTest,
       GetDatasetMetaShouldReturnNewMetaWhenDatasetIndexIsInvalid) {
  // Arrange
  Chart chart{"item", Configuration()};
  // Act
  auto& meta = chart.GetDatasetMeta(0);
  // Assert
  EXPECT_FALSE(meta._dataset);
}

TEST_F(ControllerTest,
       BuildOrUpdateControllersShouldNoControllerWhenDatasetIs0) {
  // Arrange
  Chart chart{"item", Configuration()};

  // Act
  auto new_controllers = chart.BuildOrUpdateControllers();

  // Assert
  EXPECT_EQ(new_controllers.size(), 0);
}

TEST_F(
    ControllerTest,
    BuildOrUpdateControllersShouldBuildRadarControllerWhenConfigurationIsRadarDatasetTypeIsEmpty) {
  // Arrange
  Chart chart{"item", Configuration{.type = "radar", .data = {.datasets{{}}}}};

  // Act
  auto new_controllers = chart.BuildOrUpdateControllers();

  // Assert
  EXPECT_EQ(new_controllers.size(), 1);
  auto& new_controller = new_controllers[0].get();
  EXPECT_NO_THROW(dynamic_cast<RadarController&>(new_controller));
}

TEST_F(
    ControllerTest,
    BuildOrUpdateControllersShouldBuildRadarControllerWhenConfigurationIsNotRadarDatasetTypeIsEmpty) {
  // Arrange
  Chart chart{"item", Configuration{.type = "abc", .data = {.datasets{{}}}}};

  // Act & Assert
  EXPECT_THROW(auto new_controllers = chart.BuildOrUpdateControllers(),
               std::runtime_error);
}

TEST_F(ControllerTest,
       BuildOrUpdateControllersShouldBuildRadarControllerWhenDatasetIsRadar) {
  // Arrange
  Chart chart{"item", Configuration{.data = {.datasets{{.type = "radar"}}}}};

  // Act
  auto new_controllers = chart.BuildOrUpdateControllers();

  // Assert
  EXPECT_EQ(new_controllers.size(), 1);
  auto& new_controller = new_controllers[0].get();
  EXPECT_NO_THROW(dynamic_cast<RadarController&>(new_controller));
}

TEST_F(ControllerTest,
       BuildOrUpdateControllersShouldThrowExceptionWhenDatasetIsNotRadar) {
  // Arrange
  Chart chart{"item", Configuration{.data = {.datasets{{.type = "abc"}}}}};

  // Act & Assert
  EXPECT_THROW(auto new_controllers = chart.BuildOrUpdateControllers(),
               std::runtime_error);
}
