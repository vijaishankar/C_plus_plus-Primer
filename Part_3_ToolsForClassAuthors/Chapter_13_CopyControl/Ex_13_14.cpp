/************************************************************************************************************************************************************
 * @file Ex_13_14.cpp
 * @brief Exercise 13.14: Assume that numbered is a class with a default constructor that generates a unique serial number for
 * each object, which is stored in a data member named mysn. Assuming numbered uses the synthesized copy-control members and
 * given the following function: 
 *      void f (numbered s) { cout << s.mysn << endl; }
 * what output does the following code produce?
 *      numbered a, b = a, c = b;
 *      f(a); f(b); f(c);
 * @date 2024-01-23
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * let serial no start from 1
 * a = 1, b = 1, c = 1, every object created has the same serial no, as b copies from a, c copies from b and the param copies from arg, as
 * synthesised copy_control members copies the s.no in to the new object
 * output :
 * 1
 * 1
 * 1
 *************************************************************************************************************************************************************/