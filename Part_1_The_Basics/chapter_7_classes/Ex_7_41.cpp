/************************************************************************************************************************************************************
 * @file Ex_7_41.cpp
 * @brief Exercise 7.41: Rewrite your own version of the Sales_data class to use delegating constructors. Add a 
 * statement to the body of each of the constructors that prints a message whenever it is executed. Write 
 * declarations to construct a Sales_data object in every way possible. Study the output until you are certain you 
 * understand the order of execution among delegating constructors.
 *
 * @date 2023-12-22
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>

struct Sales_data;   // forward declaration as read() declaration is using name Sales_data in its parameter list
std::istream & read(std::istream &, Sales_data &); // forward declaration Sales_data(std::istream &) constructor is usin read()

// definition of Sales_data class
struct Sales_data{
//  interface begins here
friend std::istream & read(std::istream &is, Sales_data &item);     //  by declaring read() as a friend, read() code will have access to non-public members of the class, friends are not affected by access specifier
friend std::ostream & print(std::ostream &os, const Sales_data &item);     //  every non-member function which is a part of the class interface to access non-public members need to declared as friend
public :                            //  members declarations following public access specifier can be accessed from user code, forms the interface of the class
    std::string isbn() const {      //   declared as const member function so that we can call isbn() for const objects
        return book_no;
    }

    double avg_price() const;       //  returns average price for the book
    Sales_data & combine(const Sales_data &rhs);

    //  constructors list begins
    Sales_data() : Sales_data("", 0, 0) {                    //   default constructor delegating work to three param constructor
        std::cout << "Sales_data() : invoked" << std::endl;
    } 

    //   constructor that takes one parameter of type istream reference
    Sales_data(std::istream & is) : Sales_data("",0,0) {    // delegating work to 3 param constructor to avoid undefined value incase of eof or invalid input
        std::cout << "Sales_data(std::istream & is) : invoked" << std::endl;
        read(is, *this);                                   
    }

    //  constructor that takes only isbn no, delegating work to 3 param constructor
    Sales_data(const std::string book_no_p) : Sales_data(book_no_p,0,0) {   
        std::cout << "Sales_data(const std::string book_no_p) : invoked" << std::endl;
     }

    //  constructor that takes isbn no, units sold, and revenue
    Sales_data(const std::string book_no_p, const unsigned units_sold_p, const double price) :
            book_no(book_no_p), units_sold(units_sold_p), revenue( units_sold_p * price ) {
                std::cout << "Sales_data(const std::string book_no_p, const unsigned units_sold_p, const double price) : invoked"
                          << std::endl;  
            }
    //  list of constructors ends here
//  interface ends here
//  implementation begins here
private :                                          //   member declarations following private access specifier can be accessed by only members not by user code
    std::string book_no;                           //   isbn no                     
    unsigned units_sold = 0 ;                      //   total no of units sold
    double revenue = 0;                            //   revenue from the total sale of this book
};

Sales_data & Sales_data::combine(const Sales_data &rhs){  //   returns reference of the object for which combine was called, it-
    units_sold += rhs.units_sold;                         //   -mimics the += operator's return value   
    revenue += rhs.revenue;

    return *this;                                   //  this is pointer which is rvalue, to get lvalue we dereference it
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
}

/**
 * Output :
 * Sales_data(const std::string book_no_p, const unsigned units_sold_p, const double price) : invoked
 * Sales_data() : invoked
 * Sales_data(const std::string book_no_p, const unsigned units_sold_p, const double price) : invoked
 * Sales_data(const std::string book_no_p) : invoked
 * Sales_data(const std::string book_no_p, const unsigned units_sold_p, const double price) : invoked
 * Sales_data(const std::string book_no_p, const unsigned units_sold_p, const double price) : invoked
 * Sales_data(std::istream & is) : invoked
 * Enter the transactin details[isbn count price] : 
 * hackersSlate
 * 45
 * 23.45
*/