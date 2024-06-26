/************************************************************************************************************************************************************
 * @file Ex_16_62.cpp
 * @brief Exercise 16.62: Define your own version of hash<Sales_data> and define an unordered_multiset of Sales_data
 * objects. Put several transactions into the container and print its contents.
 * @date 2024-02-17
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/


#include <iostream>
#include <string>
#include <unordered_set>



template <class T> class hash;  // template declaration of std::hash is required to declare a version a friend

class Sales_data{      
public :        
    friend class std::hash<Sales_data>;  // Sales_data version of std::hash is declared as friend
    friend std::ostream & operator<<(std::ostream &os, const Sales_data &source);    
    friend std::istream & operator>>(std::istream &is, Sales_data &source);  
    bool operator==(const Sales_data &rhs) const {
        std::cout << "inside == " << std::endl;
        return book_no == rhs.book_no && 
               units_sold == rhs.units_sold &&
               revenue == rhs.revenue;
    }

    Sales_data operator+(const Sales_data &rhs);
    Sales_data & operator+=(const Sales_data &rhs);             
    std::string isbn() const {      
        return book_no;
    }

    double avg_price() const;       
    Sales_data & combine(const Sales_data &rhs);

    Sales_data() : Sales_data("", 0, 0) {                   
        std::cout << "Sales_data() : invoked" << std::endl;
    } 

    explicit Sales_data(std::istream & is) : Sales_data("",0,0) {    
        std::cout << "Sales_data(std::istream & is) : invoked" << std::endl;
        is >> *this;                                   
    }

    explicit Sales_data(const std::string book_no_p) : Sales_data(book_no_p,0,0) {   
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

Sales_data Sales_data::operator+(const Sales_data &rhs){
    Sales_data temp(*this);
    return temp += rhs;
}

Sales_data & Sales_data::operator+=(const Sales_data &rhs){
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;

    return *this;
}             

std::istream & operator>>(std::istream &is, Sales_data &source){
    double price;
    is >> source.book_no >> source.units_sold >> price;
    if (is){     //  checks if read was successfull
        source.revenue = price * source.units_sold;
    } else {
        source = Sales_data();
    }

    return is;
}

std::ostream & operator<<(std::ostream &os, const Sales_data &item){
    os << item.book_no << " " << item.units_sold << " " << item.revenue ;
    return os;
}

Sales_data & Sales_data::combine(const Sales_data &rhs){  
    units_sold += rhs.units_sold;                         
    revenue += rhs.revenue;

    return *this;                                   
}

inline double Sales_data::avg_price() const {
    return revenue / units_sold;
}

namespace std {
    template <> 
    struct hash<Sales_data> {
        typedef Sales_data argument_type;
        typedef size_t return_type;
        size_t operator()(const Sales_data &s) const ;
    };
}

size_t std::hash<Sales_data>::operator()(const Sales_data &s) const {
    std::cout << "inside hash" << std::endl;
    return hash<std::string>()(s.book_no) ^ 
           hash<size_t>()(s.units_sold) ^
           hash<double>()(s.revenue);
}

int main() {
    std::unordered_multiset<Sales_data> transactions{{"delta", 90, 100}, {"beta", 90,100}, {"alpha", 90,100}, {"charlie", 90, 100}};
    for(auto &s : transactions) {
        std::cout << s << std::endl;
    }
    
    return 0;
}