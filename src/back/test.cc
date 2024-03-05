#include <gtest/gtest.h>

#include "../controller/s21_controller.h"

TEST(S21multisetTests, initializer_list_constructor_test) {
  S21ViewerController buf;
  EXPECT_ANY_THROW(buf.ReadFileController("none"));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}