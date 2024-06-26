/************************************************************************************************************************************************************
 * @file Ex_7_40.cpp
 * @brief Exercise 7.40: Choose one of the following abstractions (or an abstraction of your own choosing). Determine
 *  what data are needed in the class. Provide an appropriate set of constructors. Explain your decisions.
 *      (a) Book        (b) Date        (c) Employee
 *      (d) Vehicle     (e) Object      (f) Tree
 * 
 * @date 2023-12-22
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

//  following code defines Date class
#include <iostream>
#include <ctime>
class Date {
public:
    typedef unsigned short number;
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
    Date date1(10,11,22);
    Date date2(22,12,23);
    std::cout << date1.get(0,0,0) << std::endl;
    std::cout << date2.get(0) << "/" << date2.get(0,0) << "/" << date2.get(0,0,0) << std::endl;
    date1.set(23,10,21);
    std::cout << date1.get(0,0,0) << std::endl;
    date1.set(12,24);
    std::cout << date1.get(0,0,0) << std::endl;
    date1.set(20);
    std::cout << date1.get(0,0,0) << std::endl;
}