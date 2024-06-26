/************************************************************************************************************************************************************
 * @file Ex_14_52.cpp
 * @brief Exercise 14.52: Which operator+, if any, is selected for each of the addition expressions? List the 
 * candidate functions, the viable functions, and the type conversions on the arguments for each viable function:
 * struct LongDouble {
 *      // member operator+ for illustration purposes;+ is usually a nonmember
 *      LongDouble operator+(const SmallInt&);
 *      // other members as in § 14.9.2 (p. 587)
 * };
 * LongDouble operator+(LongDouble&, double);
 * SmallInt si;
 * LongDouble ld;
 * ld = si + ld;
 * ld = ld + si;
 * @date 2024-02-01
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * ld = si + ld  // 
 * candidate functions : all overloaded operator+ functions and built in operator+ 
 * viable functions : built in operator+(int , float) , operator+(int, double) as LongDouble provides converstion to both float and double
 * both are equaly good, so call is ambiguous.
 * 
 * ld = ld + si  
 * candidate functions : all overloaded operator+ and built in operator+
 * viable functions : LongDouble::operator+(const SmallInt &), operator+(double, int), operator+(LongDouble &, double)
 * best match : LongDouble::operator+(const SmallInt &) better match as only const conversion happens. 
 * 
 *************************************************************************************************************************************************************/