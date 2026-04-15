#include <gtest/gtest.h>

#include "models/Relay.hpp"

using namespace powersim::models;

TEST(RelayTest, InitializesCorrectlyWithDefaultLever) {
  Relay ocr{"Main_OCR", RelayType::OCR, 5.0};

  EXPECT_EQ(ocr.getName(), "Main_OCR");
  EXPECT_EQ(ocr.getType(), RelayType::OCR);
  EXPECT_DOUBLE_EQ(ocr.getTapSetting(), 5.0);
  EXPECT_DOUBLE_EQ(ocr.getTimeLever(), 10.0);
}

TEST(RelayTest, InitializesWithCustomLever) {
  Relay uvr{"Main_UVR", RelayType::UVR, 110.0, 2.5};

  EXPECT_DOUBLE_EQ(uvr.getTimeLever(), 2.5);
}