#include "config.h"
#include <gtest/gtest.h>

using namespace testing;
using namespace emscchart;

class ConfigTest : public testing::Test {};

TEST_F(ConfigTest, UpdateShouldResetOptions) {
  using OptionsByte = std::array<std::byte, sizeof(Options)>;

  Config config{Configuration()};
  config.Update();
  auto updated_options_bytes =
      reinterpret_cast<OptionsByte const&>(config.Options());

  Options initial_options{};
  auto initial_options_bytes =
      reinterpret_cast<OptionsByte const&>(initial_options);

  // for (auto i = 0; i < sizeof(Options); i++) {
  //   EXPECT_EQ(updated_options_bytes[i], initial_options_bytes[i])
  //       << "where i is " << i;
  // }
}