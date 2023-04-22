#include <OSDL/Core/Utilities/Assert.h>
#include <gtest/gtest.h>

TEST(UtilAssert, Assertion)
{
#ifdef OSDL_ENABLE_ASSERTS
  const auto assertFunc = []
  {
    OSDL_ASSERT(nullptr != nullptr);
  };

  EXPECT_DEATH(assertFunc(), "");
#else
  ASSERT_TRUE(false) << "OSDL assertions are disabled";
#endif
}

TEST(UtilAssert, AssertionMessage)
{
#ifdef OSDL_ENABLE_ASSERTS
  const auto assertFunc = []
  {
    OSDL_ASSERT_MSG(nullptr != nullptr, "Some useful message");
  };

  EXPECT_DEATH(assertFunc(), "");
#else
  ASSERT_TRUE(false) << "OSDL assertions are disabled";
#endif
}
