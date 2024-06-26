/************************************************************************************************************************************************************
 * @file Ex_9_40.cpp
 * @brief Exercise 9.40: If the program in the previous exercise reads 256 words, what is its likely capacity after it is 
 *        resized? What if it reads 512? 1,000? 1,048?
 * @date 2024-01-01
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/
/**
 * vector<string> svec;
 * svec.reserve(1024);
 * string word;
 * while (cin >> word)
 *      svec.push_back(word);
 * svec.resize(svec.size()+svec.size()/2);
 * 
*/

/**
 * 1. 256 words : 
 *      capacity after resize : 1024 , as resize increases size by only 384(256 +128) words
 * 2. 512 words :
 *      capacity after resize : 1024, as resize increases size by only 768(512 + 256) words
 * 3. 1000 words :
 *      capacity after resize : 1500, as resize increases size by 1500(1000 + 500) words
 * 4. 1048 words :
 *      capacity after resize : 1572, as resize increases size by 1572(1048 + 524) words
 * 
 * 
*/
