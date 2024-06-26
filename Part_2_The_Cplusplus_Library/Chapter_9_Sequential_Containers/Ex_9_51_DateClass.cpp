/************************************************************************************************************************************************************
 * @file Ex_9_51_DateClass.cpp
 * @brief Exercise 9.51: Write a class that has three unsigned members representing year, month, and day. Write a constructor
 *        that takes a string representing a date. Your constructor should handle a variety of date formats, such as 
 *        January 1, 1900, 1/1/1900, Jan 1, 1900, and so on.
 * @date 2024-01-02
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>

class Date{
    public :
        typedef unsigned short dateNumeral;    
        Date(const std::string &seq);
        std::string get();
    private :
        dateNumeral date = 0;
        std::string month;
        dateNumeral year = 0;
};

std::string Date::get(){
    return std::to_string(date) + "-" + month + "-" + std::to_string(year);
}

Date::Date(const std::string &seq){
    // January 1,1900
    // 1/1/1900
    // Jan 1,1900
    // 1-1-1900
    // 1 Jan 1900
    // 1 January 1900
    std::string alphabets;
    for( char ch = 'a'; ch != 'z'; ++ch){
        alphabets.push_back(ch);
        alphabets.push_back(std::toupper(ch));
    }

    int num;
    std::string::size_type pos = 0, lpos = 0;
    
    //  code to extract month name from the string
    if((pos = seq.find_first_of(alphabets)) != std::string::npos){
        lpos = seq.find_last_of(alphabets);
        month = seq.substr(pos,lpos - pos + 1);
    }

    pos = 0;
    while( (pos = seq.find_first_of("0123456789", pos)) != std::string::npos){
        num = stoi(seq.substr(pos));
        pos += std::to_string(num).size();
        if(num > 31){
            year = num;
        }else if(num > 12 && month.empty()){
            month = std::to_string(num);
        }else{
            if( date == 0 ){
                date = num;
            }else{
                month = std::to_string(num);
            }
        }
    }       
}

int main(){
    Date d1("September 15,2000"), d2("Jan 1,1900"), d3("11 Mar, 2023");
    Date d4("31 August 1967"), d5("2/12/2009"), d6("1-11-1453");

    std::cout << d1.get() << std::endl;
    std::cout << d2.get() << std::endl;
    std::cout << d3.get() << std::endl;
    std::cout << d4.get() << std::endl;
    std::cout << d5.get() << std::endl;
    std::cout << d6.get() << std::endl;
    
    return 0;
}