#pragma once


#define TEST_VERIFY(statement, testname) \
do {\
    if ( static_cast<bool>(statement) )\
        std::cout << "PASSED";\
    else\
        std::cout << "FAILED";\
    std::cout << " : " << testname << std::endl;\
} while (false)

void CommonTest()
{
    // TEST1
    std::string strTestName = "TEST: Create definitive CArray";
    {
        CArray<int> predefineArray;
        predefineArray.push_back(10);
        predefineArray.push_back(11);
        predefineArray.push_back(12);

        std::string str = predefineArray.printArray();
        TEST_VERIFY( str == "['10'; '11'; '12']" && predefineArray.size() == 3, strTestName );
        std::cout << "  CArray: " << str << std::endl;
        std::cout << std::endl;
    }

    // TEST2
    strTestName = "TEST: Create CArray with random numbers";
    {
        const unsigned int n = 20;
        CArray<int> a2;

        for(int i=0; i<n; ++i)
        {
            a2.push_back(rand()%100);
        }

        TEST_VERIFY(a2.size() == n, strTestName );
        std::cout << "  CArray: " << a2.printArray() << std::endl;
        std::cout << std::endl;
    }

    // TEST3
    strTestName = "TEST: Operator[]";
    {
        CArray<int> predefineArray;
        predefineArray.push_back(0);
        predefineArray.push_back(1);
        predefineArray.push_back(2);
        predefineArray.push_back(3);
        predefineArray.push_back(4);

        int res;

        for(int i=0; i< predefineArray.size(); i++)
        {
            bool bOutOfRange = false;
            try {
             res = predefineArray[i];
            }
            catch(const char* exp)
            {
                bOutOfRange = true;
            }
            TEST_VERIFY( res == i, strTestName );
        }
        std::cout << std::endl;
    }

    // TEST4
    strTestName = "TEST: Out Of Range";
    {
        CArray<int> predefineArray;
        predefineArray.push_back(10);
        predefineArray.push_back(11);
        predefineArray.push_back(12);

        const unsigned int targetIndex = predefineArray.size();

        bool bOutOfRange = false;
        try {
          int y = predefineArray[targetIndex];
        }
        catch(const char* exp)
        {
            bOutOfRange = true;
        }

        TEST_VERIFY( bOutOfRange == true, strTestName );
        std::cout << std::endl;
    }

    // TEST5
    strTestName = "TEST: Get Value From Empty CArray";
    {
        CArray<int> predefineArray;

        bool bOutOfRange = false;
        try {
          int y = predefineArray[0];
        }
        catch(const char* exp)
        {
            bOutOfRange = true;
        }

        TEST_VERIFY( bOutOfRange == true, strTestName );
        std::cout << std::endl;
    }

    // TEST6
    strTestName = "TEST: Inset Value In Position";
    {
        CArray<int> predefineArray;
        predefineArray.push_back(1);
        predefineArray.push_back(3);

        const unsigned int newSize = predefineArray.size() + 1;
        const unsigned int pos = 1;
        const unsigned int val = 2;

        std::cout << "  Sourse array: " << predefineArray.printArray() << std::endl;

        predefineArray.insert(pos, val);

        std::cout << "  Target array: " << predefineArray.printArray() << std::endl;

        std::string str = predefineArray.printArray();
        TEST_VERIFY( predefineArray.size() == newSize &&
                     str == "['1'; '2'; '3']", strTestName);


        std::cout << std::endl;
    }

    // TEST7
    strTestName = "TEST: Inset Value In Empty CArray";
    {
        CArray<int> predefineArray;

        unsigned int newSize = predefineArray.size() + 1;
        unsigned int pos = 0;
        unsigned int val = 1;

        std::cout << "  Sourse array: " << predefineArray.printArray() << std::endl;

        predefineArray.insert(pos, val);

        std::cout << "  Target array: " << predefineArray.printArray() << std::endl;

        TEST_VERIFY( predefineArray.size() == newSize &&
                     predefineArray[pos] == val, strTestName + " - 1");

        predefineArray.insert(++pos, ++val);
        ++newSize;

        std::cout << "  Target array: " << predefineArray.printArray() << std::endl;

        TEST_VERIFY( predefineArray.size() == newSize &&
                     predefineArray[pos] == val, strTestName + " - 2");

        std::cout << std::endl;
    }

    // TEST7
    strTestName = "TEST: Erase Element from CArray";
    {
      CArray<int> predefineArray;
      predefineArray.push_back(10);
      predefineArray.push_back(11);
      predefineArray.push_back(12);
      predefineArray.push_back(13);
      predefineArray.push_back(14);

      std::cout << "  Sourse array: " << predefineArray.printArray() << std::endl;

      unsigned int newSize = predefineArray.size() - 1;

      predefineArray.erase(2);

      std::cout << "  Target array: " << predefineArray.printArray() << std::endl;

      TEST_VERIFY( predefineArray.size() == newSize,
                   strTestName + " - 1 From the Middle");

      predefineArray.erase(0);
      --newSize;

      std::cout << "  Target array: " << predefineArray.printArray() << std::endl;

      TEST_VERIFY( predefineArray.size() == newSize,
                   strTestName + " - 2 From Head");

      predefineArray.erase(predefineArray.size()-1);
      --newSize;

      std::cout << "  Target array: " << predefineArray.printArray() << std::endl;

      TEST_VERIFY( predefineArray.size() == newSize,
                   strTestName + " - 3 From Tail");

      std::cout << std::endl;
    }


    // TEST7
    strTestName = "TEST: Clear CArray";
    {
      CArray<int> predefineArray;
      predefineArray.push_back(10);
      predefineArray.push_back(11);
      predefineArray.push_back(12);
      predefineArray.push_back(13);
      predefineArray.push_back(14);

      predefineArray.clear();

      std::cout << " CArray: " << predefineArray.printArray() << std::endl;


      TEST_VERIFY( predefineArray.size() == 0,
                   strTestName);

      std::cout << std::endl;
    }

    // TEST
    strTestName = "TEST: Create array with strings";
    {
        const unsigned int n = 6;
        CArray<std::string> a_str;

        a_str.push_back("We");
        a_str.push_back("Are");
        a_str.push_back("The");
        a_str.push_back("Champions");
        a_str.push_back("My");
        a_str.push_back("Friends");

        std::cout << "  CArray: " << a_str.printArray() << std::endl;
        TEST_VERIFY(a_str.size() == n, strTestName );
    }

    CArray<std::string>* s1 = new CArray<std::string>;
    std::cout << "  CArray: " << s1->printArray() << std::endl;
}
