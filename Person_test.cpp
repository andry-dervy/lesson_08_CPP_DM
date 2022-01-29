/*
 * Student_test.cpp
 *
 *  Created on: Jan 24, 2022
 *      Author: andry
 */

#include <gtest/gtest.h>

#include "Person.h"

namespace psn {

class TestPerson: public testing::Test
{
protected:
  void SetUp() override
  {
    person_one = new Person();
    person_two = new Person();
  }

  void TearDown() override
  {
    delete person_one;
    delete person_two;
  }

  Person* person_one;
  Person* person_two;
};

TEST_F(TestPerson,setdata)
{
  *person_one = {"Fam","Name",std::nullopt};
  *person_two = {"Fam","Name","Patronymic"};
  ASSERT_EQ(std::make_tuple(person_one->surname,person_one->name,person_one->patronymic),
      std::make_tuple("Fam","Name",std::nullopt));
  ASSERT_NE(std::make_tuple(person_one->surname,person_one->name,person_one->patronymic),
      std::make_tuple("Fam","Name","Patronymic"));
  person_one->patronymic = "Patronymic";
  ASSERT_EQ(std::make_tuple(person_one->surname,person_one->name,person_one->patronymic),
      std::make_tuple("Fam","Name","Patronymic"));
}

TEST_F(TestPerson,comparison_operator)
{
  *person_one = {"Fam","Name",std::nullopt};
  *person_two = {"Fam","Name","Patronymic"};
  ASSERT_EQ(*person_one == *person_two,false);
  person_one->patronymic = "Patronymic";
  ASSERT_EQ(*person_one == *person_two,true);
}

TEST_F(TestPerson,less_operator)
{
  *person_one = {"Fim","Nime","Patr"};
  *person_two = {"Fim","Name","Patr"};
  ASSERT_EQ(*person_one < *person_two,false);
  *person_one = {"Fim","Name","Patr"};
  *person_two = {"Fim","Name","Pitr"};
  ASSERT_EQ(*person_one < *person_two,true);
}

} /* namespace psn */
