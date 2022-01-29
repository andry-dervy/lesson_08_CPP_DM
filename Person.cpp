/*
 * Person.cpp
 *
 *  Created on: Jan 24, 2022
 *      Author: andry
 */

#include "Person.h"

namespace psn {

std::ostream& operator<<(std::ostream& out, const Person &person)
{
  std::stringstream ss;
  ss << person.surname << " ";
  ss << person.name;
  if(person.patronymic.has_value())
    ss << " " << person.patronymic.value();
  out << ss.str();
  return out;
}

bool operator<(const Person &personFirst,
               const Person &personSecond)
{
  return std::tie(personFirst.surname,
             personFirst.name,
             personFirst.patronymic) <
         std::tie(personSecond.surname,
             personSecond.name,
             personSecond.patronymic);
}

bool operator==(const Person &personFirst,
               const Person &personSecond)
{
  return std::tie(personFirst.surname,
             personFirst.name,
             personFirst.patronymic) ==
         std::tie(personSecond.surname,
             personSecond.name,
             personSecond.patronymic);
}

} /* namespace psn */
