/*
 * PhoneBook.cpp
 *
 *  Created on: Jan 29, 2022
 *      Author: andry
 */

#include "PhoneBook.h"

namespace psn {

std::vector<std::string> split(const std::string &s, const std::string &delim)
{
  std::vector<std::string> vec;

  if(s.length() == 0)
    return vec;

  if(delim.length() == 0)
  {
    vec.push_back(s);
    return vec;
  }

  size_t pos = 0;
  while (pos < s.length() - 1)
  {
    size_t posDelim = s.length();
    for(const char ch: delim)
    {
      size_t p = s.find(ch,pos);
      if(p < posDelim)
        posDelim = p;
    }
    if(posDelim == pos)
    {
      ++pos;
      continue;
    }
    std::string substr = s.substr(pos,posDelim - pos);
    vec.push_back(substr);
    pos = posDelim + 1;
  }
  return vec;
}

PhoneBook::PhoneBook(std::ifstream &inFile)
{
  if (inFile.is_open())
  {
    const size_t size = 255;
    char buf[size];
    std::string line_of_file;
    while (!inFile.eof())
    {
      inFile.getline(buf, size);
      line_of_file = buf;

      std::string fullName =
          line_of_file.substr(0, line_of_file.find("+")-1);

      std::vector<std::string> vName = split(fullName," ");

      std::string phoneNumber =
          line_of_file.substr(line_of_file.find("+")+1,line_of_file.back());

      std::vector<std::string> vPhoneNumber = split(phoneNumber,"() ");

      if(vName.size() < 2 || vPhoneNumber.size() < 3)
        continue;

      std::shared_ptr<Person> pPerson = std::make_shared<Person>();

      pPerson->surname = vName[0];
      pPerson->name = vName[1];
      if(vName.size() > 2)
        pPerson->patronymic = vName[2];
      else
        pPerson->patronymic = std::nullopt;

      std::shared_ptr<PhoneNumber> pPhoneNumber = std::make_shared<PhoneNumber>();

      pPhoneNumber->codeCountry = stoi(vPhoneNumber[0]);
      pPhoneNumber->codeCity = stoi(vPhoneNumber[1]);
      pPhoneNumber->number = vPhoneNumber[2];
      if(vPhoneNumber.size() > 3)
        pPhoneNumber->extensionNumber = stoi(vPhoneNumber[3]);
      else
        pPhoneNumber->extensionNumber = std::nullopt;

      vecPair.push_back(std::make_pair(pPerson,pPhoneNumber));
    }
    inFile.close();
  }
  else
  {
    std::cout << "File did not open!" << std::endl;
  }
}

PhoneBook::~PhoneBook()
{
}

std::ostream& operator<<(std::ostream& out, const PhoneBook &pb)
{
  for(const auto& a: pb.vecPair)
  {
    if(a.first != nullptr && a.second != nullptr)
      out << *a.first << " " << *a.second << std::endl;
  }
  return out;
}

void PhoneBook::SortByName()
{
  auto Comp = [](std::pair<std::shared_ptr<Person>,std::shared_ptr<PhoneNumber>> p1,
      std::pair<std::shared_ptr<Person>,std::shared_ptr<PhoneNumber>> p2) -> bool
    {
      if(p1.first != nullptr && p2.second != nullptr)
        return *p1.first < *p2.first;
      return false;
    };

  sort(vecPair.begin(),vecPair.end(),Comp);
}

void PhoneBook::SortByPhone()
{
  auto Comp = [](std::pair<std::shared_ptr<Person>,std::shared_ptr<PhoneNumber>> p1,
      std::pair<std::shared_ptr<Person>,std::shared_ptr<PhoneNumber>> p2) -> bool
    {
      if(p1.second != nullptr && p2.second != nullptr)
        return *p1.second < *p2.second;
      return false;
    };

  sort(vecPair.begin(),vecPair.end(),Comp);
}

std::tuple<std::string,PhoneNumber> PhoneBook::GetPhoneNumber(const std::string &surname) const
{
  size_t cnt = 0;
  std::shared_ptr<PhoneNumber> p_pn;
  auto counter = [&cnt,surname,&p_pn](const std::pair<std::shared_ptr<Person>,std::shared_ptr<PhoneNumber>> &p){
    if(surname == p.first->surname)
    {
      ++cnt;
      p_pn = p.second;
    }
  };

  for_each(vecPair.begin(),vecPair.end(),counter);

  std::tuple<std::string,PhoneNumber> t;
  if(cnt == 0)
    t = std::make_tuple("Not found", PhoneNumber{0,0,"",std::nullopt});
  else if(cnt == 1)
    t = std::make_tuple("", *p_pn);
  else
    t = std::make_tuple("Found more than 1", PhoneNumber{0,0,"",std::nullopt});

  return t;
}

void PhoneBook::ChangePhoneNumber(const Person &person, const PhoneNumber &phoneNumber)
{
  auto it = find_if(vecPair.begin(),vecPair.end(),
                    [person](std::pair<std::shared_ptr<Person>,std::shared_ptr<PhoneNumber>> p) -> bool
                      {
                        if(p.first != nullptr)
                          return person == *p.first;
                        return false;
                      }
                    );

  if(it != vecPair.end())
  {
    *it->second = phoneNumber;
  }
}

std::string getNameFile()
{
  std::cout << "Enter file's name: ";
  std::string s;
  std::cin >> s;
  return s;
}

std::vector<std::pair <std::shared_ptr<Person>, std::shared_ptr<PhoneNumber>>>::const_iterator PhoneBook::cbegin()
{
  return vecPair.cbegin();
}

std::vector<std::pair <std::shared_ptr<Person>, std::shared_ptr<PhoneNumber>>>::const_iterator PhoneBook::cend()
{
  return vecPair.cend();
}

} /* namespace psn */
