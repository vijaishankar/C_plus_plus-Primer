/************************************************************************************************************************************************************
 * @file Ex_13_49.cpp
 * @brief Exercise 13.49: Add a move constructor and move-assignment operator to your StrVec, String, and Message classes
 * @date 2024-01-27
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/**********************************************Message program begins here**************************************************
#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include <string>
#include <algorithm>


// ==========================Message class defintion begins here ===============================================
class Folder;
// Message objects will contain msg and a set of folders which contains the message
class Message{
    friend void swap(Message &lhs, Message &rhs);
    public :
        // default constructor and constructor that takes a string
        Message(const std::string &msg = "") : contents(msg) {}        
         // copy_constructor
        Message(const Message &source) : contents(source.contents), folders(source.folders) {
            std::cout << "Message(const Message &source) : " << std::endl; 
            addToFolders(source);
        }    
        // move constructor
        Message(Message &&source);
        // copy_assignment operator
        Message & operator=(const Message &m);    // copy_assignment operator
        // move_assignment operator
        Message & operator=(Message &&rhs);
        ~Message(){     // destructor
            removeFromFolders();
        }

        void save(Folder &);   //  adds the folder to its list and makes the folder to add this 
        void remove(Folder &); //  removes the folder from its list and makes the folder to remove this 
        void print();  // prints the data      
        const std::string & get_msg(){
            return contents;
        }   
    private :
        // private utility functions
        void removeFromFolders();
        void addToFolders(const Message &source);
        void moveFolders(Message *);

        // data members
        std::string contents;
        std::set<Folder *> folders;
};

//  Folder class contains set of Messages and members to add and remove a Message 
class Folder{
    public :
        Folder(const std::string &str) : name(str) {}
        void addMsg(Message &m); 
        void rmvMsg(Message &m);
        void print();
        std::string get_name(){ return name ;}
    private :
        std::string name;
        std::set<Message *> messages;
};

//  adds a folder to the folders list and makes the folder to add this in to its set of Messages
void Message::save(Folder &f){
    folders.insert(&f);
    f.addMsg(*this);
}

// removes a folder from the folders list and makes the folder to remove this from its set of Messages
void Message::remove(Folder &f){
    folders.erase(&f);
    f.rmvMsg(*this);
}

// private utility function to remove this Message from all the Folders that contains it
void Message::removeFromFolders(){
    for(auto f : folders){
        f->rmvMsg(*this);
    }   
}

// private utility function to add this Message to all the Folders the source contains 
void Message::addToFolders(const Message &source){
    for(auto f : source.folders){
        f->addMsg(*this);
    }

}

// move constructor
Message::Message(Message &&source): contents(std::move(source.contents)){
    std::cout << "Message::Message(Message &&source) :" << std::endl;
    moveFolders(&source);
} 

// moveFolders private utility function 
void Message::moveFolders(Message *m){
    folders = std::move(m->folders);
    for(auto f : folders){
        f->rmvMsg(*m);
        f->addMsg(*this);
    }
    m->folders.clear();
}

// copy_assignment operator, copies the contents and Folers list
Message & Message::operator=(const Message &rhs){
    std::cout << "Message::operator=(const Message &rhs) : " << std::endl;
    removeFromFolders();
    contents = rhs.contents;
    folders = rhs.folders;
    addToFolders(rhs);

    return *this;
}

// move_assignment operator
Message & Message::operator=(Message &&rhs){
    std::cout << "Message::operator=(Message &&rhs) called" << std::endl;
    if(this != &rhs){
        removeFromFolders();
        contents = std::move(rhs.contents);
        moveFolders(&rhs);
    }
    return *this;
}

//  adds a Message to the list of Messages the folder contains
void Folder::addMsg(Message &m){
    messages.insert(&m);
}

//  removes a Message from the list of Messages the folder contains
void Folder::rmvMsg(Message &m){
    messages.erase(&m);
}

void Message::print(){
    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "msg : " << contents << std::endl;
    std::cout << "folders : ";
    for(auto f : folders){
        std::cout << f->get_name() << " || ";

    }

    std::cout << std::endl;
}

void Folder::print(){
    std::cout << "----------------------------------------------------------------------" << std::endl;
    std::cout << "name : " << name << std::endl;
    std::cout << "msgs : " << std::endl;
    for(auto m : messages){
        std::cout << m->get_msg() << std::endl;
    } 
}

void swap(Message &lhs, Message &rhs){
    using std::swap;
    lhs.removeFromFolders();
    rhs.removeFromFolders();
    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);
    lhs.addToFolders(lhs);
    rhs.addToFolders(rhs);
}

Message Test(Message m){
    return m;
}

int main(){
    Folder f1("f1"), f2("f2"), f3("f3");
    Message m1("m1");
    m1.save(f1);
    m1.save(f2);
    m1.save(f3);
    Message m2(std::move(m1));
    Message m3("m3"), m4("m4");
    m3.save(f1);
    m3.save(f2);
    m4 = std::move(m3);

    m2.print();
    m4.print();

    m2 = Test(m4);
    m2.print();

    return 0;
}


******************************************Message program ends here********************************************************************/

/*****************************************StrVec program begins here********************************************************
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <string>
#include <initializer_list>

class StrVec{
    friend void swap(StrVec &lhs, StrVec &rhs);
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

    std::cout << "----------------------------------------------------------------" << std::endl;
    StrVec svec5(std::move(svec1)), svec6;
    svec5.push_back("working");
    svec6 = std::move(svec4);
    svec6.push_back("it works as awesome");
    std::cout << "after pushing----------------------------" << std::endl; 
    print(svec5);
    print(svec6);
    
    return 0;
}

***********************************StrVec program ends here *****************************************************************/

/**********************************String program begins here ***************************************************************/
#include <iostream>
#include <utility>
#include <memory>
#include <algorithm>
#include <cstring>
#include <vector>

class String {
    public :
        String() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
        String(const char *p);
        String(const String &source);
        String(String &&source) noexcept;
        String & operator=(String rhs);
        String & operator=(String &&rhs);
        char * begin() const;
        char * end() const;
        ~String(){ free(); }
        size_t size();
        void reserve(const size_t sz);
        size_t capacity();
        void push_back(const char &ch);
    private :
        void swap(String &lhs, String &rhs);
        void check_n_alloc();
        void realloc(const size_t sz = 0);
        void free();
        std::pair<char *, char *> alloc_n_copy(const char *b, const char *e);
        char * elements;
        char * first_free;
        char * cap;
        std::allocator<char> alloc;
};

String::String(const char *p){
    std::cout << "String(const char *p) : " << std::endl;
    std::cout << "sizeof(p) " << strlen(p) << std::endl;
    auto data = alloc_n_copy(p, p + strlen(p));
    elements = data.first;
    first_free = cap = data.second;
}

String::String(const String &source){
    std::cout << "String(const String &source) :" << std::endl;
    auto data = alloc_n_copy(source.begin(), source.end());
    elements = data.first;
    first_free = cap = data.second;
}

String::String(String &&source) noexcept : elements(source.elements), first_free(source.first_free), cap(source.cap){
    std::cout << "String::String(String &&source) noexcept : " << std::endl;
    source.elements = source.first_free = source.cap = nullptr;
}


char * String::begin() const {
    return elements;
}

char * String::end() const {
    return first_free;
}

String & String::operator=(String rhs){
    std::cout << "operator=(String rhs) : " << std::endl;
    swap(*this, rhs);
    return *this;
}

String & String::operator=(String &&rhs){
    std::cout << "String::operator=(String &&rhs) : " << std::endl;
    if(this != &rhs){
        swap(*this, rhs);
    }
    return *this;
}

void String::swap(String &lhs, String &rhs){
   using std::swap;
   swap(lhs.elements, rhs.elements);
   swap(lhs.first_free, rhs.first_free);
   swap(lhs.cap, rhs.cap);
}

void String::check_n_alloc(){
    if(first_free == cap){
        realloc();
    }
}

size_t String::size(){
    return first_free - elements;
}

void String::reserve(const size_t sz){
    realloc(sz);
}

size_t String::capacity(){
    return cap - elements;
}

void String::realloc(const size_t sz){
    size_t new_capacity;
    if(!sz){
        new_capacity = size() ? 2 * size() : 1;
    }else if( sz && sz > capacity()){
        new_capacity = sz;
    }else {
        return ;
    }

    auto new_elements = alloc.allocate(new_capacity);
    auto new_first_free = std::uninitialized_copy(std::make_move_iterator(elements), std::make_move_iterator(first_free), new_elements);
    free();
    elements = new_elements;
    first_free = new_first_free;
    cap = elements + new_capacity;
}

void String::free(){
    while(first_free != elements){
        std::destroy_at(--first_free);
    }
    alloc.deallocate(elements, cap - elements);
    elements = first_free = cap = nullptr;
}

std::pair<char *, char *> String::alloc_n_copy(const char *b, const char *e){
    auto new_elements = alloc.allocate(e - b);
    auto new_first_free = std::uninitialized_copy(b, e, new_elements);
    return {new_elements, new_first_free};
}

void String::push_back(const char &ch){
    check_n_alloc();
    std::construct_at(first_free++, ch);
}

void print(const String &str){
    for(auto iter = str.begin(); iter != str.end(); ++iter){
        std::cout << *iter ;
    }
    std::cout << std::endl;
}

int main(){
   std::vector<String> svec;
   svec.push_back("1");
   std::cout << "=============" << std::endl;
   svec.push_back("2");
std::cout << "=============" << std::endl;
   svec.push_back("3");
std::cout << "=============" << std::endl;
   svec.push_back("4");
std::cout << "=============" << std::endl;
   svec.push_back("5");
std::cout << "=============" << std::endl;
   svec.push_back("6");
std::cout << "=============" << std::endl;
   svec.push_back("7");
std::cout << "=============" << std::endl;

   svec.push_back("8");
std::cout << "=============" << std::endl;
   svec.push_back("9");
std::cout << "=============" << std::endl;

}



/******************************************String program ends here *********************************************************/
