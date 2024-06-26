/************************************************************************************************************************************************************
 * @file Ex_15_1.cpp
 * @brief Exercise 15.1: What is a virtual member?
 * @date 2024-02-03
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * virtual member :
 *      A base class differentiates the functions that are type dependent (ie) the derived class can have its own 
 * definition, are declared as virtual by base class. when derived classes inherits from base class, the derived class
 * will give its own defintiion to the virtual members.
 *      when a call is made through reference or pointer to the base class, which version of the virtual function
 * is run depends on the type of the object (ie) base class or derived class is passed.
 *      So the base class declares those functions that should be dynamilly bound as virtual (ie) at runtime, where as
 * other functions are resolved at compile time.
 * 
 *************************************************************************************************************************************************************/