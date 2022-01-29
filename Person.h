/*
 * Peson.h
 *
 *  Created on: Jan 24, 2022
 *      Author: andry
 */

#ifndef PERSON_H_
#define PERSON_H_

#include <iostream>
#include <string>
#include <sstream>
#include <optional>
#include <tuple>

namespace psn {

struct Person {
  std::string surname;
  std::string name;
  std::optional<std::string> patronymic;
};

std::ostream& operator<<(std::ostream& out, const Person &person);
bool operator<(const Person &personFirst,
               const Person &personSecond);
bool operator==(const Person &personFirst,
               const Person &personSecond);




} /* namespace psn */

#endif /* PERSON_H_ */
