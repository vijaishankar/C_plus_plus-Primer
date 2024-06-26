/************************************************************************************************************************************************************
 * @file Ex_13_48.cpp
 * @brief Exercise 13.48: Define a vector<String> and call push_back several times on that vector. Run your program and see
 * how often Strings are copied.
 * @date 2024-01-27
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include "Ex_13_44_String.cpp"
#include <iostream>
#include <vector>

int main(){
   std::vector<String> svec;
   svec.push_back("1");
   std::cout << "=============" << std::endl;
   svec.push_back("2");
std::cout << "=============" << std::endl;
   svec.push_back("3");
std::cout << "=============" << std::endl;
   svec.push_back("4");
std::cout << "=============" << std::endl;
   svec.push_back("5");
std::cout << "=============" << std::endl;
   svec.push_back("6");
std::cout << "=============" << std::endl;
   svec.push_back("7");
std::cout << "=============" << std::endl;

   svec.push_back("8");
std::cout << "=============" << std::endl;
   svec.push_back("9");
std::cout << "=============" << std::endl;

}