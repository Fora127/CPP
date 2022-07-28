#pragma once

#include "CArray.h"

static bool bResult = true;

#define TEST_VERIFY(statement, testname) \
do {\
    if ( static_cast<bool>(statement) )\
        std::cout << "PASSED";\
    else{\
        std::cout << "FAILED";\
        bResult = false;}\
    std::cout << " : " << testname << std::endl;\
} while (false)

void CommonTest()
{
    // TEST 1
  std::string strTestName = "TEST: Create definitive CArray";
  {
      CArray<int> predefineArray;
      predefineArray.push_back(10);
      predefineArray.push_back(11);
      predefineArray.push_back(12);

      std::string str = predefineArray.print();
      TEST_VERIFY( str == "['10'; '11'; '12']" && predefineArray.size() == 3, strTestName );
      std::cout << "  CArray: " << str << std::endl;
      std::cout << std::endl;
  }

  // TEST 2
  strTestName = "TEST: Create CArray with random numbers";
  {
      const std::size_t n = 20;
      CArray<std::size_t> a2;

      for(std::size_t i=0; i<n; ++i)
      {
          a2.push_back(rand()%100);
      }

      TEST_VERIFY(a2.size() == n, strTestName );
      std::cout << "  CArray: " << a2.print() << std::endl;
      std::cout << std::endl;
  }

  // TEST 3
  strTestName = "TEST: Operator[]";
  {
      CArray<std::size_t> predefineArray;
      predefineArray.push_back(0);
      predefineArray.push_back(1);
      predefineArray.push_back(2);
      predefineArray.push_back(3);
      predefineArray.push_back(4);

      int  valByIndex = 0;

      for(std::size_t  i=0; i< predefineArray.size(); i++)
      {
          bool bOutOfRange = false;
          try {
           valByIndex = predefineArray[i];
          }
          catch(const char* /*exp*/)
          {
              bOutOfRange = true;
          }
          TEST_VERIFY( bOutOfRange == false &&
                       valByIndex ==  static_cast<int> (i), strTestName );
      }
      std::cout << std::endl;
  }

  // TEST 4
  strTestName = "TEST: Out Of Range";
  {
      CArray<std::size_t> predefineArray;
      predefineArray.push_back(10);
      predefineArray.push_back(11);
      predefineArray.push_back(12);

      const std::size_t targetIndex = predefineArray.size();

      bool bOutOfRange = false;
      try {
        predefineArray[targetIndex];
      }
      catch(const char* /*exp*/)
      {
        bOutOfRange = true;
      }

      TEST_VERIFY( bOutOfRange == true, strTestName );
      std::cout << std::endl;
  }

  // TEST 5
  strTestName = "TEST: Get Value From Empty CArray";
  {
      CArray<std::size_t> predefineArray;

      bool bOutOfRange = false;
      try {
         predefineArray[0];
      }
      catch(const char* /*exp*/)
      {
         bOutOfRange = true;
      }

      TEST_VERIFY( bOutOfRange == true, strTestName );
      std::cout << std::endl;
  }

  // TEST 6
  strTestName = "TEST: Inset Value In Position";
  {
      CArray<std::size_t> predefineArray;
      predefineArray.push_back(1);
      predefineArray.push_back(3);

      const std::size_t newSize = predefineArray.size() + 1;
      const std::size_t pos = 1;
      const std::size_t val = 2;

      std::cout << "  Sourse array: " << predefineArray.print() << std::endl;

      predefineArray.insert(pos, val);

      std::cout << "  Target array: " << predefineArray.print() << std::endl;

      std::string str = predefineArray.print();
      TEST_VERIFY( predefineArray.size() == newSize &&
                   str == "['1'; '2'; '3']", strTestName);

      std::cout << std::endl;
  }

  // TEST 7
  strTestName = "TEST: Inset Value In Empty CArray";
  {
      CArray<std::size_t> predefineArray;

      std::size_t newSize = predefineArray.size() + 1;
      std::size_t pos = 0;
      std::size_t val = 1;

      std::cout << "  Sourse array: " << predefineArray.print() << std::endl;

      predefineArray.insert(pos, val);

      std::cout << "  Target array: " << predefineArray.print() << std::endl;

      TEST_VERIFY( predefineArray.size() == newSize &&
                   predefineArray[pos] == val, strTestName + " - 1");

      predefineArray.insert(++pos, ++val);
      ++newSize;

      std::cout << "  Target array: " << predefineArray.print() << std::endl;

      TEST_VERIFY( predefineArray.size() == newSize &&
                   predefineArray[pos] == val, strTestName + " - 2");

      std::cout << std::endl;
  }

  // TEST 8
  strTestName = "TEST: Erase Element from CArray";
  {
    CArray<std::size_t> predefineArray;
    predefineArray.push_back(10);
    predefineArray.push_back(11);
    predefineArray.push_back(12);
    predefineArray.push_back(13);
    predefineArray.push_back(14);

    std::cout << "  Sourse array: " << predefineArray.print() << std::endl;

    std::size_t newSize = predefineArray.size() - 1;

    predefineArray.erase(2);

    std::cout << "  Target array: " << predefineArray.print() << std::endl;

    TEST_VERIFY( predefineArray.size() == newSize,
                 strTestName + " - 1 From the Middle");

    predefineArray.erase(0);
    --newSize;

    std::cout << "  Target array: " << predefineArray.print() << std::endl;

    TEST_VERIFY( predefineArray.size() == newSize,
                 strTestName + " - 2 From Head");

    predefineArray.erase(predefineArray.size()-1);
    --newSize;

    std::cout << "  Target array: " << predefineArray.print() << std::endl;

    TEST_VERIFY( predefineArray.size() == newSize,
                 strTestName + " - 3 From Tail");

    std::cout << std::endl;
  }


  // TEST 9
  strTestName = "TEST: Clear CArray";
  {
    CArray<std::size_t> predefineArray;
    predefineArray.push_back(10);
    predefineArray.push_back(11);
    predefineArray.push_back(12);
    predefineArray.push_back(13);
    predefineArray.push_back(14);

    predefineArray.clear();

    std::cout << " CArray: " << predefineArray.print() << std::endl;

    TEST_VERIFY( predefineArray.size() == 0,
                 strTestName);

    std::cout << std::endl;
  }

  // TEST 10
  strTestName = "TEST: Create array with strings";
  {
      const std::size_t n = 6;
      CArray<std::string> a_str;

      a_str.push_back("We");
      a_str.push_back("Are");
      a_str.push_back("The");
      a_str.push_back("Champions");
      a_str.push_back("My");
      a_str.push_back("Friends");

      std::cout << "  CArray: " << a_str.print() << std::endl;
      TEST_VERIFY(a_str.size() == n, strTestName );
  }

  CArray<std::string>* s1 = new CArray<std::string>;
  std::cout << "  CArray: " << s1->print() << std::endl;
  std::cout << std::endl;

  // TEST 11
  strTestName = "TEST: Make a copy";
  {
      CArray<std::string> a_str;

      a_str.push_back("We");
      a_str.push_back("Are");
      a_str.push_back("The");
      a_str.push_back("Champions");
      a_str.push_back("My");
      a_str.push_back("Friends");

      CArray<std::string> b_str(a_str);

      std::string str = b_str.print();
      TEST_VERIFY( str == "['We'; 'Are'; 'The'; 'Champions'; 'My'; 'Friends']" && a_str.size() == b_str.size(), strTestName );
      std::cout << "  CArray: " << str << std::endl;
  }

  if (bResult == true)
  {
      std::cout <<  std::endl;
      std::cout << "ALL TESTS PASSED " << std::endl;
  }
  else
  {
      std::cout <<  std::endl;
      std::cout << "SOME TEST FAILED " << std::endl;
  }


}
