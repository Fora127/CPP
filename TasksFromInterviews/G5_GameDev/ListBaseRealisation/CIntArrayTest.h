#pragma once
#include<vector>

#include "CArray.h"

class CIntArray : public CArray<int>
{
public:
  CIntArray(){}

  ~CIntArray(){}

  void createRandomArray(
      const unsigned int _n
    );
  void deleteEvenElements();

  void insertRandomElements(
      unsigned int _n
    );
};


void CIntArray::createRandomArray(
    const unsigned int _n
  )
{
  for(int i = 0; i < _n; ++i)
  {
      push_back( rand()%100 );
  }
}


void CIntArray::deleteEvenElements()
{
  unsigned int i = 1;
  for(int i = 0; i < size(); ++i)
  {
     erase(i);
  }
}


void CIntArray::insertRandomElements(
    unsigned int _n
  )
{
  int pos = 0;
  while ( _n > 0)
  {
     pos = rand() % size();
     insert(pos, (rand() % 100));
     --_n;
  }
}

