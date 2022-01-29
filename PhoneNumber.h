/*
 * PhoneNumber.h
 *
 *  Created on: Jan 29, 2022
 *      Author: andry
 */

#ifndef PHONENUMBER_H_
#define PHONENUMBER_H_

#include <string>
#include <optional>
#include <sstream>
#include <tuple>

namespace psn {

struct PhoneNumber {
  int codeCountry;
  int codeCity;
  std::string number;
  std::optional<int> extensionNumber;
};

std::ostream& operator<<(std::ostream& out, const PhoneNumber &pn);
bool operator<(const PhoneNumber &phoneNumberFirst,
               const PhoneNumber &phoneNumberSecond);

} /* namespace psn */

#endif /* PHONENUMBER_H_ */
