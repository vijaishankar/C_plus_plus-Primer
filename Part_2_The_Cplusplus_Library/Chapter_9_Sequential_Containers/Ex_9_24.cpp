/************************************************************************************************************************************************************
 * @file Ex_9_24.cpp
 * @brief Exercise 9.24: Write a program that fetches the first element in a vector using at, the subscript operator, front,
 *        and begin. Test your program on an empty vector.
 * @date 2023-12-29
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <vector>

int main(){
    std::vector<int> ivec;
    std::cout << ivec.at(0) << std::endl;         // throws out of range exception
    std::cout << *ivec.begin() << std::endl;      // segmentation fault (core dumped)  
    std::cout << ivec.front() << std::endl;       // segmentation fault (core dumped)
    std::cout << ivec[0] << std::endl;            // segmentation fault (core dumped)

    return 0;
}

// compiled with g++-12 "c++20" standard