#include <gtest/gtest.h>
#include <fstream>

#include "file_reader.h"

std::ifstream fin("../resources/source.txt");

TEST(FileReaderTest, InitialValues) {
  FileReader reader;
  EXPECT_EQ(reader.getLineNumber(), 1);
  EXPECT_EQ(reader.getColumnNumber(), 1);
}

TEST(FileReaderTest, GetChar) {
  FileReader reader;
  char c = reader.getchar();
  EXPECT_TRUE(c >= 0);
}

TEST(FileReaderTest, UpdateLocation) {
  FileReader reader;
  reader.updateLocation();
  EXPECT_EQ(reader.getLineNumber(), 1);
  EXPECT_EQ(reader.getColumnNumber(), 2);

  reader.updateLocation();
  EXPECT_EQ(reader.getLineNumber(), 2);
  EXPECT_EQ(reader.getColumnNumber(), 1);
}

TEST(FileReaderTest, IncludeOnce) { SUCCEED(); }
