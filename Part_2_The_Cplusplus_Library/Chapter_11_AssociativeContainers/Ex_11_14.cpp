/************************************************************************************************************************************************************
 * @file Ex_11_14.cpp
 * @brief Exercise 11.14: Extend the map of children to their family name that you wrote for the exercises in § 11.2.1 (p. 424)
 *        by having the vector store a pair that holds a child’s name and birthday.
 * @date 2024-01-09
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <map>
#include <vector>

int main(){
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> family;  // each element is a pair of string and a vector of string-string pair

    std::string last_name;
    std::string first_name;
    std::string dob;
    std::cout << "Enter the family details [last_name first_name] : " << std::endl;
    while(std::cin >> last_name >> first_name >> dob){
        family[last_name].push_back({first_name, dob});   //  the value fetched is a vector, so we use vector's push_back() member to add the pair
    }

    for( auto f : family){   //  f contains string and a vector of pairs
        std::cout << "family's last name : " << f.first << std::endl;
        for( auto c : f.second){  // c contains string and string
            std::cout << "  " << c.first << " " << c.second << std::endl;
        }
    }

    return 0;
}