#include <gtest/gtest.h>

#include "langdef.h"

TEST(LangDefTest, AssignOperatorIsPresent) {
  ASSERT_NE(0, isoperator(SIMPLE_ASSIGN_OPERATOR));
}