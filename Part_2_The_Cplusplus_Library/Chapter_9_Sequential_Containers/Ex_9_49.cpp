/************************************************************************************************************************************************************
 * @file Ex_9_49.cpp
 * @brief Exercise 9.49: A letter has an ascender if, as with d or f, part of the letter extends above the middle of the line.
 *        A letter has a descender if, as with p or g, part of the letter extends below the line. Write a program that reads
 *        a file containing words and reports the longest word that contains neither ascenders nor descenders.
 * @date 2024-01-02
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <fstream>

std::string getLargerstWordWithout(std::ifstream &in, const std::string &seq1, const std::string &seq2);
void strToLower(std::string &str);

int main(){
    std::ifstream file("text.txt");
    if(!file){
        std::cerr << "Unable to open file" << std::endl;
        return -1;
    }

    std::string ascender{"bdfhklt"}, descender{"gjpq"};
    std::string largeWord{getLargerstWordWithout(file, ascender, descender)};
    if(!largeWord.empty()){
        std::cout << "The largest word in the file is " << largeWord << std::endl;
    }else{
        std::cout << "No word is without \"" << ascender << "\" and \"" << descender << std::endl;
    }
}

std::string getLargerstWordWithout(std::ifstream &in, const std::string &seq1, const std::string &seq2){
    std::string curr;
    std::string largest;
    const std::string exclusionList(seq1 + seq2);
    while( in >> curr ){
        strToLower(curr);
        if(curr.find_first_of(seq1) == std::string::npos){
            if( largest.size() < curr.size()){
                largest = curr;
            }
        }
    }

    return largest;
}

void strToLower(std::string &str){
    std::string::size_type pos = 0;
    while( pos != str.size()){
        str[pos] = std::tolower(str[pos]);
        ++pos;
    }

    return;
}