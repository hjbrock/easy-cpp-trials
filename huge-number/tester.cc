/*
 * Tester file for huge_number.h and huge_number.cc
 */

#include <string>
#include "huge_number.h"
#include <iostream>

using namespace std;

int main ()
{
    huge_number zero;
    huge_number h1("123456789012345678901234567891");
    huge_number h2("2");
    huge_number h3("32093847");
    huge_number h4("0");

    h3 = h1 / h2;
    cout << h1.get_value() << endl;
    cout << h2.get_value() << endl;
    cout << h3.get_value() << endl;

    h3 = h1 % h4;
    cout << h4.get_value() << endl;
}
