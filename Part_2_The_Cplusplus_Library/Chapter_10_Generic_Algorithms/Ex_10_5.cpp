/************************************************************************************************************************************************************
 * @file Ex_10_5.cpp
 * @brief Exercise 10.5: In the call to equal on rosters, what would happen if both rosters held C-style strings, 
 *        rather than library strings
 * @date 2024-01-04
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

//  ok : if both are const char*, compiler optimises the code in such a way, that same literal is stored only once, same
//          address is stored in differrent const char *. since the addressess are same, equal() compares addressess returns true
//      equal() on string type, and const char* type , value is compared
//      equal() on const char * and const char* type, address is compared 
//      https://github.com/Mooophy/Cpp-Primer/issues/227#issue-71759386        

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main(){
    const char arr1[3][4]{"one","two","thr"};
    const char arr2[3][4]{"one","two","thr"};
    std::vector<const char *> strvec1(std::begin(arr1), std::end(arr1));
    std::vector<const char *> strvec2(std::begin(arr2), std::end(arr2));
    std::cout << std::equal(strvec1.begin(), strvec1.end(), strvec2.begin()) << std::endl;  //  false

    std::cout << &strvec1[0] << " " << &strvec2[0]  << std::endl;

    std::vector<const char *> strvec3{"one","two","thr"};
    std::vector<const char *> strvec4{"one","two","thr"};
    std::cout << std::equal(strvec3.begin(), strvec3.end(), strvec4.begin()) << std::endl;  // true
    return 0;
}

// only address is compared
// in first case since we first initialise the arrays, the address differs so we get false
// in second case since we directly initialise, compiler stores the literal only once and stores the address in both vectors
// so we get true as both points to same address