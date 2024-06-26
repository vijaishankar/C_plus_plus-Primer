/************************************************************************************************************************************************************
 * @file Ex_16_11.cpp
 * @brief Exercise 16.11: The following definition of List is incorrect. How would you fix it?
 * template <typename elemType> class ListItem;
 * template <typename elemType> class List {
 * public:
 *      List<elemType>();
 *      List<elemType>(const List<elemType> &);
 *      List<elemType>& operator=(const List<elemType> &);
 *      ~List();
 *      void insert(ListItem *ptr, elemType value);
 * private:
 *      ListItem *front, *end;
 * };
 * @date 2024-02-10
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/*
 * template <typename elemType> class ListItem;
 * template <typename elemType> class List {
 * public:
 *      List<elemType>();   //  no need to use template argument in the class name inside the definition as it is implicitly added by the compiler
 *      List<elemType>(const List<elemType> &);
 *      List<elemType>& operator=(const List<elemType> &);
 *      ~List();  
 *      void insert(ListItem *ptr, elemType value);   // when we use ListItem we are instantiating a new class, so template argument should be passed 
 * private:                                           // in the angle brackets following the template name. just because element type is the parameter name                                      
 *      ListItem *front, *end;                        // used in both class templates we cannot assume it to be implicitly passed as the argument for instantiation
 * };
 * 
 */
#include <iostream>

template <typename elemType> class ListItem;
   template <typename elemType> class List {
   public:
        List();  
        List(const List &);
       List& operator=(const List &);
        ~List();  
        void insert(ListItem<elemType> *ptr, elemType value);   
   private:                                                                             
       ListItem<elemType> *front, *end;  
};

int main(){
    List<int> ilst;

}