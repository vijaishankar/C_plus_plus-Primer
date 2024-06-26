/*  Exercise 6.4: Write a function that interacts with the user, asking for a number and generating the factorial of that
    number. Call this function from main. */

#include <iostream>

//  fact function prompts user for a number and prints factorial of given number
void fact(){                           // void is used as function won't return anything, and there are no parameters     
    std::cout << "Enter a number : ";
    int num;
    std::cin >> num;

    int res = 1;
    for(int i = 1; i <= num; ++i){    //  for loop will multiply 1 * 2 *... * num
        res *= i ;
    }

    std::cout << num << "! : " << res << std::endl;
}

int main(){
    
    fact();
    fact();
    return 0;
}