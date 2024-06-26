/************************************************************************************************************************************************************
 * @file Ex_10_11.cpp
 * @brief Exercise 10.11: Write a program that uses stable_sort and isShorter to sort a vector passed to your version of elimDups. Print the vector
 *        to verify that your program is correct.
 * @date 2024-01-05
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void elimDups(std::vector<std::string> &sourcVec);
bool isShorter(const std::string &lhs, const std::string &rhs){
    return lhs.size() < rhs.size();
}

int main(){
    std::vector<std::string> strvec;
    std::cout << "Enter the list of words :\n";
    std::string word;
    while(std::cin >> word){
        strvec.push_back(word);
    }

    std::cout << "\nList of words entered : "<< std::endl; 
    for( auto s : strvec){
        std::cout << s << " ";
    }

    elimDups(strvec);
    std::cout << "\nafter eliminating duplicates:" << std::endl;
    for( auto s : strvec){
        std::cout << s << " ";
    }
    
    //  code to sort the list based on length but maintaining original alphabetical order
    std::stable_sort(strvec.begin(), strvec.end(), isShorter);
    std::cout << "\nlist after stable sort :" << std::endl;
    for( auto s : strvec){
        std::cout << s << " ";
    }

    return 0;

}

void elimDups(std::vector<std::string> &sourceVec){
    // sort() the elements in the given sequence
    std::sort(sourceVec.begin(), sourceVec.end());
    std::cout << "\n\nList after sorted : " << std::endl;
    for( auto s : sourceVec){
        std::cout << s << " ";
    }
    std::cout << "[end of list]" << std::endl;

    //  unique() rearranges the elements such that, elements appear only once in the front by writing over the adjusant duplicates
    //  and returns the end of the unique range
    auto endOfUnique = std::unique(sourceVec.begin(), sourceVec.end());
    std::cout << "\nUnique list with duplicate words : " << std::endl;
    for( auto s : sourceVec){
        std::cout << s << " ";
    }
    std::cout << "[end of list]" << std::endl;    //  as the duplicate words are overwriten with the next unique word eventualy we get a empty string 

    //  code to erase the duplicate words
    sourceVec.erase(endOfUnique, sourceVec.end());
    std::cout << "\nunique words with out duplicates : " << std::endl;
    for( auto s : sourceVec){
        std::cout << s << " ";
    }
    std::cout << "[end of list]" << std::endl;

}