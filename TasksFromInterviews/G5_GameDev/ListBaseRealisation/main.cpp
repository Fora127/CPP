#include <iostream>
#include <vector>
#include <string>

#include "CArray.h"
#include "CommonTests.h"
#include "CIntArrayTest.h"
#include "CStringArrayTests.h"

int main()
{
  int i = 0;

  while(i < 100)
  {
     std::cout << "TEST " << i+1 << "------------------------------------------------------------------------------------------" << std::endl;

     //tests for CArray<int>

     //test 1.1
     CIntArray arr;
     arr.createRandomArray(20);
     std::cout << "Create: ";
     std::cout << arr.printArray() << std::endl;

     //test 1.2
     arr.deleteEvenElements();
     std::cout << "Delete even elements: ";
     std::cout << arr.printArray() << std::endl;

     //test 1.3
     arr.sort();
     std::cout << "Sort: ";
     std::cout << arr.printArray() << std::endl;

     //test 1.4
     arr.insertRandomElements(10);
     std::cout << "Insert random elements: ";
     std::cout << arr.printArray() << std::endl;

     //test 1.5
     arr.clear();
     std::cout << "Destroy: ";
     std::cout << arr.printArray() << std::endl;

     std::cout << std::endl;

     //tests for CArray<std::string>

     CStringArray sArr;

     //test 2.1
     sArr.createRandomArray(15);
     std::cout << "Create: ";
     std::cout << sArr.printArray() << std::endl;

     //test 2.2
     sArr.sort();
     std::cout << "Sort: ";
     std::cout << sArr.printArray() << std::endl;

     //test 2.3
     std::vector<char> symbolsToDelete = {'a','b','c','d','e'};

     sArr.deleteElementsBySymbols(symbolsToDelete);
     std::cout << "Delete elements with symbols: [";
     for(auto v : symbolsToDelete)
         std::cout << v << " ";
     std::cout << "]" << std::endl;
     std::cout << sArr.printArray() << std::endl;

     //test 2.4
     sArr.insertRandomElements(3);
     std::cout << "Insert random elements: ";
     std::cout << sArr.printArray() << std::endl;

     std::cout << std::endl << std::endl;

     ++i;
  }

  return 0;
}
