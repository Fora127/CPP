#include <unistd.h>
#include <iostream>

#include "ParamReceiver.h"
#include "Controller.h"

//template<typename T>
//void f(T data)
//{
//    static int i = 0;
//    ++i;
//    std::cout << i << std::endl;
//}

//int k=0;
//f<int>(k);
//f<int>(k);

//double d = 0.0;
//f<double>(d);

//std::string s = "123";

//f<std::string>(s);


int main()
{
    Controller controller;
    ParamReceiver receiver ( &controller );

    int i = 100;
    while( i-- )
    {
        double Y = receiver.checkInputValue("");
        receiver.setCurrentY(Y);
        std::cout << "Y: " << receiver.getCurrentY() << std::endl;
        usleep(50);
    }

    return 0;
}
