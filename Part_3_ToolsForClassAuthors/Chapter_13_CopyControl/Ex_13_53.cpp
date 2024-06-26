/************************************************************************************************************************************************************
 * @file Ex_13_53.cpp
 * @brief Exercise 13.54: What would happen if we defined a HasPtr move-assignment operator but did not change the copy-and-swap
 * operator? Write code to test your answer.
 * @date 2024-01-27
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

//  class defined to behave like value, (ie) object's state is independent from the other
class HasPtr {
    friend void swap(HasPtr &, HasPtr &);
public:
    // constructor that takes a string with empty string as a default value to behave as default constructor
    HasPtr(const std::string& s = std::string())
        : ps(new std::string(s)), i(0){}

    // copy constructor    
    HasPtr(const HasPtr& hp) : ps(new std::string(*(hp.ps))), i(hp.i) {
        std::cout << "copy constructor called" << std::endl;
    } 

    // copy-assignment operator
    HasPtr & operator=(HasPtr rhs){
        swap(*this, rhs);
        return *this;
    }

    // move-assignment operator
    HasPtr & operator=(HasPtr &&rhs){
        if(this != &rhs){
            swap(*this, rhs);
        }
        return *this;
    }

    // destructor 
    ~HasPtr(){
        delete ps;
        std::cout << "destructor is run and the memory allocated to hold the string is deleted" << std::endl;
    }

    // comparison operator
    bool operator<(const HasPtr &rhs){
        std::cout << *ps << " < " << *rhs.ps << std::endl;
        return *ps < *rhs.ps;
    }

    void info(){
        std::cout << ps << " " << *ps << " " << i << std::endl;
    }

    std::string & get_val(){
        return *ps;
    }
private :
    std::string* ps;
    int i;
};
void swap(HasPtr &lhs, HasPtr &rhs){
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
    std::cout << "successfully swaped" << std::endl;
}

int main(){
    HasPtr hp1("hello"), hp2("world");
    hp1 = std::move(hp2);
    return 0;
}

/************************************************************************************************************************************************************
 * ambigous call when we try to use '=' operator with rvalue, as both
 * operator=(HasPtr rhs)
 * operator=(HasPtr &&rhs)
 * can be called, no definition is better than the other
 * 
 *************************************************************************************************************************************************************/