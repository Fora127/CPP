#pragma once
#include<vector>

#include "CArray.h"

class CIntArray : public CArray<int>
{
public:

  CIntArray(){}

  ~CIntArray(){}

  void createRandomArray(
      const std::size_t _n
    );
  void deleteElements();

  void insertRandomElements(
      std::size_t _n
    );
};


void CIntArray::createRandomArray(
    const std::size_t _n
  )
{
  for(std::size_t i = 0; i < _n; ++i)
  {
      push_back( std::move(rand() % 100) );
  }
}


void CIntArray::deleteElements()
{
  // erase function moves position by 1 after delete element
  // start i with 1 due to delete even elements
  for(std::size_t i = 1; i < size(); ++i)
  {
     erase(i);
  }
}


void CIntArray::insertRandomElements(
    std::size_t _n
  )
{
  for ( size_t i = 0; i < _n; ++i )
  {
     insert(rand() % size(), std::move((rand() % 100)));
  }
}

