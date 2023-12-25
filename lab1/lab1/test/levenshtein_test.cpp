#include <gtest/gtest.h>
#include "../levenshtein.hpp"
#include <string>

TEST(MatrixTest, InsertTest) {
  int res = 1;
  std::wstring first_word = L"12";
  std::wstring second_word = L"123";

  EXPECT_EQ(levenshtein_matrix(first_word, second_word), res);
}

TEST(MatrixTest, DeleteTest) {
  int res = 1;
  std::wstring first_word = L"123";
  std::wstring second_word = L"12";

  EXPECT_EQ(levenshtein_matrix(first_word, second_word), res);
}

TEST(MatrixTest, EqTest) {
  int res = 0;
  std::wstring first_word = L"123";
  std::wstring second_word = L"123";

  EXPECT_EQ(levenshtein_matrix(first_word, second_word), res);
}

TEST(MatrixTest, SubstTest) {
  int res = 1;
  std::wstring first_word = L"125";
  std::wstring second_word = L"123";

  EXPECT_EQ(levenshtein_matrix(first_word, second_word), res);
}

TEST(MatrixTest, EmptyTest) {
  int res = 0;
  std::wstring first_word = L"";
  std::wstring second_word = L"";

  EXPECT_EQ(levenshtein_matrix(first_word, second_word), res);
}

TEST(MatrixTest, ManyOperationsTest) {
  int res = 6;
  std::wstring first_word = L"levenshtein";
  std::wstring second_word = L"frankenstein";

  EXPECT_EQ(levenshtein_matrix(first_word, second_word), res);
}

TEST(MatrixTest, RussianTest) {
  int res = 3;
  std::wstring first_word = L"коты";
  std::wstring second_word = L"шпроты";

  EXPECT_EQ(levenshtein_matrix(first_word, second_word), res);
}
