/************************************************************************************************************************************************************
 * @file Ex_10_31.cpp
 * @brief Exercise 10.31: Update the program from the previous exercise so that it prints only the unique elements. Your program
 *        should use unqiue_copy (§ 10.4.1, p. 403).
 * @date 2024-01-06
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main(){
    std::cout << "Enter the list of nums : " << std::endl;
    std::istream_iterator<int> i_istrm_iter(std::cin), end;     // initialises an istream_iterator to read int from cin
    std::vector<int> ivec(i_istrm_iter, end);       //  initialises a vector of int from cin using istream_iterator and end_iter

    std::sort(ivec.begin(), ivec.end());    // sorts the vector
    std::ostream_iterator<int> i_ostrm_iter(std::cout , " ");   // initialises an ostream_iterator to write int followed by space to cout 
    std::cout << std::endl;
    std::unique_copy(ivec.begin(), ivec.end(), i_ostrm_iter);      // copies unique items in the vector to cout using ostream_iterator.

    return 0;
}