/************************************************************************************************************************************************************
 * @file Ex_12_27_TextQuery.cpp
 * @brief Exercise 12.27: The TextQuery and QueryResult classes use only capabilities that we have already covered. Without 
 * looking ahead, write your own versions of these classes.
 * @date 2024-01-18
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

// necessary libraries
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>

class QueryResult;

class TextQuery{
    public :
        typedef std::vector<std::string>::size_type index_type;

        TextQuery(std::ifstream &ifile);  //  constructor that takes a filestrm object
        inline QueryResult query(const std::string & word) const ;  //  queries the text
        inline void debug() const;

    private :
        std::shared_ptr<std::vector<std::string>> text;  //  contains the text from the file
        std::shared_ptr<std::map<std::string, std::set<index_type>>> word_map;  //  contains each word in the file and line numbers they appear 
        void ignoreCase(std::string &word);
};

class QueryResult{
    friend inline std::ostream & print(std::ostream &out, const QueryResult &qr);
    public :
        QueryResult(const std::string &word_param, std::shared_ptr<std::vector<std::string>> text_param,
                    std::shared_ptr<std::map<std::string, std::set<TextQuery::index_type>>> word_map_param,
                    std::vector<std::set<TextQuery::index_type>::iterator> &lines_param) :
                    word(word_param), text(text_param), word_map(word_map_param), lines(lines_param) {}

    private :
        std::string word;
        std::shared_ptr<std::vector<std::string>> text;
        std::shared_ptr<std::map<std::string, std::set<TextQuery::index_type>>> word_map;
        std::vector<std::set<TextQuery::index_type>::iterator> lines;
};

TextQuery::TextQuery(std::ifstream &ifile){
    //  code to dynamicaly allocate memory
    text = std::make_shared<std::vector<std::string>>();    // text is allocated memory and initialised with empty vector of strings
    word_map = std::make_shared<std::map<std::string, std::set<index_type>>>();  // word_map is allocated memory and initialised with empty map

    std::string line;
    index_type line_no = 0;
    while(getline(ifile, line)){  //  extracts one line at a time from the file
        std::istringstream linestrm(line);
        std::string word;
        text->push_back(line);  //  each line is added as a seperate element in the vector 

        while(linestrm >> word){
            ignoreCase(word);   //  changes all the letters to lowercase so "as" and "As" will be considered as same words
            (*word_map)[word].insert(line_no);  //  map is subscripted with word, and corresponding line_no is added to set returned
        }

        ++line_no;
        line.clear();  //  to clear the eof 
    }
}

void TextQuery::debug() const {  
    //  prints the vector that contains the file
    std::cout << "the text from the file as follows..........." << std::endl;
    for(auto iter = text->cbegin(); iter != text->cend(); ++iter){
        std::cout << *iter << std::endl;
    }

    //  prints the word_map of the file
    std::cout << "\nword map builded out of text is as follows.........." << std::endl;
    for(auto iter = word_map->cbegin(); iter != word_map->cend(); ++iter){
        std::cout << iter->first << " [" ;
        for(auto beg = iter->second.cbegin(); beg != iter->second.cend(); ++beg){
            std::cout << *beg << " ";
        }    
        std::cout << "]" << std::endl;
    }
}

void TextQuery::ignoreCase(std::string &word){
    for(std::string::size_type i = 0; i != word.size(); ++i){
        word[i] = tolower(word[i]);
    }
}


QueryResult TextQuery::query(const std::string &word) const {
    std::vector<std::set<TextQuery::index_type>::iterator> lines;
    auto res_iter = word_map->find(word);
    
    if(res_iter != (word_map->cend())){
         for( auto iter = res_iter->second.begin(); iter != res_iter->second.end(); ++iter){
            lines.push_back(iter);
         }
    }

    return QueryResult(word, text, word_map, lines);
}

std::ostream & print(std::ostream &out,const QueryResult &qr){
    if(qr.lines.empty()){
        out << qr.word << " not found in the text" << std::endl;
    }else{
        out << qr.word << " found in the following lines........\n" << std::endl;
        for(auto iter = qr.lines.begin(); iter != qr.lines.end(); ++iter){  
            TextQuery::index_type n = **iter;   //  since iter is a iterator in to the lines-vector. first dereference will return iterator in to set, second dereference yields line_num
            out << "[ " << n << " ]  " << (*qr.text)[n] << std::endl;
        }
    }

    return out;
}

int main(){
    std::ifstream ifile("text.txt");
    if(!ifile){
        std::cerr << "unable to open the file" << std::endl;
        return -1;
    }

    TextQuery tq(ifile);
    std::string word;
    std::cout << "\nEnter the word to search or q to quit : ";
    while(std::cin >> word && word != "q"){
        print(std::cout, tq.query(word)) << std::endl;
            std::cout << "\nEnter the word to search or q to quit : ";
    }

    return 0;
}