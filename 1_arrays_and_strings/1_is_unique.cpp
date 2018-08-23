#include <iostream>
#include <bitset>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;

/*
 * Checks if a string has unique characters 
 * by filling up a bitmap of occurrences for 
 * each character. As soon as we find a char 
 * with the bitmap set, we return false.
 * Otherwise, we return true.
 */

bool is_unique(const string &s) {
  static constexpr const int kAlphabetSize = 1<<8;
  if (s.size() > kAlphabetSize) return false;
  bitset<kAlphabetSize> b;
  for (char c : s) {
    if (b.test(c)) return false;
    b.set(c);
  }
  return true;
}

TEST(is_unique_test, unique) {
  static constexpr const char *kUnique = "abcde";
  EXPECT_TRUE(is_unique(kUnique));
}

TEST(is_unique_test, non_unique) {
  static constexpr const char *kNonUnique = "abcda";
  EXPECT_FALSE(is_unique(kNonUnique));
}

TEST(is_unique_test, single_char) {
  static constexpr const char *kSingle = "a";
  EXPECT_TRUE(is_unique(kSingle));
}

TEST(is_unique_test, empty) {
  static constexpr const char *kEmpty = "";
  EXPECT_TRUE(is_unique(kEmpty));
}


int main(int argc, char** argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
