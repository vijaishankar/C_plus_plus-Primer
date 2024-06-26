/************************************************************************************************************************************************************
 * @file Ex_10_28.cpp
 * @brief Exercise 10.28: Copy a vector that holds the values from 1 to 9 inclusive, into three other containers. Use an
 *        inserter, a back_inserter, and a front_inserter, respectivly to add elements to these containers. Predict how the
 *        output sequence varies by the kind of inserter and verify your predictions by running your programs
 * @date 2024-01-06
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>

void print(const std::vector<int> &vec){
    for( auto n : vec){
        std::cout << n << " ";
    }
}

int main(){
    std::vector<int> ivec{1,2,3,4,5,6,7,8,9};
    std::vector<int> b_ivec, i_ivec;
    std::deque<int> f_idq;   

    std::copy(ivec.begin(), ivec.end(), std::back_inserter(b_ivec));
    std::copy(ivec.begin(), ivec.end(), std::front_inserter(f_idq));     // vector doesn't have push_front() method
    std::copy(ivec.begin(), ivec.end(), std::inserter(i_ivec, i_ivec.begin()));

    std::cout << "List of elements added through back_inserter [same order as the original container] : " << std::endl;
    print(b_ivec);
    std::cout << std::endl;

    std::cout << "List of elements added through front_inserter [reverse order to the original container] : " << std::endl;
    for( auto n : f_idq){
        std::cout << n << " ";
    }
    std::cout << std::endl;

    std::cout << "List of elements added through inserter [same order as the original container] : " << std::endl;
    print(i_ivec);
    std::cout << std::endl;
    
    return 0;
}