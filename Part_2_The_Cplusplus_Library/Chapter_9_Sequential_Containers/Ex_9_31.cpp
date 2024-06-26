/************************************************************************************************************************************************************
 * @file Ex_9_31.cpp
 * @brief Exercise 9.31: The program on page 354 to remove even-valued elements and duplicate odd ones will not work on a list
 *        or forward_list. Why? Revise the program so that it works on these types as well.
 * @date 2023-12-30
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <list>
#include <forward_list>

int main(){
    std::vector<int> vi = {0,1,2,3,4,5,6,7,8,9};
    std::list<int> li(vi.cbegin(), vi.cend());
    std::forward_list<int> fli(li.cbegin(), li.cend());

    //  code to change list
    auto iter = li.begin(); 
    while (iter != li.end()) {
        if (*iter % 2) {
            iter = li.insert(iter, *iter);
            iter++;
            iter++;         //   list don't support iterator arithmatic, iter += 2
        } else
        iter = li.erase(iter); 
    }

    //  code to change forward list
    auto prev = fli.before_begin();
    auto curr = fli.begin();
    while(curr != fli.end()){
        if(*curr % 2){
            curr = fli.insert_after(curr , *curr);     
            prev = curr++;
        }else{
           curr = fli.erase_after(prev); 
        }
    }

    std::cout << "Numbers in forward_list : \n";
    for(auto n : fli){
        std::cout << n << " ";
    }
    std::cout << std::endl;

    std::cout << "Numbers in list : \n";
    for(auto n : li){
        std::cout << n << " "; 
    }
    std::cout << std::endl;

    return 0;
}