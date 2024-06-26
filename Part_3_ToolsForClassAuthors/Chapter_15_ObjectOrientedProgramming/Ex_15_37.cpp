/************************************************************************************************************************************************************
 * @file Ex_15_37.cpp
 * @brief Exercise 15.37: What changes would your classes need if the derived classes had members of type 
 * shared_ptr<Query_base> rather than of type Query?
 * @date 2024-02-07
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * If derived classes had members of type shared_ptr<Query_base> rather than of type Query
 * (a) Query q1 =  Query(s1) | Query(s2) & ~ Query(s3);
 * the rhs should be writen as
 * == OrQuery( WordQuery(s1), AndQuery( WordQuery(S2),NotQuery(Wordquery(s3)) ) )
 * so OrQuery() should be constructed from WordQuery and AndQuery objects, but what if both the operands of type
 * AndQuery or OrQuery or any other combination. So It is lot of verbose to come up with all sort of combinations.
 *      So to avoid that Query_base which acts as an abstract class should also behave as a interface class.
 * 1. (ie) Query_base class should be modified to be normal base class, so that its objects can be created and 
 * 2. it needs a constructor which takes a string and builds a WordQuery object
 * 3. eval() and rep() should be defined as normal virtual functions
 * 4. it should have a datamember of type shared_ptr to Query_base;
 * 
 *************************************************************************************************************************************************************/
#include "TextQuery.cpp"
#include <iostream>
#include <memory>

// abstract class to represent different types of queries, And, Not, Or, WordQuery
class Query_base {
    friend class Query;
    public :
        // virtual functions when called type specific version will run
        virtual QueryResult eval(const TextQuery &query) const {
            
        }
        virtual std::string rep() const {

        }
};

//  Interface class of the queries
class Query {
    friend class Query_base;
    friend Query operator~(const Query &q);    //   returns set of lines in which the word didn't appear  
    friend Query operator|(const Query &l, const Query &r);     //  returns Query object pointing to NotQuery object constructed from two Query objects
    friend Query operator&(const Query &l, const Query &r);     //  returns Query object pointing to AndQuery object constructed form two Query objects    
    public : 
        //  Builds a WordQuery object from the string
        Query(const std::string &query_word_);
    
        //  calls virtual function eval of pointed type 
        QueryResult eval(const TextQuery &query) const {
            return q->eval(query);
        }
    
        //  calls virtual function rep of pointed type
        std::string rep() const {
            return q->rep();
        }    

    private : 
        //  constructor to construct Query object from a shared pointer to Query_base
        Query(std::shared_ptr<Query_base> q_) : q(q_) {}

        //  data member, a shared_ptr to the Query_base
        std::shared_ptr<Query_base> q;
};


// stores a string, when eval() is called calles TextQuery.query() on the string to get the QueryResult containing line_no
// This is the only class which does the core work of queriying (ie) returning the set line_nos in which the word appears
class WordQuery : public Query_base {
    friend class Query;
    private : 
        // only constructor of this class, which takes a query word
        WordQuery(const std::string & query_word_) : query_word(query_word_) {}

        // queries the Text_Query with the given word
        QueryResult eval(const TextQuery &query) const override {
            std::cout << "QueryResult WordQuery::eval(const TextQuery &query) const override : invoked " << query_word << std::endl;
            return query.query(query_word);
        }   

        //  returns the query_word
        std::string rep() const override {
            std::cout << "std::string WordQuery::rep() const override : invoked" << std::endl;
            return query_word;
        }

    private :
        std::string query_word;
};

Query::Query(const std::string &query_word_) : q(new WordQuery(query_word_)) {
    std::cout << "Query(const std::string &query_word_) : q(WordQuery(query_word_)) : invoked" << std::endl;
}

// abstract class contains Query objects to represent two operands and operator symbol representing Or or And
class BinaryQuery : public Query_base {
    protected :

        std::string rep() const override {
            return "(" + lhs->rep() + " " + opSym + " " + rhs->rep() + ")" ;     
        }

        BinaryQuery(const Query_base &l, const Query_base &r, const std::string &opSym_) 
            : lhs(new Query_base(l)), rhs(new Query_base(r)), opSym(opSym_) {}

    protected :
        std::shared_ptr<Query_base> lhs, rhs;
        std::string opSym;
};

// class OrQuery which represents the union of the lineno's in both the operands
class OrQuery : public BinaryQuery {
    friend Query operator|(const Query &l, const Query &r);
    private :
        OrQuery(const Query_base &l, const Query_base &r) 
            : BinaryQuery(l, r, "|") {}
        
        QueryResult eval(const TextQuery &query) const override {
            auto res1 = lhs->eval(query);
            auto res2 = rhs->eval(query);
            std::set<size_t> res_lines(res1.begin(), res1.end());
            res_lines.insert(res2.begin(), res2.end());

            return QueryResult(rep(), res1.get_file(), std::shared_ptr<std::set<size_t>>(new std::set<size_t>(res_lines)));
        } 
};

// class derived from BinaryQuery which returns the intersection of set lineno's in both the operands
class AndQuery : public BinaryQuery {
    friend Query operator&(const Query &l, const Query &r);
    private :
        // takes two Query objects representing two operands and constructs its BinaryQuery part with '&' symbol
        AndQuery(const Query_base &l, const Query_base &r) 
            : BinaryQuery(l, r, "&") {}
        

        QueryResult eval(const TextQuery &query) const override {
            auto left = lhs->eval(query), right = rhs->eval(query);
            std::set<size_t> res;
            std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(res, res.begin()));
            
            return QueryResult(rep(), left.get_file(), std::shared_ptr<decltype(res)>(new std::set<size_t>(res)));
        }
};

// class that contains a query object, when evaluted, it returns line_no in which the word is not found
class NotQuery : public Query_base {
    friend Query operator~(const Query &q);
    private :   
        // constructor that takes a query object
        NotQuery(const Query_base &q_) 
            : q(new Query_base(q_)) {}


        QueryResult eval(const TextQuery &query) const override{
            auto qr = q->eval(query);
            auto sz = qr.get_file()->size();
            auto beg = qr.begin();
            auto end = qr.end();
            std::set<size_t> res;

            for( size_t i = 0; i < sz ; ++i) {
                if(beg == end || *beg != i ) {
                    res.insert(i);
                } else {
                    ++beg;
                } 
            }

            return QueryResult(rep(), qr.get_file(), std::shared_ptr<decltype(res)>(new decltype(res)(res)));
        }

        std::string rep() const override {
            return "~(" + q->rep() + ")"; 
        }

        std::shared_ptr<Query_base> q;
};

Query operator~(const Query &q) {
    std::cout << "Query operator~(const Query &q) : invoked" << std::endl;
    return std::shared_ptr<Query_base>(new NotQuery((q.q)));
}

Query operator|(const Query &l, const Query &r) { 
    std::cout << "Query operator|(const Query &l, const Query &r) : invoked" << std::endl;
    return std::shared_ptr<Query_base>(new OrQuery((l.q),(r.q)));
}

Query operator&(const Query &l, const Query &r) {
    std::cout << "Query operator&(const Query &l, const Query &r)" << std::endl;
    return std::shared_ptr<Query_base>(new AndQuery((l.q),(r.q)));
}

int main(){
    std::ifstream ifile("text.txt");
    if(!ifile) {
        std::cerr << "Unable to open file" << std::endl;
        return -1;
    }

    TextQuery tq(ifile);

    Query q = ~Query("Alice");
    auto qr = q.eval(tq);
    std::cout << qr << std::endl;

    return 0;
}

