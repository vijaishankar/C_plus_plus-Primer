/************************************************************************************************************************************************************
 * @file Ex_13_13.cpp
 * @brief Exercise 13.13: A good way to understand copy-control members and constructors is to define a simple class with these
 *  members in which each member prints its name:
 * struct X {
 *      X() {std::cout << "X()" << std::endl;}
 *      X(const X&) {std::cout << "X(const X&)" << std::endl;}
 * };
 * Add the copy-assignment operator and destructor to X and write a program using X objects in various ways: Pass them as 
 * nonreference and reference parameters; dynamically allocate them; put them in containers; and so forth. Study the output
 * until you are certain you understand when and why each copy-control member is used. As you read the output, remember 
 * that the compiler can omit calls to the copy constructor.
 * @date 2024-01-23
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <memory>

struct X {
    static size_t count;
    std::string *ptr;
    int id;
    X(const std::string &str) : ptr(new std::string(str)), id(++count) {std::cout << "X(const std::string &) invoked, x" << id << std::endl;}
    X() : ptr(new std::string()),id(++count) {std::cout << "X() invoked, x" << id << std::endl;}
    X(const X& p) : ptr(new std::string(*(p.ptr))), id(++count) {std::cout << "X(const X&) invoked, x" << id << std::endl;}
    X& operator=(const X& p) {*ptr = *(p.ptr); std::cout << "operator=(const X&) invoked, x" << id << std::endl; return *this;}
    ~X() {delete ptr; std::cout << "~X() invoked, x" << id << std::endl;};
};

size_t X::count = 0;


X fun(X xarg){
    return xarg;
}

int main(){
    X x1("hello");
    X x2 = std::string("world");
    return 0;
}

/**
 * push_back, insert and emplace used copy_constructor to copy_construct a temp_object and then again copy_constructed the new object in the vector
 * X x1;  had default constructor
 * x1 = x2  //  copy-assignment operator used
 * new X;   //  default constructor
 * std::make_shared<X>()  //  default constructor
 * 
 * function(x1)  // copy_constructor to copy arg to param
 * return type as X  //  copy_constructor to copy return val to result of expression
 * result object destroyed 
 * followed by the destruction of param obj
 * destructor was called when delete was used on built-in pointer
 * 
*/