/*  Exercise 6.17: Write a function to determine whether a string contains any capital letters. Write a function to change
 *  a string to all lowercase. Do the parameters you used in these functions have the same type? If so, why? If not, why
 *  not? */
#include <iostream>
#include <string>

void changeToLower(std::string &str);           // parameter is plain reference as the argument will be modified            
bool checkForCaps(const std::string &str);      // parameter is const reference as the argment will not be modified

int main(){
    std::cout << "Enter a sentence : ";
    std::string sentence;
    getline(std::cin, sentence);
    bool contains_caps = checkForCaps(sentence);
    std::cout << sentence << " contains capital letter ? : " << contains_caps << std::endl;
    changeToLower(sentence);
    std::cout << sentence << std::endl;

    return 0;
}

//  function to change the all letters to lowercase
void changeToLower(std::string &str){
    for(std::string::size_type i = 0; i != str.size(); ++i){
        str[i] = tolower(str[i]);
    }
}

//  function to check if string contains any upper case letters
bool checkForCaps(const std::string &str){
    for(std::string::size_type i = 0; i != str.size(); ++i){
        if(isupper(str[i])){
            return true;
        }
    }

    return false;
}

