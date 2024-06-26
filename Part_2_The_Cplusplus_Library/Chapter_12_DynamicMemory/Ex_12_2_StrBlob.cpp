/************************************************************************************************************************************************************
 * @file Ex_12_2.cpp
 * @brief Exercise 12.2: Write your own version of the StrBlob class including the const versions of front and back
 * @date 2024-01-13
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

//  libraries needed
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <initializer_list>
#include <exception>

// StrBlob, all objects share the same underlying data, vector of strings
class StrBlob{
    public :
        // type alias for size
        typedef std::vector<std::string>::size_type size_type;

        // constructors
        StrBlob();
        StrBlob(const std::initializer_list<std::string> &il);

        // size operations
        size_type size() const;
        bool empty() const;

        // access operations
        std::string& front();
        std::string& back();
        const std::string & front() const;
        const std::string & back() const;
        void push_back(const std::string &word);
        void pop_back();

    private :
        // shared_ptr to point to container
        std::shared_ptr<std::vector<std::string>> data;
        void check(size_type i, const std::string &msg) const ;
};

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}

StrBlob::StrBlob(const std::initializer_list<std::string> &il) : data(std::make_shared<std::vector<std::string>>(il)) {}

StrBlob::size_type StrBlob::size() const {
    return data->size();
}

bool StrBlob::empty() const {
    return data->empty();
}

std::string & StrBlob::front(){
    check(0,"container is empty");
    return data->front();
}

std::string & StrBlob::back(){
    check(0,"container is empty");
    return data->back();
}

const std::string & StrBlob::front() const{
    check(0,"container is empty");
    return data->front();
} 

const std::string & StrBlob::back() const{
    check(0, "container is empty");
    return data->back();
}

void StrBlob::push_back(const std::string &word) {
    data->push_back(word);
}

void StrBlob::pop_back() {
    check(0, "container is empty");
    data->pop_back();
}

void StrBlob::check(size_type i, const std::string &msg) const {
    if( i >= data->size()){
        throw std::runtime_error(msg);
    }
}

int main(){
    StrBlob b1, b2({"one","two","three","four","five"});
    const StrBlob b3({"discrete","mathematics","c++ primer"});

    std::cout << "b1.size() : " << b1.size() << std::endl;
    std::cout << "b2.size() : " << b2.size() << std::endl;
    std::cout << "b3.size() : " << b3.size() << std::endl;

    for(int i = 0 ; i < 5; ++i){
        b1.push_back(std::to_string(i));
    }

    std::cout << "b1.size() : " << b1.size() << std::endl;
    std::cout << "b1.front() : " << b1.front() << "  b1.back() : " << b1.back() << std::endl;

    b2.front() = "zero";
    while(b2.size()){
        std::cout << b2.back() << " ";
        b2.pop_back();
    }

    std::cout << std::endl;
    std::cout << "b3.front() : " << b3.front() << "  b3.back() : " << b3.back() << std::endl; 

    
}


