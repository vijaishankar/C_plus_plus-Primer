/************************************************************************************************************************************************************
 * @file Ex_14_23.cpp
 * @brief Exercise 14.23: Define an initializer_list assignment operator for your version of the StrVec class.
 * @date 2024-01-30
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <string>
#include <initializer_list>

class StrVec{
    friend void swap(StrVec &lhs, StrVec &rhs);
    friend bool operator<(const StrVec &lhs, const StrVec &rhs);
    friend bool operator==(const StrVec &lhs, const StrVec &rhs);
    friend bool operator!=(const StrVec &lhs, const StrVec &rhs);
    public :
        StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
        StrVec(const StrVec &);
        StrVec(StrVec &&) noexcept;
        StrVec & operator=(const StrVec &rhs);
        StrVec & operator=(StrVec &&rhs) noexcept;
        StrVec(const std::initializer_list<std::string> &il);
        size_t size() const ;
        size_t capacity() const;
        void reserve(const size_t sz);
        void push_back(const std::string &);
        const std::string *begin() const ;
        const std::string *end() const ;
        StrVec & operator=(const std::initializer_list<std::string> &il);
        ~StrVec(){ free(); }

    private :
        std::string *elements;
        std::string *first_free;
        std::string *cap;

        std::allocator<std::string> alloc;
        void realloc(const size_t sz = 0);
        void check_n_alloc();
        std::pair<std::string *, std::string *> alloc_n_copy(const std::string *b, const std::string *e);
        void free();
};

StrVec & StrVec::operator=(const std::initializer_list<std::string> &il){
    StrVec temp(il);
    swap(*this, temp);
    return *this; 
}
StrVec::StrVec(const StrVec &source){
    std::cout << "StrVec::StrVec(const StrVec &source)" << std::endl;
    auto new_data = alloc_n_copy(source.begin(), source.end());
    elements = new_data.first;
    first_free = cap = new_data.second;
}

StrVec::StrVec(StrVec &&source) noexcept : elements(source.elements), first_free(source.first_free), cap(source.cap){
    std::cout << "StrVec::StrVec(StrVec &&source) noexcept : " << std::endl;
    source.elements = source.first_free = source.cap = nullptr;
}


StrVec & StrVec::operator=(const StrVec &rhs){
    std::cout << "StrVec::operator=(const StrVec &rhs) : " << std::endl;
    auto new_data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = new_data.first;
    first_free = cap = new_data.second;

    return *this;
}

void swap(StrVec &lhs, StrVec &rhs){
    std::cout << "void swap(StrVec &lhs, StrVec &rhs) : " << std::endl;
    using std::swap;
    swap(lhs.elements, rhs.elements);
    swap(lhs.first_free, rhs.first_free);
    swap(lhs.cap, rhs.cap);
}

StrVec & StrVec::operator=(StrVec &&rhs) noexcept{
    std::cout << "StrVec::operator=(StrVec &&rhs) noexcept : " << std::endl;
    if(this != &rhs){
        swap(*this, rhs);
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }

    return *this;
}


StrVec::StrVec(const std::initializer_list<std::string> &il){
    std::cout << "StrVec::StrVec(const std::initializer_list<std::string> &il) : " << std::endl;
    auto data = alloc_n_copy(il.begin(), il.end());
    elements = data.first;
    first_free = cap = data.second;
}

size_t StrVec::size() const {
    return first_free - elements;
}

size_t StrVec::capacity() const{
    return cap - elements;
}

void StrVec::reserve(const size_t sz) {
    realloc(sz);
}

void StrVec::push_back(const std::string &str){
    check_n_alloc();
    std::construct_at(first_free++, str);
}

const std::string *StrVec::begin() const{
    return elements;
}

const std::string *StrVec::end() const{
    return first_free;
}

void StrVec::realloc(const size_t sz){
    std::cout << "StrVec::realloc(const size_t sz) : " << std::endl;
    size_t new_capacity;
    if (!sz) {
        new_capacity = size() ? 2 * size() : 1;
    } else if (sz && sz > capacity()) {
        new_capacity = sz;
    } else {
        return;
    }
    auto new_elements = alloc.allocate(new_capacity);
    auto new_first_free = std::uninitialized_copy(std::make_move_iterator(elements), std::make_move_iterator(first_free), new_elements);
    free();
    elements = new_elements;
    first_free = new_first_free;
    cap = elements + new_capacity;
}

void StrVec::check_n_alloc(){
    if(first_free == cap)
        realloc();
}

std::pair<std::string *, std::string *> StrVec::alloc_n_copy(const std::string *b, const std::string *e){
    auto new_elements = alloc.allocate(e - b);
    auto first_free = std::uninitialized_copy(b, e, new_elements);
    return {new_elements, first_free};
}

void StrVec::free(){
    if(elements){
        while(first_free != elements){
            std::destroy_at(--first_free);
        }
    }
    alloc.deallocate(elements, cap - elements);
}   
void print(const StrVec &svec){
    if(svec.size() == 0){
        std::cout << "list is empty" << std::endl;
        return;
    }

    std::cout << "====================================================" << std::endl << "##  ";
    for(auto iter = svec.begin(); iter != svec.end(); ++iter){
        std::cout << *iter << " ";
    }
    std::cout << "  ##" << std::endl;
    return;
}

bool operator==(const StrVec &lhs, const StrVec &rhs){
    if(lhs.size() != rhs.size()){
        return 0;
    }

    auto iterlhs = lhs.begin();
    auto iterrhs = rhs.begin();
    while(iterlhs != lhs.end()){
        if(*iterlhs++ != *iterrhs++){
            return 0;
        }
    }
    return 1;
}

bool operator!=(const StrVec &lhs, const StrVec &rhs){
    return !(lhs == rhs);
}

bool operator<(const StrVec &lhs, const StrVec &rhs){
    auto iterlhs = lhs.begin();
    auto iterrhs = rhs.begin();
    if(lhs.size() == rhs.size()){
        while(iterlhs != lhs.end()){
            if(*iterlhs++ > *iterrhs++){
                return 0;
            }
        }
        return 1;
    } else if (lhs.size() < rhs.size()) {
        auto iterlhs = lhs.begin();
        auto iterrhs = rhs.begin();
        while(iterlhs != lhs.end()){
            if(*iterlhs++ > *iterrhs++){
                return 0;
            }
        }
        return 1;
    } else {
        auto iterlhs = lhs.begin();
        auto iterrhs = rhs.begin();
        while(iterrhs != rhs.end()){
            if(*iterlhs++ > *iterrhs++){
                return 0;
            }
        }
        return 0;
    }
}

int main(){
    StrVec svec1;
    svec1 = {"alpha", "beta", "gamma"};
    print(svec1);

}