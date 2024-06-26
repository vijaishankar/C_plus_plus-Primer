/************************************************************************************************************************************************************
 * @file Ex_9_6.cpp
 * @brief Exercise 9.6: What is wrong with the following program? How might you correct it?
            list<int> lst1;
            list<int>::iterator iter1 = lst1.begin(),
            iter2 = lst1.end();
            while (iter1 < iter2) /* ... /
 * @date 2023-12-28
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

/**
 * iter1 needs to be incremented to iterate through the range
 * by repeatedly incrementing iter1 we will get iter1 == iter2, as iter2 refers to end of the range.
 * so if iter1 == iter2, means the range is empty as iter2 is one past last element in the range
 * iter1 < iter2, means there is atleast one item, so until the condition is false the iter1 will traverse through the range,
 * but not every container's iterator type supports < operator, so it is safe to incultivate the habit of using
 *      iter1 != iter2
 * so the correct form is 
 *      while(iter1 != iter2 ){ /. . . / ++iter1; }  
*/