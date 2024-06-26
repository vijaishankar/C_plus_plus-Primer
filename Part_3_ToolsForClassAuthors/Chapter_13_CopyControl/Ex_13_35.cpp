/************************************************************************************************************************************************************
 * @file Ex_13_35.cpp
 * @brief Exercise 13.35: What would happen if Message used the synthesized versions of the copy-control members?
 * @date 2024-01-25
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * copying message should not only copy the contents and folders list, it should make the folders to add msg object in their
 * respective list.
 * deleting message should not only delete its data, it should also make the respective folders to delete its pointers
 * Assigning should do both copying an deleting as above.
 *      This is not possible with synthesised ones, as it does only member wise copy, if we use it, we will not get the respective
 * work in the assosiated folders.
 * 
 *************************************************************************************************************************************************************/