#include <iostream>

#include "CommonTests.h"
#include "CIntArrayTest.h"
#include "CStringArrayTests.h"

using namespace std;


int main()
{
  int i = 0;

  while(i < 50000)
  {
     cout << "TEST " << i+1 << " ------------------------------------------------------------------------------------------\n";

     // tests for CArray<int>

     //test 1.1
     CIntArray arr;
     arr.createRandomArray(20);
     cout << "Create: ";
     cout << arr.print() << endl;

     //test 1.2
     arr.deleteElements();
     cout << "Delete each second elements: ";
     cout << arr.print() << endl;

     //test 1.3
     arr.sort();
     cout << "Sort: ";
     cout << arr.print() << endl;

     //test 1.4
     arr.insertRandomElements(10);
     cout << "Insert random elements: ";
     cout << arr.print() << endl;

     //test 1.5
     arr.clear();
     cout << "Destroy: ";
     cout << arr.print() << endl;

     cout << endl;


     // tests for CArray<std::string>

      CStringArray sArr;

     //test 2.1
     sArr.createRandomArray(15);
     cout << "Create: ";
     cout << sArr.print() << endl;

     //test 2.2
     sArr.sort();
     cout << "Sort: ";
     cout << sArr.print() << endl;

     //test 2.3
     vector<char> symbolsToDelete = {'a','b','c','d','e'};

     sArr.deleteElementsBySymbols(symbolsToDelete);
     cout << "Delete elements with symbols: [";
     for(auto v : symbolsToDelete)
         cout << v << " ";
     cout << "] : ";
     cout << sArr.print() << endl;

     //test 2.4
     sArr.insertRandomElements(3);
     cout << "Insert random elements: ";
     cout << sArr.print() << endl;

     cout << endl << endl;

     ++i;
  }

  CommonTest();

  return 0;
}
