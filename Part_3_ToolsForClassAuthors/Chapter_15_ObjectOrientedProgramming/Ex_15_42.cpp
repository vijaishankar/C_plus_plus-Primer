/************************************************************************************************************************************************************
 * @file Ex_15_42.cpp
 * @brief Exercise 15.42: Design and implement one of the following enhancements:
 * (a) Print words only once per sentence rather than once per line.
 * (b) Introduce a history system in which the user can refer to a previous query by number, possibly adding to it or
 *     combining it with another.
 * (c) Allow the user to limit the results so that only matches in a given range of lines are displayed.

 * @date 2024-02-08
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * Following features have been added
 * (b) Introduce a history system in which the user can refer to a previous query by number, possibly adding to it or
 *     combining it with another.
 * (c) Allow the user to limit the results so that only matches in a given range of lines are displayed.
 *************************************************************************************************************************************************************/
#include "Ex_15_35_Query.cpp"

int main(){
    std::ifstream ifile("text.txt");
    if(!ifile) {
        std::cerr << "Unable to open file" << std::endl;
        return -1;
    }

    TextQuery tq(ifile);

    Query q1 = Query("fiery") & Query("bird") | Query("wind");
    auto qr = q1.eval(tq);
    qr.range(3,6);
    std::cout << qr << std::endl;

    std::cout << "============================================" << std::endl;
    for ( size_t i = 0; i != Query::history.size(); ++i ){
        std::cout << "[Query[" << i << "]" << (Query::history[i]).eval(tq) << std::endl;
    }

    std::cout << "======================================" << std::endl;
    std::cout << Query("Daddy").eval(tq) << std::endl;

    Query q2 = ~(Query::history[4] & Query::history[5]);
    std::cout << q2.eval(tq) << std::endl;
    return 0;
}