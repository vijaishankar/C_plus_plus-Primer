### functions - a named block of code       
*functions* definitions has a **return_type, function_name, list of zero or more parameters, statement block{funtion body enclosed in curly braces }**.       
functions are called by using **() call operator**, a call operator takes an expression, which is a function_name or pointer to a function and inside the parantheses is a comma seperated list of arguments, the **type** of call operator is the return type of the function      
a call operator does two things      
- it initialises the function_parameters with the corresponding arguments and     
- transfers execution from calling function to the called function      
Execution of function begins with implicit definition and initialisation of its parameters     
Execution of function is stopped when it encounters a return statement      
Return statements does two things      
- it returns the value in the return if any
- transfers execution from called function to calling function      
- value returned by the function is used to initialise the result of the call expression       

### funcion prototype
    function prototype is nothing but function declaration which specifies the return type and list of parameters and function name and ends with ; and there is no function body.     
          
    return_type func_name(param_list);     
    
### Parameter as reference to const    
    if parameter is a plain reference, calling function won't be able to pass     
-   literal constant      
-   const object     
    if parameter is a reference to const, calling function can use literal or const object to call    
    ex :-    
        void print(const std::string &ref);                             
            std::string str("good example");                    
            const std::string cstr("encryption_key");      
            print(str);             // ok                     
            print(cstr);            // ok                     
            print("hello world");   // ok                      
                                                                                               
        void display(std::string & ref);             
            display(str)    // ok       
            display(cstr)   // error : can't bind const string to plain ref      
            display("hello world")  /* error : can't bind string literal to plain reference     

### argc - argv      
-   last element in the arguments to the main is guaranteed to null pointer || 0      
    while(*argv) { std::cout << *argv++ << " "}    // each argument is printed untill *argv is null pointer         

##  Initialiser list    
-    initialiser list is a container of const elements of same type    
-    once initialised cannot be modified     

## return statement    
-   creates a temporary object with the result which will be used to initialise the result of call expression    
-   functions with **void** return type allows us to use return statement without value to exit at intermediate point    
-   return statements can use initialiser_list to list initialise any container     
-   when there is no return statement provided for a function with return type, there are chances that compiler fails to point it as an error in that case what happens when calling such a function is undefined, refere Ex_6_30.cpp
-   compiler will implicitly place a return statement if there is none in a function with void return type 

##  call operator     
-   **lvalue** if return returns a reference or a pointer or a object of class type, then it is a lvalue   
-   **rvalue** if return returns plain value it is rvalue   
-   **lvalue** result can be used as left operand of ***member access*** operator and lhs of assignment         
    ex:-         
        char &get_space(std::string &str);        
        get_space returns a reference to space character in the string..         
        get_space(str1) = '#';  //  here result of call is a lvalue, so it is used to assign '#'        
        std::string &get_name(std::string &info);      
        get_name(information).size(); /*result is reference to string, for (.) operator, result of () is a left operand, 
                                       so . operator fetches size member */           

### Functions returning Pointer and Reference to an Array
    std::string (*function())[size]{ /*.....*/}
    int (*function())[size]{/*.......*/}

    std::string (&function())[size]{/*..........*/}
    int (*funcion())[size]{/*..................*/}
#### using type alias
    type alias for ptr :    
    using ptrtoarr = std::string (*)[size]
    typedef std::string (*ptrtoarr)[size]

    using ptrtoarr = int (*)[size]
    typedef int (*ptrtoarr)[size]

    type alias for ref :
    using reftoarr = std::string (&)[size]
    typedef std::string (&ptrtoarr)[size]

    using reftoarr = int (&)[size]
    typedef int (&reftoarr)[size]

#### trailing return type
    auto function() -> std::string (*)[size]   //   auto informs the compiler that return type can be deduced 
    auto funcion() -> int (*)[size]

    auto function() -> std::string (&)[size]
    auto function() -> int (&)[size]  

#### decltype
    std::string strarr[size];
    decltype(strarr) & function(){/*......*/}
    decltype(strarr) * function(){/*........*/}

#### Example :-
    #include <iostream>

    using RefarrOfTenStrings = std::string (&)[10];
    typedef std::string (*PtrToTenStrings)[10];

    std::string tenStringsArr[10];

    decltype(tenStringsArr) *functionRetPtr(RefarrOfTenStrings strArr){
        return &strArr;
    }

    auto functionRetRef(RefarrOfTenStrings strArr)-> std::string (&) [10]{
        return strArr;
    }

    std::string (*function(PtrToTenStrings ptrStrArr))[10]{
        return ptrStrArr;
    }


    int main(){
        std::string strArr[10] = {"one","two","three","four","five","six","seven","eight","nine","ten"};
        for( auto str : *function(&strArr)){
            std::cout << str << " ";
        }   

        std::cout << "\n-----------------------------\n";
        for( auto str : functionRetRef(strArr)){
            std::cout << str << " ";
        }

        std::cout << "\n------------------------------\n";
        for(auto str : *functionRetPtr(strArr)){       //  ptr to an array is a rvalue, to use in range for it must be- 
            std::cout << str << " ";                   //  -dereferenced to get the object at that address. 
        }

        return 0;
    }

### In C++ name lookup happens before type checking     

### default arguments     
-   all parameters following the parameter having default argument should be provided default arguments     
-   a function can have many declarations but cannot redefine a default argument, but can add default arguments to a parameter which doesn't have before but all parameters following it should have default arguments     
-   during a function call, default arguments are for the trailing(right most argument) of  the call.    
    ex:-    
        int function(int x = 5, int y = -10, z = 45);    
        function(10) == function(10,-10,45) , argument specified is used for x     
        function(10,-20)  == function(10,-20,45), arguments specified are used for x , y     

        that's why all parameters following the parameter with default argument should be provided default arguments    
    
### inline
    small functions with one or two statements can be placed as inline using the keyword inline     
    inline int function(int num){
        return num * num;
    }

    inline is a request to the compiler, but compiler chooses whatever it thinks right

#### constexpr
    for a function to be constexpr function
-   every object defined needs to be a constexpr      
-   every function it calls should be constant expression     
-   only one return statement is allowed

constexpr function is allowed to return a non-constant type if it is called with non-const arguments, in that case it will be a normal function.    

### Macros & pre-defined valiables
    pre-defined variable :-
    __fun__  - function name, compiler implicitly defines the function name in every function, it is const char* pre-processor variable
    __FILE__ - file name 
    __LINE__ - line no 
    __TIME__ - system time
    __DATE__ - system date

##  FUCTION MATCHING
**list of functions**
    func();
    func(int);
    func(int, int);
    func(double, double x = 9.8)
    func(std::string)
    func(SalesItem &);
    getx();
    gety();
    print()
### 1st step : CANDIDATE FUNCTION 
    candidate functions are the set of overloaded functions, whose name matches the function name being called.
    for the function call, 
    ex 1 :- func(43);
    candidate functions are :-
        func();
        func(int);
        func(int, int);
        func(double, double x = 9.8);
        func(std::string);
        func(SalesItem &);

### 2nd step : VIABLE FUNCTION
    those functions from the set of candidate functions who can be called with the arguments in the given call.     
-   To be viable, a function must have same no of parameters as there are arguments,
-   and the types of arguments either matches or can be convertible to the parameters types.
    so the viable functions to the call are,
    func(int);                      //  can be called as it takes one parameter of type int
    func(double, double x = 9.8)    //  can be called, as int can be converted to double parameter, second parameter has 
                                        default argument
### 3rd step : BEST MATCH  
from the set of viable functions, the function with the best match is called, there is an overall best match if there is one and only function for which      
-   There is atlest one argument for which the match is better than the match provided by any other viable functions
-   The match of each argument is no worse than the match required by any other viable function
    a match is better if the types of arguments and parameters are closer to each other
    func(int) - argument '43' is of the same type as the parameter 
    func(double, double x = 9.8) - argument '43' needs to converted to double type 
    so func(int) is the exact match,
    an exact match is better than a match that requires a conversion.

    ex 2 :-
    func(4.3,23);
    candidate functions :-
        func();
        func(int);
        func(int, int);
        func(double, double x = 9.8);
        func(std::string);
        func(SalesItem &);
    viable functions :-
        func(int,int)
        func(double,double)

        func(int, int) - first argument '4.3' needs to be converted to int, second matches with the second parameters type
        func(double,double) - first argument matches to the first parameters type, second argument '23' needs to be 
                              converted to int
        when we consider only the first argument, func(double, double) is an exact match
        when we consider only the second argument, func(int, int) is an exact match
        Compiler will rejects this call, because it is ambiguous.
    
#### Conversions are Ranked during function matching
1. **exact matches** no conversion needed
   - identical parameters and argument
   - function or array to pointers of similar types
   - top level const is added or discarded
2. match through **const conversion**  (int i; const int *p = &i) non-const pointer is converted to pointer to const
3. match through **promotion** (short s; s + 4;) s is promoted to int
4. matching through **arithmatic or pointer** conversion  (int to double or pointer to bool etc)
5. matching through **class type** conversion   (class define the implicit conversion to other type)

### Pointer to functions
    function pointer is like any other pointer, that denotes a function rather than an object, like any other pointer, function pointer points to a particular type(function type)
    A function type is determined by its return type and its parameter types
        bool function(int , int);  has a type bool (int , int);
        void print(const std::string &) has a type void (const std::string &)
        int sub(int, int) has a type int (int, int)
    ordinarily function name decays in to function pointer like arrays
#### declaration of pointer to functions
    - typedef bool (*fp)(int, int)   //  fp is a pointer to function which takes two int parameters and returns a int type
    - typedef bool f(int, int)       //  f is a funcion type which takes two int parameters and returns a int type, when 
                                         used it is implicitly converted to pointer type
    - using fp = bool (*)(int, int)  //  fp is a pointer to function
    - using f = bool (int, int)      //  f is a function type
    - typedef decltype(function) *fp //  fp is a pointer type
    - typedef decltype(function) f   //  f is a function type
    - using opfp = int (*)(int,int) 
    - using opf = int (*)(int, int)
    all the declarations of fp and f are same f is implicitly converted to pointer
#### storing a function pointer
    fp fp1 = function;
    f *fp2 = function;
    auto newfp1 = print;
    bool (*newfp2)(int, int) = function;
    decltype(print) *newfp3 = print;

    std::vector<opfp> opfpvec{add, sub, mul, div}   // int add(int m,int n){return m+n; }  similarly other functions only 
                                                   differ by only definition not by types
                        
#### passing a pointer
    void printResults(std::ostream &, *opfp);  // function that takes a ostream obj and function pointer

    printResults(std::cin, add) //  fuction call with cin, and add as arguments

#### returning a pointer
    unlike other cases, when comes to returning, a funtion type is not implicitly converted to function pointer and we can't return a function type.

    opfp returnFunctionPtr(decltype(opfpvec), size_t index);
    opf *returnFunctionPtr(decltype(opfpvec), size_t index); 
    decltype(function) *returnFunctionPtr(decltype(opfpvec), size_t index);
    auto returnFunctionPtr(decltype(opfpvec), size_t index);
    auto returnFunctionPtr(decltype(opfpvec), size_t index) -> int (*)(int,int)






