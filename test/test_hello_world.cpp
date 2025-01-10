#include <gtest/gtest.h>
#include <string>

TEST(HelloWorld, assertHelloWorld) {
  std::string test_str = "Hello World!";
  ASSERT_TRUE(test_str == "Hello World!");
}
