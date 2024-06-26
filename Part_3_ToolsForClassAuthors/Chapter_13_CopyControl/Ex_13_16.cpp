/************************************************************************************************************************************************************
 * @file Ex_13_16.cpp
 * @brief Exercise 13.16: What if the parameter in f were const numbered&? Does that change the output? If so, why? What 
 * output gets generated?
 * @date 2024-01-23
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * let s.no start from 1
 * a = 1  // default constructor
 * b = 2  // copy_constructor
 * c = 3  // copy_constructor 
 * as the parameter is const &, no new object is created, so the s.no's of corresponding argument get's printed
 * output :
 * 1
 * 2
 * 3
 *************************************************************************************************************************************************************/