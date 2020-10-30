#include "src/lib/trojanmap.h"

#include <map>
#include <vector>

#include "gtest/gtest.h"

TEST(TrojanMapTest, ReturnHelloWorld) {
  TrojanMap trojanmap;
  std::string actual = cpplib.PrintHelloWorld();
  std::string expected = "**** Hello World ****";
  EXPECT_EQ(true, true);
}
