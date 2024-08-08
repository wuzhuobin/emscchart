#include "point.h"
#include "mock_rendering_context.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace emscchart;

class PointTest : public Test {};

TEST_F(PointTest, Constructor) { EXPECT_NO_THROW(Point()); }

TEST_F(
    PointTest,
    InRangeShouldReturnCorrectValueWhenAMousePositionIsInRangeOfSumOfHitRadiusAndRadius) {
  // Arrange
  Point const point({{{.x = 10U, .y = 15U}}, {.options = {{{}, 2U, 3U}, {}}}});

  // Act & Assert
  EXPECT_TRUE(point.InRange(10U, 15U));
  EXPECT_FALSE(point.InRange(10U, 10U));
  EXPECT_FALSE(point.InRange(10U, 5U));
  EXPECT_FALSE(point.InRange(5U, 5U));
}

TEST_F(PointTest, DrawShouldDrawCircleWithXYAndRadius) {
  // Arrange
  MockCanvasRenderingContext ctx;
  Point const point({{{.x = 10U, .y = 15U}}, {.options = {{{}, 2U, {}}, {}}}});

  // Assert
  EXPECT_CALL(ctx, Circle(10U, 15U, 2U));

  // Act
  point.Draw(ctx, {});
}