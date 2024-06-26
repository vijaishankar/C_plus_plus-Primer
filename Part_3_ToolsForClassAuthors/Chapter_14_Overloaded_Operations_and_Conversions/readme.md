# <p style = "text-align:center"> OVERLOADED OPERATIONS AND CONVERSIONS </p>

## Overloaded operators 
***operators*** can be overloaded like overloading functions, it gives us a way to define what should happen when
***built-in*** operators are used with our classes.     
*Overloaded operators* can either be members or non-members, but should take atleast one parameter of class type.     
They are similar to a function, as they have a return_type, special_function name as "operator" keyword followed by the operator symbol being defined, a parameter list inside parantheses and a body.     
They have same precedence, associativity and same number of arguments as the corresponding built-in operators.    

    return_type operator+(param_list){   //  defines + operator
        .../body
    };
    

    class foo{
        public :
            foo operator+(const foo &rhs){    //  ....1
                // body
                return *this;
            }
    };

    foo operator+(const foo &lhs, const foo &rhs){   //   ....2
            // body
        return temp;
    }

    1 - operator+ is a member, where this pointer is implicitly bound to the left operand, and the right operand is passed as explicit parameter.

    2 - operator+ is defined as a non-member, where left is passed as the first param, and right operand is passed as the second param

    can be called indirectly by using the operator 
        ex :-  foo f1, f2;
               foo f3 = f1 + f2;
    or can be called explicitly
               foo f3 = f1.operator+(f2);   //  member functions can be called explicitly

**Members**
- assignment(=), call_operator(), subscript([]), member_access operator(->) should be defined as members.
- The compound assignment operators are not required to be members but mostly defined as members
- operators that changes the state of the obect such as increment(++) post and pre, decrement(--) post and pre, 
and dereference are usually defined as members.

**Non-Members**
- symmetric operators - which when operands are reversed gives the same meaning, should be defined as non-members. arithmatic operators, equality operators, relational operators and bitwise operators are all symmetric operators
- stream operators should be defined as non-members, since for member, class type should be in left, which is not so here.
## Input and Output operators :  << >>
non-member function, as class type is in right hand side to the stream operators.
#### operator<< - Output stream operator
- first parameter - non-const reference to output stream, non-const because when writen changes the state of the object and reference as stream objects cannot be copied.
- second parameter - const reference to class type, const because writing to a stream doesn't change the object.
- return_type - a reference to the output stream 
- should be declared as friend function to have access to non-public members.    

        ex:-   
           class foo{
           friend ostream & operator<<( ostream &, const foo &);
           };

           ostream & operator<<( ostream & os, const foo & f){
                os << f.members ;
                return os;
           }
As normally << operators do minimal formating, it should be followed for class too, as the users of the operator excepts it to behave in the same way.
#### operator>>   -  Input stream operator
- first parameter - non-const reference to input stream, same reasons as output operator
- second parameter - non-const reference to class type, non-const as what read is going to be written to the object.
- return_type - reference to input stream
- friend declaration is needed to access non-public members
- should check for read errors and should put the object in a consistent state if there is an error, probably default construct the object    

        ex :-
        class foo{
            friend istream & operator>>(istream &, foo &);
        };

        istream & operator>>( istream & is, foo & f){
            is >> f.members;
            if(!is){  // checks whether read is successfull
                ...do what needs to be done to put the object in a consistent state
                is.set(std::iostream::failbit) // indicate the read error
            }
            return is;
        }
    
- read errors : incorrect type and eof

## Arithmetic and Relational operators
### Arithmetic Operators
Defined as non-member functions so that either operand can be converted as class type
- first & second parameter : left operand and right operand is passed as first & second parameters respectively, both are const reference as these operators normally don't change the state of the objects.
- return_type : returns a copy of the result which is distinct to value of both the operands as result is calculated in a local temp variable
- classes which define arithmetic operators should defined corresponding **compound assignment** operators and normally should delegate the real work to them, as they assign the result to the left operand, first parameter is non-const reference to left operand if designed as non-member, but normally they designed as members.     

        ex :-
        class Foo{
        friend Foo operator+(const Foo &lhs, const Foo &rhs){
            Foo temp(lhs);
            temp += rhs;    // delegates work to +=
            return temp;
        }
        Foo & operator+=(const Foo &rhs){
            member1 += rhs.member1;  //  each member is added using += operator defined by them
            ...body
            return *this;
        }

        }

### Equality operator  ==  !=
- defined as non-member function 
- first parameter - const reference to left operand
- second parameter - const reference to righ operand
- return type - bool indicating equal or not
- classes defined == should define != and only one should do the real work, and another should delegate work.
They are defined to check equality between two objects of the class type, which checks the equality of each member from lhs with corresponding from the rhs.    
Library algorithms uses == and < definitions of the class, so it is easy to use algorithms on the class type which has defined these       

        ex:- 
        class Foo{
        friend bool operator==(const Foo &lhs, const Foo &rhs){
            return lhs.member1 == rhs.member1 &&
                   lhs.member2 == rhs.member2 &&
                   ...etc
        }

        friend bool operator!=(const Foo &lhs, const Foo &rhs){
            return !(lhs == rhs);
        }
        };
        
### Relational operators
- non-members
- first and second parameter : const references to the operands
- return_type : bool
- Assosiative containers uses < operator of the key type to store the data    

        ex:- 
        class Foo{
        friend bool operator<(const Foo &lhs, const Foo &rhs){
            return .../class type should have a natural comparison
        }
        };

### Assignment operators
- members as they assign the value of the right hand operand value to the left hand operand
- explicit parameter : const reference to the class type, right operand is passed as explicit parameter
- return_type : reference to the left hand operand(object to which 'this' is implicitly bound)
- Need to check for self assignment before assigning.
    ```c++
    
        class Foo{
        public :
            Foo & operator=(const std::initializer_list<T> &il){
                ....body  //  when objects of other types are used, no need to check for self assignment
            }
        };
    ```

### Compound Assignment operators
- normaly defined as members, but not a necessary
- explicit parameter : const reference to the right operand
- return_type : reference to the left operand
    ```C++
    
        class Foo{
        public :
            Foo & operator+=(const Foo &rhs){
                .../body
                return *this;
            }
        };
    ```

### Subscript operator
- classes which behaves like containers, should define [] operator to retrieve the element by position
- should be defined as members
- parameter : size_t to indicate the position
- return_type : reference to the element type, so used to both read and write
- should have const version and non const version, const version should return reference to const element type

```c++
        class Foo{
        public :
            T & operator[](size_t i){
                return data[i];
            }
            const T & operator[](size_t i) const {
                return data[i];
            }
        };

```
### Increment and Decrement 
- defined as members as they change the state of the object
- classes define iterators should defined these to move iterators across the containers
- both pre and post should be defined
- return_type of pre operators : returns reference to the object
- return_type of post operators : should return the old value
- post operators should save state of the object before increment or decrement and then saved state should be refturned by value
- to distinguish pre and post operators, post operators normally take a unnamed second parameter, it is unnamed as it is not going to be used, as ++ and -- are unary operators pre and post don't get differentiated for overloading so post operator should take a unnamed second parameter.compiler supplies 0 for the parameter when called.
- post operators should normally delagate the work to pre operators.
    ```c++
     
        class Fooiter{
        public :
            Fooiter & operator++(){
                ../body
                return *this
            }
            Fooiter operator++(int){   //  as we don't use the parameter, it is not used
                auto old_iter = *this;
                ++*this;    //  calls the pre-increment operator on this object
                return old_iter;
            };
        };
    ```

### Member-Access operator
#### dereference operator *
- defined as member, classes that behaves like iterators should define operator*()
- returns a reference to the pointed type
- operator-> has restrictions on what it should return unlike other operators, as others can be defined to do anything we like though it shouldn't be done.
- point->mem;
1) if arrow operator is called on a pointer, then the pointer is dereferenced to get the object and the indicated member is fetched. if mem is not found, the code is in error.      
point->mem  == (*point).mem;
2) if arrow operator is called on a object which has defined operator-> then the result of operator-> is used to fetch mem, If the result is a pointer then step 1 is repeated on that object, this process continues untill either a pointer to an object with indicated member is returned or the code is in error.  
obj->mem == (ret_type from obj.operator->()).mem       
*** The overloaded operator-> should either return a pointer or an object with a overloaded operator->  
    
        class Foo{
        public :
            T & operator*() const {
                return t;
            }

            T * operator->() const {
                return &(*this);   // pointer should be returned, as member should be fetched from the returned object
            }
        };
- operator-> normally uses the operator* to get the reference to the object on which it uses & operator to return the pointer to the object.

### call operator - Function objects
Function call operator makes the object callable like any other callable object.
- can define many overloaded operator() functions, type or no.of parameters should differ
- should be defined as members
- takes parameters and returns either void or some-thing.
- objects of classes that has overloaded call operator, are called function objects.
- Function objects can store state, (ie) we can define members to customise the call operator
    ```c++
    
        class Print{
        private :
            std::ostream &os;
            char ch;
        public :
            Print(std::ostream &os_ = std::cout, char ch_ = ' ') : os(os_), ch(ch_) {}
            void operator()(const std::string &str){
                os << str << ch;
           }
        };
    ```

        Print has a constructor which takes a reference to a outputstream, and char as to be printed with default arguments.
        operator() takes a const reference to string which is writen to the output stream along with the char.

        so we can create obects with different output streams and diff char
        Print p1(ostr, '\n'), p2(ofile), p3;
        std::string str("hello world");

        p1(str)   //   writes str to ostr(ostrstream) along with a '\n'
        p2(str)   //   writes str to a file along with a space
        p3(str)   //   writes str to std::cout along with a space

- Function objects are used with algorithms often
    std::for_each(b, e, p3);
    std::copy(b, 3, Print(ofile2, '\n'));

- Lambdas are unnamed function objects of unnamed classes, when we define a lambda, an unnamed class is created with members assigned with captured variables by a contructor that takes the captured variables as parameters and overloaded operator() that takes same parameters as the lambda takes and returns what the lambda is defined to return
- generated call operator of lambdas are const member function by default as they don't change the state of the members by default
- lambdas can be defined mutable to get a non-const version of call-operator
    ```c++
    
        [sz](const std::string &str){ return str.size() < sz ;}  //  lamda defintion
        equivalent defintion of class that will be generated
        class check{
        public :
            check(size_t sz_) : sz(sz_) {}
            bool operator()(const std::string &str)const{
                return str.size() < sz;
            }
        private :
            size_t sz;
        };
    ```

## Library defined function objects
Library provides function objects corresponding to arithmetic, relational and logical operators. These are used in algorithms to change how algorithms compare elements.    
Sort normally sorts the elements in ascending order, but by using function objects we can sort the elements in descending order.    
Most important fact about library function objects is that they work with pointers of different types. (ie) normally comparing two pointers of two different containers is undefined but library function objects guarantees to work with them, So we can use them sort a container of pointers to different types like function.
    ex:- 
        std::less<int>() //  it creates a function object of type lesser which when called returns a bool indicating if the first is lesser than the second
Associative containers use less<key> to store data, as a result we can use pointers as key type.   

## CALLABLE OBJECTS
c++ provides many ways to create callable objects
- functions
- lambdas
- function objects - classes with overridded call operator
- objects created by std::bind()

Each object has a type, each lambda defined is its own unique(unnamed class) type. But these callable objects of different types can have same call signature      
###### return_type (param_types...)   is a call signature of a callable object
    ex:- int func(int , char)    int (int , int)
         [](double p){ return p%2; }    bool (double)

         class foo{
         public :
            void operator(int, string){
                ...body
            }
         };
         objects of foo has a call signature void (int, string)

        call signature of objects created by std::bind()  is old_callable_return_type ( param...)

    Though these callables has same call signature, we cannot store them in a container together normally as they are different types

### LIBRARY FUNCTION TYPE
Library provides a function type, which is a template that takes *call signature* as its type     
```c++
    ex:- 
        class Divide{
        public :
            int operator/(int m, int n){
                return m / n;
            }
        };

        std::function<int (int, int)> f1 = std::plus<int>();
        std::function<int (int, int)> f2 = [](int m, int n ){ return m - n ;};
        std::function<int (int, int)> f3 = Divide();  

        // binops is a function table which maps string(operator sym) to library function type(operation).
        std::map<string, std::function<int (int, int)>> binops =  { {"+", f1},
                                                                    {"-", f2},
                                                                    {"/", f3},
                                                                    {"*", [](int m, int n){ return m*n;}},
                                                                    {"=", std::equal<int>()},
                                                                    {"?", std::bind(callable, _2, _1)}
                                                                  };
```


### OVERLOADING, CONVERSIONS, OPERATORS
#### Conversions
classes provides conversion from class type to another type through conversion operators and conversion from another type to class type through constructors.    
**Conversion operators**
- defined with special name as operator-keyword followed by type_name and parantheses, These don't take any parameters and though don't mention return type returns something that is convertible to the type_name to which it is providing conversion operator.
- should be defined as const member function, as they don't change the state of the object.
```c++

        class foo{
        public :
            operator int() const { return val;}
        };

```
- compiler does a implicit conversions from our class type to another type for which conversion operator is provided, but sometimes it will result in ambiguous call or surprising results, to avoid that conversion operators can be made explicit
```c++
        class foo{
        public :
            explicit operator int() const { return val;}
        };

        static_cast<int>(foo());    //  explicitly calls operator int.
```

- explicit conversion operators are implicitly called in condition statements like
* if, do, while, for
* logical operators
* conditional operator 

- conversions to bool is usually only used in conditions, so they should be defined as explicit.









