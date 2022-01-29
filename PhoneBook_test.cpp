/*
 * PhoneBook_test.cpp
 *
 *  Created on: Jan 29, 2022
 *      Author: andry
 */

#include <gtest/gtest.h>

#include "PhoneBook.h"

namespace psn {

class TestPhoneBook: public testing::Test
{
protected:
  void SetUp() override
  {
    phoneBook = nullptr;
  }

  void TearDown() override
  {
    if(phoneBook != nullptr) delete phoneBook;
  }

  PhoneBook* phoneBook;
};

TEST_F(TestPhoneBook,loaddata)
{
  std::string nameFile = "testFile";
  std::ifstream fin(nameFile + ".txt");
  phoneBook = new PhoneBook(fin);

  auto a = phoneBook->GetPhoneNumber("Панфилов");
  ASSERT_EQ(std::get<0>(a).length() == 0, true);

  {
    std::stringstream ss;
    ss << std::get<1>(a);
    ASSERT_EQ(ss.str() == "+7(950)2343678", true);
  }

  a = phoneBook->GetPhoneNumber("Петров");
  ASSERT_EQ(std::get<0>(a) == "Not found", true);

  a = phoneBook->GetPhoneNumber("Елисеев");
  ASSERT_EQ(std::get<0>(a) == "Found more than 1", true);
}

TEST_F(TestPhoneBook,sortDataByName)
{
  std::string nameFile = "testFile";
  std::ifstream fin(nameFile + ".txt");
  phoneBook = new PhoneBook(fin);

  phoneBook->SortByName();

  auto begin = phoneBook->cbegin();
  auto end = phoneBook->cend();
  auto begin_next = begin + 1;

  ASSERT_EQ(begin == end, false);

  while(begin_next != end)
  {
    ASSERT_EQ(*(begin->first) < *(begin_next->first), true);
    ++begin;
    ++begin_next;
  }
}

TEST_F(TestPhoneBook,sortDataByPhone)
{
  std::string nameFile = "testFile";
  std::ifstream fin(nameFile + ".txt");
  phoneBook = new PhoneBook(fin);

  phoneBook->SortByPhone();

  auto begin = phoneBook->cbegin();
  auto end = phoneBook->cend();
  auto begin_next = begin + 1;

  ASSERT_EQ(begin == end, false);

  while(begin_next != end)
  {
    ASSERT_EQ(*(begin->second) < *(begin_next->second), true);
    ++begin;
    ++begin_next;
  }
}

TEST_F(TestPhoneBook,ChangePhoneNumber)
{
  std::string nameFile = "testFile";
  std::ifstream fin(nameFile + ".txt");
  phoneBook = new PhoneBook(fin);

  Person p = {"Кошелев", "Аким", "Феликсович"};

  auto a = phoneBook->GetPhoneNumber(p.surname);

  ASSERT_EQ(std::get<1>(a).codeCountry == 7, true);
  ASSERT_EQ(std::get<1>(a).codeCity == 960, true);
  ASSERT_EQ(std::get<1>(a).number == "2743478", false);
  ASSERT_EQ(std::get<1>(a).extensionNumber == 9, true);

  PhoneNumber phoneNumber = {7,960,"2743418"};
  phoneBook->ChangePhoneNumber(p, phoneNumber);

  a = phoneBook->GetPhoneNumber(p.surname);

  ASSERT_EQ(std::get<1>(a).codeCountry == 7, true);
  ASSERT_EQ(std::get<1>(a).codeCity == 960, true);
  ASSERT_EQ(std::get<1>(a).number == "2743418", true);
  ASSERT_EQ(std::get<1>(a).extensionNumber == std::nullopt, true);
}

} /* namespace psn */
