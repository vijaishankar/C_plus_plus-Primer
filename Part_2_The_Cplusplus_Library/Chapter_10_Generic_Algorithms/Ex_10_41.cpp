/************************************************************************************************************************************************************
 * @file Ex_10_41.cpp
 * @brief Exercise 10.41: Based only on the algorithm and argument names, describe the operation that the each of the 
 * following library algorithms performs:
 *          replace(beg, end, old_val, new_val);
 *          replace_if(beg, end, pred, new_val);
 *          replace_copy(beg, end, dest, old_val, new_val);
 *          replace_copy_if(beg, end, dest, pred, new_val);
 * @date 2024-01-08
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

replace(beg, end, old_val, new_val)  
    beg, end : input range 
    old_val  : value to be searched in the range
    new_val  : value to be writen over the element which matches with old_val

    replace : searches the entire input range for every element whose value matches with the value specified by old_val, on matching
              writes the value of new_val over the elements matched

replace_if(beg, end, pred, new_val)
    beg, end  : input range 
    predicate : returns a non-zero when an element satisfies a given condition
    new_val   : new value to be writen

    replace_if : searches the entire input range and calls the predicate on every element, writes the value of new_val over 
                 the element for which predicate returns a non-zero value

replace_copy(beg, end, dest, old_val, new_val)
    beg, end : input range 
    dest     : destination sequence where elements need to be writen
    old_val  : value to search for 
    new_val  : value to be writen

    replace_copy : same as replace algorithm, but instead of writing in the original sequence it copies and writes in the new destination sequence 
                   pointed by the dest with the old_val replaced with new_val

replace_copy_if(beg, end, dest, pred, new_val)
    beg, end : input range 
    dest     : destination sequence
    pred     : predicate which will be called on the element 
    new_val  : new value to be writen

    replace_copy_if : same as replace_if algorithm, but copies the entire sequence and writes to the new sequence pointed by 
                      destination sequence with new_val writen over the elements for which predicates returns true


