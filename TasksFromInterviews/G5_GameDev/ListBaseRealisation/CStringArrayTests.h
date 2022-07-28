#pragma once

#include "CArray.h"
#include <vector>
#include <iostream>
#include <regex>

class CStringArray : public CArray<std::string>
{
private:
  std::vector<std::string> m_source_str;

private:
  void createSourceStr();

public:
  CStringArray()
  {
     createSourceStr();
  }

  ~CStringArray(){}

  void createRandomArray(
      const unsigned int _n
    );

  void deleteElementsBySymbols(
      const std::vector<char>&
    );

  void insertRandomElements(
      unsigned int _n
    );

};

void CStringArray::createSourceStr()
{
  std::string string_to_split = "psychic spies from china try to steal your mind's elation \
          and little girls from sweden dream of silver screen quotation \
          and if you want these kind of dreams it's californication  \
          it's the edge of the world and all of western civilization \
          the sun may rise in the east at least it's settled in a final location \
          it's understood that hollywood sells californication \
          pay your surgeon very well to break the spell of aging \
          celebrity skin, is this your chin, or is that war you're waging? \
          first born unicorn \
          hardcore soft porn \
          dream of californication \
          dream of californication  \
          dream of californication \
          dream of californication \
          marry me, girl, be my fairy to the world, be my very own constellation \
          a teenage bride with a baby inside getting high on information \
          and buy me a star on the boulevard, it's californication \
          space may be the final frontier but it's made in a hollywood basement \
          and cobain can you hear the spheres singing songs off station to station? \
          and alderaan's not far away, it's californication \
          born and raised by those who praise control of population \
          well, everybody's been there and i don't mean on vacation \
          first born unicorn \
          hardcore soft porn \
          dream of californication \
          dream of californication \
          dream of californication \
          dream of californication \
          destruction leads to a very rough road but it also breeds creation \
          and earthquakes are to a girl's guitar, they're just another good vibration \
          and tidal waves couldn't save the world from californication \
          pay your surgeon very well to break the spell of aging \
          sicker than the rest, there is no test, but this is what you're craving?";

  std::regex rgx("\\s+");
  std::sregex_token_iterator iter(
      string_to_split.begin(),
      string_to_split.end(),
      rgx,
      -1
    );

  std::sregex_token_iterator end;

  for ( ; iter != end; ++iter)
    m_source_str.push_back(*iter);

}

void CStringArray::createRandomArray(
    unsigned int _n
  )
{
  int r;
  for(int i = 0; i < _n; ++i)
  {
    r = rand() % m_source_str.size();
    push_back( m_source_str[r] );
  }
  printArray();
}


void CStringArray::deleteElementsBySymbols(
    const std::vector<char>& vec
  )
{
  std::string pattern;

  for(auto s : vec)
  {
     pattern +=s;
     pattern +='|';
  }
  pattern.pop_back();
  std::regex rx(pattern);

  int r;
  unsigned int i = 0;
  while( i < size() )
  {
      r = std::regex_search(this->operator [](i), rx);
      if( r > 0)
        erase(i);
      else
        ++i;
  }
}

void CStringArray::insertRandomElements(unsigned int _n)
{
    int r;

    for(int i = 0; i < _n; ++i)
    {
      r = rand() % m_source_str.size();
      if( size() == 0)
        insert(0, m_source_str[r] );
      else
        insert(rand() % size(), m_source_str[r] );
    }
}
