# Statements
- **declaration statements**
- **definition statements**
- **expression statements**, expr statements causes the expression to be evaluated
- **while,for,do-while**, provides iterative executions
- **if,switch**, conditional executions
- **continue**, skips the current iteration
- **break**, exits a current loop, switch
- **goto**, which transfers control to a labeled statement
- **try-catch**, defines exception handler
- **throw**, raises an exception
- **return**, stops the exection of a current execution

### Switch-case-default
    switch(val), val is value of any expression converted to integral type, initialised declaration is allowed
    case l : , l is a label, it should be constant integral expression and the form is [case lable :]
    default : , if defalt is empty it should include a null statement.
    variable declaration : if the varible's declaration is in a case, if the case is jumped while matching, then variable should not be used otherwise there will be a compiler error. 

### while(cond)
    condition cannot be empty
    initialised declaration is allowed
    variable declared in conditon or in the body will be created and initialised and destroyed every iteration

### do-while construct
    do{
        //...body
    }while(cond);

    variable declaration is not allowed in condition, as it cannot be used in the body as it is out of scope
    variable declared in the body is out of scope to while, as the scope ends with the end of the block '}', closing braces

### for construct
    for( init-statement condition; expr)
    init-statement can be expressions, declarations and initialisations ending with a ; making it expr statement
    so the form can be written as for( init-expr; cond; expr)
    init-expr can be omitted, but should have a null statement,  for( ; cond; expr)
    condition can be omitted, the abscence will be considered as true by default , for( ; ; expr)
    expr can be omitted too, for( ; ; )

### exception handling
exception handling in c++ consists of three concepts **throw,try-catch and exception classes**
    throw is of form 
        throw expression
    a throw expression is usually followed by a semicolon, which makes it expression statement
    the type of expression determines the kind of expression is thrown
    when exception is thrown it terminates the current function and transfer control to a handler that knows how to handle
    throw should be used inside a try block for the catch clause to be matched, or else terminate is called
    form of try-catch
    try{
        ....// process
    }catch (exception-declaration){
        //...handler
    }catch (exception-declaration){
        //...handler
    }

    try block will consist of code that might throw an exception, followed by one are more catch clauses
    catch has 3 parts, catch keyword, declaration of possibly unnamed object in parantheses and a block. when a catch is selected, the associated block is executed and after finishing, execution continues with the statement immedietly following the last catch clause of the try block
    if there is no exception handler is matched, then execution is transferred to the library function terminate
    terminate behaviour is system dependent but is guaranteed to stop further excecution of the program
  
**Exception Classes**      
    c++ library defines several exception classes that it uses to report problems encountered in std lib functions, and we
    can also use these classes in our programs
**Four headers**     
- exception header - defines the most general kind of exception class exception, It provides only that exception occured but provides no further information
- stdexcept header - defines several general purpose exception classes
- new header - defines the bad_alloc exception type
- type_info header - defines bad_cast exception type

