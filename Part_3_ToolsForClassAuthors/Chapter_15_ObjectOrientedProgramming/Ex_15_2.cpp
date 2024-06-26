/************************************************************************************************************************************************************
 * @file Ex_15_2.cpp
 * @brief Exercise 15.2: How does the protected access specifier differ from private?
 * @date 2024-02-03
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * private :
 *      private members can be accessed by the class members and friend, but not the users of the class. Similarly
 * a derived class doesn't have access to private members of the base class.
 *      But the base class can declare a member to be accessed by derived class without giving access to others by 
 * specifying the access specifier as protected.
 *      private members   :   other members of the class, friend
 *      public  members   :   other members of the class, friend, users of the class, derived class
 *      protected members :   other members of the class, friend , derived class
 * 
 *************************************************************************************************************************************************************/


