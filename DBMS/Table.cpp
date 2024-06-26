/************************************************************************************************************************************************************
 * @file Table.cpp
 * @brief definitions of all members of Table class
 * @date 2024-02-28
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/
#include "Table.h"
#include <algorithm>
#include <functional>
#include <utility>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>

using namespace std::placeholders; 

Table::Table(const schema_type schema_, const string &p_key_, const string &name_)
    : schema(schema_), name(name_){
            auto iter = std::find_if(schema.begin(), schema.end(),
                    [this, p_key_](const pair<string, string> &p){ return p.first == p_key_;});
    if (iter == schema.end()) {
        std::cerr << p_key_ << " didn't match" << std::endl;
        return;
    }

    primary_key = p_key_;

    switch(iter->second[0]) {
            case 'i' : key_type = Table::int_type; break;
            case 'd' : key_type = Table::double_type; break;
            case 'c' : key_type = Table::char_type; break;
            case 's' : key_type = Table::string_type; break;
    }

    key_pos = iter - schema.begin();
}

bool Table::add_record(const vector<void *> record_) {
    auto iter = std::find_if(records.begin(), records.end(),
                        std::bind(compare_equal,_1, record_, key_type, key_pos)); 
    if (iter == records.end()) {
         records.push_back(record_);
         return 1;
    } else {
        std::cerr << "duplicate primary key";
        return -1;
    }     
} 

bool Table::create_new_record(vector<void *> &r) {
    vector<void *> row;
    auto schema_iter = schema.begin();
    for( auto p : r ) {
        switch(schema_iter->second[0]) {
            case 'i' : row.push_back(new int(*static_cast<int *>(p))); break;
            case 'd' : row.push_back(new double(*static_cast<double *>(p))); break;
            case 'c' : row.push_back(new char(*static_cast<char *>(p))); break;
            case 's' : row.push_back(new string(*static_cast<string *>(p))); break;
        }
        ++schema_iter;
    }    
    records.push_back(row);

    return 1;
}

int Table::remove_record(const constraint &item) {
    if (primary_key != item.first) {
        std::cerr << "primary key mismatch" << std::endl;
        return -1;
    } 
    auto iter = std::remove_if(records.begin(), records.end(),std::bind(equal, _1, item.second, key_type, key_pos));  
    auto count = records.end() - iter;
    records.erase(iter, records.end());
    modified = true;
    return count;
}

bool Table::check(const vector<string> &lst) {
    for (auto &s : lst) {
        if(!std::any_of(schema.begin(), schema.end(), [this,&s](const pair<string, string> &p){ return p.first == s;})) {
            return 0;
        }
    }

    return 1;
}
size_t Table::size() const {
    return records.size();
}

bool Table::empty() const {
    return records.empty();
}

pair<size_t, string> Table::get_col_info(const string &col_name) const {
    size_t pos = 0;

    for (auto p : schema) {
        if (p.first == col_name) {
            return {pos, p.second};
        }
        ++pos;
    }

    return {string::npos, ""};
}

/*
int Table::delete_records(decltype(records)::iterator b, decltype(records)::iterator e) {
    
}
*/
string Table::get_name() const {
    return name;
}

Table * Table::new_table(record_type::iterator b, record_type::iterator e) {
    auto tb = new Table(schema, primary_key, name);
    for(; b != e; ++b) {
        auto r = *b;
        decltype(r) newrow;
        auto t = schema.begin();
        for(auto &p : r) {
            switch(t->second[0]) {
                case 'i' : newrow.push_back(new int(*static_cast<int *>(p))); break;
                case 'd' : newrow.push_back(new double(*static_cast<double *>(p))); break;
                case 'c' : newrow.push_back(new char(*static_cast<char *>(p))); break;
                case 's' : newrow.push_back(new string(*static_cast<string *>(p))); break;
            }
            ++t;
        }    
        tb->add_record(newrow);
    }
    return tb;
}

std::iostream & operator<<(std::iostream &os, Table &tb) {
    if (tb.first_write || tb.modified) {
        tb.first_write = false;    
        os << tb.name + "\n";
        for (auto p : tb.schema) {
            os << p.first << " " << p.second << " ";
        }    
        os << std::endl;
        os << tb.primary_key << " " << tb.key_type << " " << tb.key_pos << std::endl;
    }

    decltype(tb.updated_pos) offset = 0;
    if (!tb.first_write && !tb.modified) {
        offset = tb.updated_pos;
    }

    for (size_t i = offset; i != tb.size(); ++i) {
        auto beg = tb.schema.begin();
        for (auto p : tb.records[i]) {
            switch(beg->second[0]) {
                case 'i' : os << *(static_cast<int *>(p)) << " "; break; 
                case 'd' : os << *(static_cast<double *>(p)) << " "; break;
                case 'c' : os << *(static_cast<char *>(p)) << " "; break;
                case 's' : os << *(static_cast<string *>(p)) << " "; break; 
            }
            ++beg; 
        }
        os << std::endl;
    }

    if (tb.modified) {
        tb.set_modified(false);
    }
    return os;
}

Table::Table(std::fstream &iofile) {
    getline(iofile, name);
    std::string first_line;
    getline(iofile, first_line);
    std::istringstream fline_strm(first_line);
    std::string col_name, col_type;
    while(fline_strm >> col_name >> col_type) {
        schema.push_back({col_name, col_type});
    } 

    int k_t;
    iofile >> primary_key >> k_t >> key_pos;

    switch(k_t) {
        case int_type : key_type = int_type; break;
        case double_type : key_type = double_type; break;
        case char_type : key_type = char_type; break;
        case string_type : key_type = string_type; break;
    }

    std::string line;
    getline(iofile,line);
    while (getline(iofile, line)) {
        std::istringstream line_strm(line);
        vector<void *> row;
        for(auto p : schema){
            switch(p.second[0]) {
                case 'i' : int ival; line_strm >> ival; row.push_back(new int(ival)); break;
                case 'd' : double dval; line_strm >> dval; row.push_back(new double(dval)); break;
                case 'c' : char cval; line_strm >> cval; row.push_back(new char(cval)); break;
                case 's' : string sval; line_strm >> sval; row.push_back(new string(sval)); break; 
            }
        }
        records.push_back(row);
    }
    updated_pos = records.size();
    if (updated_pos || schema.size()) {
        first_write = false;
    }
}

Table::schema_type Table::get_schema() const {
    return schema;
}

string Table::get_pkey() const {
    return primary_key;
}


void create_schema(Table::schema_type &schema_, string &p_key_) {
    std::string col_name;
    std::string type_name;

    std::cout << "Enter col_name data_type : [0 to exit]\n";
    while (1) {
        std::cin >> col_name >> type_name;
        if (col_name == "0" || type_name == "0") {
            break;
        }
        schema_.push_back({col_name, type_name});
    }

    for(auto p : schema_) {
        std::cout << p.first << " " << p.second << std::endl;
    }
    std::cout << "\nEnter primary key : ";
    std::cin >> p_key_;

}

bool Table::is_modified() const {
    return modified;
}

void Table::set_modified(bool value) {
    modified = value;
}

void add_record(Table &tb) {
    std::cout << "add record : ";
    char reply;
    do {
        vector<void *> row;
        string val;
        for(auto p : tb.schema){
            std::cin >> val;
            switch(p.second[0]) {
                case 'i' : row.push_back(new int(stoi(val))); break;
                case 'd' : row.push_back(new double(stod(val))); break;
                case 'c' : row.push_back(new char(val[0])); break;
                case 's' : row.push_back(new string(val)); break; 
            }
        }
        tb.add_record(row);
        std::cout << "\nadd another record [y/n] : "; 
        std::cin >> reply;
    } while(reply == 'y' || reply == 'Y'); 

}

bool compare_equal(const vector<void *> &lhs, const vector<void *> &rhs, int N, size_t pos) {
    void *p = lhs[pos];
    void *q = rhs[pos];
    using types = Table::types;
    switch(N) {
        case types::int_type : return *(static_cast<int *>(p)) == *(static_cast<int *>(q));
        case types::double_type : return *(static_cast<double *>(p)) == *(static_cast<double *>(q));
        case types::char_type : return *(static_cast<char *>(p)) == *(static_cast<char *>(q));
        case types::string_type : return *(static_cast<string *>(p)) == *(static_cast<string *>(q));
    }  
    
    return 0;
}

bool compare_less(vector<void *> &lhs, vector<void *> &rhs, int N, size_t pos) {
    void *p = lhs[pos];
    void *q = rhs[pos];
     using types = Table::types;

    switch(N) {
        case types::int_type : return *(static_cast<int *>(p)) < *(static_cast<int *>(q));
        case types::double_type : return *(static_cast<double *>(p)) < *(static_cast<double *>(q));
        case types::char_type : return *(static_cast<char *>(p)) < *(static_cast<char *>(q));
        case types::string_type : return *(static_cast<string *>(p)) < *(static_cast<string *>(q));
    }   

    return 0;
}

bool equal(const vector<void *> &vec, const string &val, int N, size_t pos) {
    void *p = vec[pos];
    using types = Table::types;
    switch(N) {
        case types::int_type : return *(static_cast<int *>(p)) == stoi(val);
        case types::double_type : return *(static_cast<double *>(p)) == stod(val);
        case types::char_type : return *(static_cast<char *>(p)) == val[0];
        case types::string_type : return *(static_cast<string *>(p)) == val;
    }   

    return 0;
}

bool lesser(const vector<void *> &vec, const string &val, int N, size_t pos) {
    void *p = vec[pos];

    using types = Table::types;
    switch(N) {
        case types::int_type : return *(static_cast<int *>(p)) < stoi(val);
        case types::double_type : return *(static_cast<double *>(p)) < stod(val);
        case types::char_type : return *(static_cast<char *>(p)) < val[0];
        case types::string_type : return *(static_cast<string *>(p)) < val;
    }   

    return 0;
}

bool not_equal(const vector<void *> &vec, const string &val, int N, size_t pos) {
    return !equal(vec, val, N, pos);
}

bool lesser_or_equal(const vector<void *> &vec, const string &val, int N, size_t pos) {
    return equal(vec, val, N, pos) || lesser(vec, val, N, pos);
}

bool greater(const vector<void *> &vec, const string &val, int N, size_t pos) {
    return !lesser_or_equal(vec, val, N, pos);
}

bool greater_or_equal(const vector<void *> &vec, const string &val, int N, size_t pos) {
    return !lesser(vec, val, N, pos);
}

std::map<string, std::function<bool (const vector<void *>, const string &, int , size_t)>> op_map{{"=",equal},
                                                                                                  {"!=", not_equal},
                                                                                                  {"<", lesser},
                                                                                                  {"<=", lesser_or_equal},
                                                                                                  {">", greater},
                                                                                                  {">=", greater_or_equal}};
compare_less_obj::compare_less_obj(int N_, size_t pos_, bool desc_) 
    : N(N_), pos(pos_), desc(desc_) {}
    
bool compare_less_obj::operator()(const vector<void *> &lhs, const vector<void *> &rhs) {
    void *p,*q;
    if (!desc) {
        p = lhs[pos];
        q = rhs[pos];
    } else {
        q = rhs[pos];
        p = lhs[pos];
    }
     using types = Table::types;

    switch(N) {
        case types::int_type : return *(static_cast<int *>(p)) < *(static_cast<int *>(q));
        case types::double_type : return *(static_cast<double *>(p)) < *(static_cast<double *>(q));
        case types::char_type : return *(static_cast<char *>(p)) < *(static_cast<char *>(q));
        case types::string_type : return *(static_cast<string *>(p)) < *(static_cast<string *>(q));
    }   

    return 0;    
}                                                                                                  
                                                                            
