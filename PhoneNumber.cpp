/*
 * PhoneNumber.cpp
 *
 *  Created on: Jan 29, 2022
 *      Author: andry
 */

#include "PhoneNumber.h"

namespace psn {

std::ostream& operator<<(std::ostream& out, const PhoneNumber &pn)
{
  std::stringstream ss;
  ss << "+" << pn.codeCountry << "("
      << pn.codeCity << ")" << pn.number;
  if(pn.extensionNumber.has_value())
    ss << " " << pn.extensionNumber.value();
  out << ss.str();
  return out;
}

bool operator<(const PhoneNumber &phoneNumberFirst,
               const PhoneNumber &phoneNumberSecond)
{
  return std::tie(phoneNumberFirst.codeCountry,
             phoneNumberFirst.codeCity,
             phoneNumberFirst.number,
             phoneNumberFirst.extensionNumber) <
         std::tie(phoneNumberSecond.codeCountry,
             phoneNumberSecond.codeCity,
             phoneNumberSecond.number,
             phoneNumberSecond.extensionNumber);
}

} /* namespace psn */
