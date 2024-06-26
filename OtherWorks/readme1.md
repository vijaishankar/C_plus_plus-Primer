
# TYPES OF INITIALISATION
1) default initialisation : when objects are not provided any initial value, objects are default initialise
    * built-in types defined outside all other functions are given 0
    * built-in types defined inside functions have undefined value
    * string objects are given empty string
    * class objects are constructed with default constructors
    ex:- int n;

2) value initialisation : objects are initialised with the value of the initialiser, if no value is provided built-in types are initialised with 0 and the other types are default initialised   
    ex:- int n(8), m();

3) list initialisation : list of initialisers given inside a pair of braces.
    - less initialisers than the no.of objects, then the remaining will be value initialsed.
    - more initialisers than the no.of objects, exception is thrown
    ex:- int arr[5]{1,2,3,4}   // 5th element in the array is value initialised

4) direct initialisation : when initialiser is provided in the parantheses 
    ex:- std::vector<int> ivec1(ivec2);

5) copy initialisation : when an object is initialised from another object using = operator
    - value of the object in the right hand side is copied in to the object in left hand side of the operator
    ex:- std::vector<int> ivec1 = ivec2;


### Macros & pre-defined valiables
    pre-defined variable :-
    __fun__  - function name, compiler implicitly defines the function name in every function, it is const char* pre-processor variable
    __FILE__ - file name 
    __LINE__ - line no 
    __TIME__ - system time
    __DATE__ - system date