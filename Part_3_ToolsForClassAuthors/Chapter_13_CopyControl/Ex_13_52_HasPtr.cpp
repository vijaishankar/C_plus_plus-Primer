/************************************************************************************************************************************************************
 * @file Ex_13_52.cpp
 * @brief Exercise 13.53: As a matter of low-level efficiency, the HasPtr assignment operator is not ideal. Explain why. 
 * Implement a copy-assignment and move-assignment operator for HasPtr and compare the operations executed in your new 
 * move-assignment operator versus the copy-and-swap version
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
        : ps(new std::string(s)), i(0){ std::cout << "HasPtr(const std::string& s = std::string()) : " << std::endl;}

    // copy constructor    
    HasPtr(const HasPtr& hp) : ps(new std::string(*(hp.ps))), i(hp.i) {
        std::cout << "HasPtr(const HasPtr& hp) :" << std::endl;
    } 

    // move constructor
    HasPtr(HasPtr &&hp) : ps(hp.ps), i(hp.i){
        hp.ps = 0;
        std::cout << "HasPtr(HasPtr &&hp) : " << std::endl;
    }

    // copy-assignment operator
    HasPtr & operator=(HasPtr &rhs){
        std::cout << "operator=(HasPtr &rhs) :" << std::endl;
        if(this != &rhs){
            *ps = *rhs.ps;
            i = rhs.i;
        }    
        return *this;
    }

    // move assignment operator
    HasPtr & operator=(HasPtr &&rhs){
        std::cout << "operator=(HasPtr &&rhs) : " << std::endl;
        if(this != &rhs){
            swap(*this, rhs);
        };
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
        if(ps){
            std::cout << ps << " " << *ps << " " << i << std::endl;
        }else{
            std::cout << "empty" << std::endl;
        }
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
    HasPtr hp1("hello"), hp2("hello world"), hp3("welcome");
    std::cout << "--------------hp1 = hp2---------------------" << std::endl;
    hp1 = hp2;
    hp1.info();
    hp2.info(); 
    std::cout << "--------------hp1 = std::move(hp3)---------------------" << std::endl;
    hp1 = std::move(hp3);
    hp1.info();
    hp3.info();
    return 0;
}