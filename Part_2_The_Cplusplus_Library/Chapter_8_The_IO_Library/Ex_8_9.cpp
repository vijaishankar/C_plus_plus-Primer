/************************************************************************************************************************************************************
 * @file Ex_8_9.cpp
 * @brief Exercise 8.9: Use the function you wrote for the first exercise in § 8.1.2 (p. 314) to print the contents of an 
 *        istringstream object.
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

/***
 * stringstream.str() will return a copy of the underlying string and stores a copy of the new string if passed,
 *     # even after extracting all characters from the stream
 *     # even if failbit, eofbit, badbit is set true
 *     # as extraction only moves the pointer, but doesn't modify the string in anyway, so strm will always have the string
 * https://stackoverflow.com/questions/43124746/istringstreamstr-does-not-return-current-contents
 * https://en.cppreference.com/w/cpp/io/basic_istringstream/str     
*/
#include <iostream>
#include <sstream>


std::istringstream & print(std::istringstream &);

int main(){
    
    std::cout << "main() invoked print()\n";
    int num;
    std::istringstream strstrm;

    print(strstrm);
    std::cout << "state of strstrm after clear all error states : \n";
    std::cout << "strstrm.good() : " << strstrm.good() << "\nstrstrm.rdstate() : " << strstrm.rdstate() 
                << "\nstrstrm.fail() :  " << strstrm.fail() << "\nstrstrm.eof() : " << strstrm.eof() << std::endl;

    //  code to check whether strstrm is operational            
    strstrm.str("hi there");
    std::cout << strstrm.str() << std::endl;    //   returns only a copy 
    std::string line;   

    // code to check whether a strstrm.str() only returned a copy
    getline(strstrm, line);         //  getline() extracts all characters 
    std::cout << line << std::endl;
    if(strstrm.good()){
        std::cout << "still good" << std::endl;
    }else{
        std::cout << "got exhausted not good" << std::endl;
    }

    return 0;
}

std::istringstream & print(std::istringstream &strstrm){
    std::cout << "condition of strstrm before input : \n";
    std::cout << "strstrm.good() : " << strstrm.good() << "\nstrstrm.rdstate() : " << strstrm.rdstate() 
                << "\nstrstrm.fail() :  " << strstrm.fail() << "\nstrstrm.eof() : " << strstrm.eof() << std::endl;

    strstrm.str("this line has five words");
    char ch;
    while(strstrm >> ch){           // extracts character by character untill hits eof
        std::cout << ch;
    }

    std::cout << "state of strstrm after eof : \n";   
    std::cout << "strstrm.good() : " << strstrm.good() << "\nstrstrm.rdstate() : " << strstrm.rdstate() 
                << "\nstrstrm.fail() :  " << strstrm.fail() << "\nstrstrm.eof() : " << strstrm.eof() << std::endl;

    // code to check whether we can store a diff string in to strstrm bfr clearing error states
    strstrm.str("hello world");         //  works 
    std::string word;
    strstrm >> word;
    if(word.size()){
        std::cout << word << std::endl;
    }else{
        getline(strstrm, word);
        if(word.size()){
            std::cout << word << std::endl;
        }else{
            std::cout << "only getting a copy works" << strstrm.str() << std::endl;
            /* works as this is how it is how str() function is implemeted, it doesn't care abt the error states or pointer pointing the char
               it just returns a copy of the entire string. for further explanations
               https://stackoverflow.com/questions/43124746/istringstreamstr-does-not-return-current-contents
             */  
        }
    }
    std::cout << "strstrm.good() : " << strstrm.good() << "\nstrstrm.rdstate() : " << strstrm.rdstate() 
                << "\nstrstrm.fail() :  " << strstrm.fail() << "\nstrstrm.eof() : " << strstrm.eof() << std::endl;
    
    strstrm.clear();        //  clears the error states
    return strstrm;
}