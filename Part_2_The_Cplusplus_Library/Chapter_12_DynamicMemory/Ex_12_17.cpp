/************************************************************************************************************************************************************
 * @file Ex_12_17.cpp
 * @brief Exercise 12.17: Which of the following unique_ptr declarations are illegal or likely to result in subsequent program
 *  error? Explain what the problem is with each one.
 *      int ix = 1024, *pi = &ix, *pi2 = new int(2048);
 *      typedef unique_ptr<int> IntP;
 * (a) IntP p0(ix); 
 * (b) IntP p1(pi);
 * (c) IntP p2(pi2); 
 * (d) IntP p3(&ix);
 * (e) IntP p4(new int(2048)); 
 * (f) IntP p5(p2.get());
 * @date 2024-01-16
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/
/*
        int ix = 1024, *pi = &ix, *pi2 = new int(2048);
        typedef unique_ptr<int> IntP;
  (a) IntP p0(ix);  //  illegal : we cannot initialise a unique_ptr with int as ix is int not a pointer
  (b) IntP p1(pi);  //  illegal : unique_ptr should be initialise with dynamic memory, but pi is pointing to local variable, so when p1 is destroyed it will
                              //  call delete on local memory resulting in to throwing runtime exception of segment fault
  (c) IntP p2(pi2); //  legal : p2 is initialised with pi2 pointint to dynamic memory, so when p2 is destroyed, pi2 becomes dangling pointer
  (d) IntP p3(&ix); //  illegal : initialising a smart pointer with address of local object, delete called on local memory
                             //   will throw runtime exception segmentation default
  (e) IntP p4(new int(2048));  //  legal : p4 initialised with dynamic memory holding object of type int with value 2048
  (f) IntP p5(p2.get());  //  illegal : p5 and p2 will point to same memory independently, so when the block ends, delete will be called
                                     // twice on same memory resulting in to throwing exception             

*/