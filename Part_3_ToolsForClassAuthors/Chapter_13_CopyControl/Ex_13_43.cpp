/************************************************************************************************************************************************************
 * @file EX_13_42.cpp
 * @brief Exercise 13.43: Rewrite the free member to use for_each and a lambda (§ 10.3.2,p. 388) in place of the for loop to 
 * destroy the elements. Which implementation do you prefer, and why?
 * @date 2024-01-26
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
    public :
        StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
        StrVec(const StrVec &);
        StrVec & operator=(const StrVec &rhs);
        StrVec(const std::initializer_list<std::string> &il);
        size_t size() const ;
        size_t capacity() const;
        void reserve(const size_t sz);
        void push_back(const std::string &);
        const std::string *begin() const ;
        const std::string *end() const ;
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

StrVec::StrVec(const StrVec &source){
    auto new_data = alloc_n_copy(source.begin(), source.end());
    elements = new_data.first;
    first_free = cap = new_data.second;
}

StrVec & StrVec::operator=(const StrVec &rhs){
    auto new_data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = new_data.first;
    first_free = cap = new_data.second;

    return *this;
}

StrVec::StrVec(const std::initializer_list<std::string> &il){
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
    size_t new_capacity;
    if (!sz) {
        new_capacity = size() ? 2 * size() : 1;
    } else if (sz && sz > capacity()) {
        new_capacity = sz;
    } else {
        return;
    }
    auto new_elements = alloc.allocate(new_capacity);
    auto dest = new_elements;
    auto beg = elements;
    while(beg != first_free){
        std::construct_at(dest++, std::move(*beg++));
    }
    free();
    elements = new_elements;
    first_free = dest;
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
        std::for_each(elements, first_free,[](std::string &p){std::destroy_at(&p);});
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


int main(){
    StrVec svec1, svec2({"alpha","beta","gamma","delta","echo"}), svec3(svec2);

    print(svec1);
    print(svec2);
    print(svec3);
    std::cout << "svec1 = svec2" << std::endl;
    svec1 = svec2;
    print(svec1);

    svec1.push_back("out");
    svec2.push_back("friday");  
    svec3.push_back("goa");    
    svec3.push_back("henry");
    

    std::cout << "after push_back" << std::endl;
    print(svec1);
    print(svec2);
    print(svec3);
    StrVec svec4;
    for(auto i = 1; i < 15; ++i){
        std::cout << svec4.size() << " " << svec4.capacity() << std::endl;
        svec4.push_back(std::to_string(i)); 
    }
    svec4.reserve(17);
    std::cout << svec4.size() << " " << svec4.capacity() << std::endl;
    svec4.push_back("15");
    svec4.push_back("16");
    svec4.push_back("17");
    std::cout << svec4.size() << " " << svec4.capacity() << std::endl;
    svec4.push_back("18");
    svec4.push_back("19");
    std::cout << svec4.size() << " " << svec4.capacity() << std::endl;
    

    return 0;
}

/************************************************************************************************************************************************************
 * old version is easy to understand and write, and moreover destruction should be done at reverse order. But since our class
 * doesn't define operators we won't be able to pass reverse iterators to the for_each() to treverse the sequence in reverse.
 *      Destruction done at reverse is performance effective than normal order.
 * 
 *************************************************************************************************************************************************************/