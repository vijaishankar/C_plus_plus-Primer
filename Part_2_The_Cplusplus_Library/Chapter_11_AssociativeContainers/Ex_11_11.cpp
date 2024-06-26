/************************************************************************************************************************************************************
 * @file Ex_11_11.cpp
 * @brief Exercise 11.11: Redefine bookstore without using decltype.
 * @date 2024-01-09
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

struct Sales_data;   
std::istream & read(std::istream &, Sales_data &); 


struct Sales_data{

friend std::istream & read(std::istream &is, Sales_data &item);     
friend std::ostream & print(std::ostream &os, const Sales_data &item);     
public :                            
    std::string isbn() const {      
        return book_no;
    }

    double avg_price() const;       
    Sales_data & combine(const Sales_data &rhs);

    
    Sales_data() : Sales_data("", 0, 0) {                    
        std::cout << "Sales_data() : invoked" << std::endl;
    } 

    Sales_data(std::istream & is) : Sales_data("",0,0) {   
        std::cout << "Sales_data(std::istream & is) : invoked" << std::endl;
        read(is, *this);                                   
    }

    
    Sales_data(const std::string book_no_p) : Sales_data(book_no_p,0,0) {   
        std::cout << "Sales_data(const std::string book_no_p) : invoked" << std::endl;
    }

    
    Sales_data(const std::string book_no_p, const unsigned units_sold_p, const double price) :
            book_no(book_no_p), units_sold(units_sold_p), revenue( units_sold_p * price ) {
                std::cout << "Sales_data(const std::string book_no_p, const unsigned units_sold_p, const double price) : invoked"
                          << std::endl;  
            }
    
private :                                          
    std::string book_no;                           
    unsigned units_sold = 0 ;                      
    double revenue = 0;                            
};

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs){
    return lhs.isbn() < rhs.isbn();
}

Sales_data & Sales_data::combine(const Sales_data &rhs){  
    units_sold += rhs.units_sold;                         
    revenue += rhs.revenue;

    return *this;                                   
}

std::istream & read(std::istream &is, Sales_data &item){
    std::cout << "Enter the transactin details[isbn count price] : \n";
    double price;
    is >> item.book_no >> item.units_sold >> price;
    item.revenue = item.units_sold * price;
    return is;
}

std::ostream & print(std::ostream &os, const Sales_data &item){
    os << item.book_no << " " << item.units_sold << " " << item.revenue ;
    return os;
}

inline double Sales_data::avg_price() const {
    return revenue / units_sold;
}

int main(){
    Sales_data book1, book2("c++primer"), book3("discrete mathmatics", 20,10.506), book4(std::cin);

    // a funtion's type is its[ return_type (param_type) ], * tells that it is a pointer to function
    std::set<Sales_data, bool (*)(const Sales_data &lhs, const Sales_data &rhs) > sales(compareIsbn);
    sales.insert(book3);
    sales.insert(book2);
    sales.insert(book1);
    sales.insert(book4);
   
    for(auto iter = sales.cbegin(); iter != sales.cend(); ++iter){
        print(std::cout, *iter) << std::endl;
    }

    return 0;
}

