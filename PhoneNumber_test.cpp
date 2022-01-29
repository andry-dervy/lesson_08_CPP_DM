/*
 * PhoneNumber_test.cpp
 *
 *  Created on: Jan 29, 2022
 *      Author: andry
 */

#include <gtest/gtest.h>

#include "PhoneNumber.h"

namespace psn {

class TestPhoneNumber: public testing::Test
{
protected:
  void SetUp() override
  {
    phoneNumber_one = new psn::PhoneNumber();
    phoneNumber_two = new psn::PhoneNumber();
  }

  void TearDown() override
  {
    delete phoneNumber_one;
    delete phoneNumber_two;
  }

  psn::PhoneNumber* phoneNumber_one;
  psn::PhoneNumber* phoneNumber_two;
};

TEST_F(TestPhoneNumber,setdata)
{
  *phoneNumber_one = {7,911,"1234567",12};

  ASSERT_EQ(phoneNumber_one->codeCountry, 7);
  ASSERT_EQ(phoneNumber_one->codeCity, 911);
  ASSERT_EQ(phoneNumber_one->number, "1234567");
  ASSERT_EQ(phoneNumber_one->extensionNumber, 12);

  *phoneNumber_one = {7,911,"1234567"};

  ASSERT_EQ(phoneNumber_one->codeCountry, 7);
  ASSERT_EQ(phoneNumber_one->codeCity, 911);
  ASSERT_EQ(phoneNumber_one->number, "1234567");
  ASSERT_EQ(phoneNumber_one->extensionNumber, std::nullopt);
}

TEST_F(TestPhoneNumber,operator_outstream)
{
  {
    *phoneNumber_one = {7,911,"1234567",12};
    std::stringstream ss;
    ss << *phoneNumber_one;
    ASSERT_EQ(ss.str(), "+7(911)1234567 12");
  }
  {
    *phoneNumber_one = {7,911,"1234567"};
    std::stringstream ss;
    ss << *phoneNumber_one;
    ASSERT_EQ(ss.str(), "+7(911)1234567");
  }
}

TEST_F(TestPhoneNumber,less_operator)
{
    *phoneNumber_one = {7,911,"1234567",12};
    *phoneNumber_two = {7,911,"1234567",12};
    ASSERT_EQ(*phoneNumber_one < *phoneNumber_two, false);
    *phoneNumber_one = {7,911,"1231567",12};
    *phoneNumber_two = {7,911,"1234567",12};
    ASSERT_EQ(*phoneNumber_one < *phoneNumber_two, true);
    *phoneNumber_one = {7,911,"1234567",12};
    *phoneNumber_two = {7,921,"1234567",12};
    ASSERT_EQ(*phoneNumber_one < *phoneNumber_two, true);
    *phoneNumber_one = {7,911,"1234567",22};
    *phoneNumber_two = {7,911,"1234567",12};
    ASSERT_EQ(*phoneNumber_one < *phoneNumber_two, false);
    *phoneNumber_one = {7,911,"1234567",22};
    *phoneNumber_two = {7,911,"1234567",std::nullopt};
    ASSERT_EQ(*phoneNumber_one < *phoneNumber_two, false);
    *phoneNumber_one = {7,911,"1234567",std::nullopt};
    *phoneNumber_two = {7,911,"1234567",12};
    ASSERT_EQ(*phoneNumber_one < *phoneNumber_two, true);
}

} /* namespace psn */
