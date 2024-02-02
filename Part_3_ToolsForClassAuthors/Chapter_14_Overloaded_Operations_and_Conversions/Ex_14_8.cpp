/************************************************************************************************************************************************************
 * @file Ex_14_8.cpp
 * @brief Exercise 14.8: Define an output operator for the class you chose in exercise 7.40 from § 7.5.1 (p. 291).
 * @date 2024-01-29
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

//  following code defines Date class
#include <iostream>
#include <ctime>
#include <string>

class Date {
public:
    typedef unsigned short number;
    friend std::ostream & operator<<(std::ostream &os, const Date &dt);
    Date(number date_p, number month_p, number year_p) 
        :   date(date_p), month(month_p), year(year_p) { }
    void set(number date_p, number month_p, number year_p);
    std::string get(number dummy1 , number dummy2 , number dummy3) const;
    std::string get(number) const ;
    std::string get(number , number ) const ;
private:
    number date;
    number month;
    number year;
};

std::ostream & operator<<(std::ostream &os, const Date &dt){
    os << dt.date << "-" << dt.month << "-" << dt.year;
    return os;
}

void Date::set(number date_p = 0, number month_p = 0, number year_p = 0){
    date = date_p ? date_p : date;
    month = month_p ? month_p : month;
    year = year_p ? year_p : year;
}

std::string Date::get(number , number , number ) const {
    return std::to_string(date) + " " + std::to_string(month) + " " +  std::to_string(year);
}

std::string Date::get(number) const {
    return std::to_string(date);
}

std::string Date::get(number , number) const {
    return std::to_string(date) + " " + std::to_string(month);
}

int main(){
    Date d1(29,1,2024);
    std::cout << d1 << std::endl;
}