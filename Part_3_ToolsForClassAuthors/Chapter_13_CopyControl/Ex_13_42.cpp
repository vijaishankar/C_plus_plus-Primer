/************************************************************************************************************************************************************
 * @file Ex_13_42.cpp
 * @brief Exercise 13.42: Test your StrVec class by using it in place of the vector<string> in your TextQuery and QueryResult
 * classes (§ 12.3, p. 484).
 * @date 2024-01-26
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <map>
#include <set>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Ex_13_39.cpp"

using std::string; using std::vector; using std::map; using std::set; using std::shared_ptr; using std::make_shared; using std::cout; using std::cin;
using std::ifstream; using std::istringstream; using std::ofstream; using std::ostream; using std::endl;


class QueryResult;
class TextQuery{
    public :
        typedef size_t index_type;

        TextQuery(ifstream &file_strm) : file(make_shared<StrVec>()) {
            string line;
            index_type line_no = 0;
            while(getline(file_strm, line)){
                file->push_back(line);
                istringstream line_strm(line);
                string word;
                while(line_strm >> word){
                    auto &l_set = word_map[word];
                    if(!l_set){
                        l_set.reset(new set<index_type>);
                    }
                    l_set->insert(line_no);
                }
                ++line_no;
            }
        }
        QueryResult query(const string &sought_word) const ;
    private :
        shared_ptr<StrVec> file;
        map<string, shared_ptr<set<index_type>>> word_map;
};

class QueryResult{
    friend inline ostream & print(ostream &out, const QueryResult &qr);
    public :
        using index_type = TextQuery::index_type;
       
        QueryResult(const string &word_param, shared_ptr<StrVec> file_param, shared_ptr<set<index_type>> lines_param) 
                : word(word_param), file(file_param), lines(lines_param) {}

    private :   
        string word;
        shared_ptr<StrVec> file;
        shared_ptr<set<index_type>> lines;            
};

QueryResult TextQuery::query(const std::string &sought_word) const {
    static shared_ptr<set<index_type>> no_data(make_shared<set<index_type>>());
    auto result = word_map.find(sought_word);
    if(result == word_map.end()){
        return QueryResult(sought_word, file, no_data);
    }else{
        return QueryResult(sought_word, file, result->second);
    }
}

string make_plural(set<TextQuery::index_type>::size_type n){
    return n > 1 ? " times " : " time ";
}

ostream & print(ostream &out, const QueryResult &qr){
    auto n = qr.lines->size();
    out << qr.word << " appears " << n << make_plural(n) << "in the file" << endl; 
    for(auto line_no : *qr.lines){
        out << "[ " << line_no + 1 << " ]  " << *(qr.file->begin() + line_no) << endl;
    }

    return out;
}

void runQueries(ifstream& infile)
{
    TextQuery tq(infile); 
    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        print(cout, tq.query(s)) << endl;
    }
}

int main(){
    std::ifstream ifile("text.txt");
    runQueries(ifile);
    
}