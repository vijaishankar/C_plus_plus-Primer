/************************************************************************************************************************************************************
 * @file Ex_1_6.cpp
 * @brief Exercise 1.6: Explain whether the following program fragment is legal.
 * If the program is legal, what does it do? If the program is not legal, why not? How would you fix it?
 * @date 2024-03-14
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
* std::cout << "The sum of " << v1;     
* << " and " << v2;                     //  illegal : requires seperate std::cout
* << " is " << v1 + v2 << std::endl;    //  illegal : requires seperate std::cout
**************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * // fix 
 * std::cout << "The sum of " << v1;
 * std::cout << " and " << v2;
 * std::cout << " is " << v1 + v2 << std::endl; 
 * 
 *************************************************************************************************************************************************************/
