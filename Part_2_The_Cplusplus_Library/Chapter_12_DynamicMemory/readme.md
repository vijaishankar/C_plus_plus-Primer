# <p style = "text-align : center"> DYNAMIC MEMORY </p>
**1. static memory**      
**2. stack memory**      
**3. heap**           
      
* static memory
    - global objects, local static objects and class static objects are created in static memory
    - created before the first use and destroyed when the program ends
 
* stack memory
    - local variables defined in any function is created in stack memory
    - created and destroyed when the block is entered and exited

* heap memory[Dynamic memory] - a seperate pool of memory for the program to use
    - dynamic allocated objects
    - creation and destruction is handled by the program 

# Dynamic memory :
## allocation
- new T, allocates memory in free store(heap) and constructs the object of type T and returns a pointer to T
- new T(optional val), parantheses value initialises the object, if optional value is not provided then built-in types will 
be initialised with zero, string and other classes will be initialised with their default constructors
- new T[sz], allocates memory for sz objects of type t, constructs the objects with default initialisation and returns     pointer to the first element in the array of objects
- new T[sz](), all the objects will be value initialised, but won't take a initialiser inside the parantheses
- new T[sz]{initialisers..}, list initialises the objects with the corresponding initialiser, if there are less initialisers, then value initialises the rest, if more initialisers are present throws bad_array_new_length exception

## deallocation
- delete p, destroys the object pointed by p, and frees the memory which is previously alloted by new
- delete [] p, destroys the array of objects and frees the memory pointed by p, should have been alloted previously by new
    if we don't delete, then memory is not freed untill the program termination leading to memory exhaustion
# SMART POINTERS
smart pointers are pointer like library types, which takes care of deallocation of the memory automatically when the objects are destroyed or goes out of scope
1) shared_ptr
2) unique_ptr
3) weak_ptr

## shared_ptr
- shared_ptr class lets multiple pointers to share the ownership of the same memory, same underlying object is pointed by multiple pointers
- std::shared_ptr<T> sp, creates a shared pointer that can point to object of type T, default initialised with null pointer
- std::make_shared<T> , allocates memory to hold object of type T and returns a shared_ptr.
- std::make_shared<T>(optional_val), value initialises the object
- sp.use_count(), returns how many users are sharing the object.
- when a shared_ptr is destroyed, use_count is decremented by 1, when use_count decrements to 0, object is destroyed and memory is freed 
- *sp, yields the object

## unique_ptr
- unique_ptr owns the object to which it points.
- std::unique_ptr<T> up, creates a unique pointer that can point to object of type T, default initialise with null pointer.
- std::make_unique<T>, allocates memory and constructs object of type T, and returns a unique pointer
- std::make_unique<T>(optional_val), value initialises the object
    * up.reset(new T), old memory is destroyed and pointer returned by new is assigned
    * up.release(), releases the object it points, then null ptr is assigned
    * std::unique_ptr<T> up1(up2) // illegal, no copy or assignment of unique ptrs;
    * std::unique_ptr<T> up1;  up1 = new T;    // illegal no copy or assignment of unique ptrs
- unique_ptr default initialised to null ptr or pointing to a valid object, a new address can be assigned only by calling reset()

## weak_ptr
- weak_ptr shares a weak binding to the objects pointed by a shared pointer, (ie) shared_ptr doesn't count weak_ptrs pointing to the same memory to delete 
- weak_ptrs are used to check before dereferencing if object is still vaild, (ie) atleast one shared_ptr is pointing to it
- std::weak_ptr<T> wp = sp; wp points to the object pointed by sp;
- wp.lock(), returns a shared_ptr if wp.expired() returns false, (ie) object is still valid, or else a null pointer
- wp.expired(), true if object is deleted, false if object is still valid

### Dynamic array
- T *p = new T[sz], p points to the first element in the array of T objects of size sz
- std::shared_ptr<T[]> sp(new T[sz]()), creates a shared_ptr to point an array of T, and new allocates memory to hold sz number of T and value initialises, default initialises in the absence of () and returns a pointer 
- std::unique_ptr<T[]> up(new T[sz]()), same as above
- since the type of the smart pointer is array, they use delete []T when they free memory
- [] operator can be used as they are array type.
- sp[i], yields the reference to ith object in the array pointed by sp

## allocator class
allocator class offers independent allocation and construction of objects in the dynamic memory, and allocator is a template
- std::allocator<T> al, al is a allocator object which can allocate memory to hold object of type T
- al.allocate(n), allocates raw unconstructed memory to hold n objects of type T, and returns a pointer
- al.deallocate(p,n), deallocates the memory that helds n objects of type T, p must be previously returned by allocate and n must be size requested during allocation
- std::construct_at(q, args), q must point to the memory pointed by p, args must match a constructor of the type pointed by q,
- std::destroy(q), destroys the objects pointed by q;  



