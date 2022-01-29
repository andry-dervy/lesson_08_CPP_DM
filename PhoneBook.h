/*
 * PhoneBook.h
 *
 *  Created on: Jan 29, 2022
 *      Author: andry
 */

#ifndef PHONEBOOK_H_
#define PHONEBOOK_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <optional>
#include <tuple>
#include <vector>
#include <memory>
#include <algorithm>

#include "Person.h"
#include "PhoneNumber.h"

namespace psn {

class PhoneBook {
private:
  std::vector<std::pair <std::shared_ptr<Person>, std::shared_ptr<PhoneNumber>>> vecPair;
public:
  PhoneBook(std::ifstream &inFile);
  ~PhoneBook();

  std::vector<std::pair <std::shared_ptr<Person>, std::shared_ptr<PhoneNumber>>>::const_iterator cbegin();
  std::vector<std::pair <std::shared_ptr<Person>, std::shared_ptr<PhoneNumber>>>::const_iterator cend();

  void SortByName();
  void SortByPhone();
  std::tuple<std::string,PhoneNumber> GetPhoneNumber(const std::string &surname) const;
  void ChangePhoneNumber(const Person &person, const PhoneNumber &phoneNumber);

  friend std::ostream& operator<<(std::ostream& out, const PhoneBook &pb);
};

} /* namespace psn */

#endif /* PHONEBOOK_H_ */
