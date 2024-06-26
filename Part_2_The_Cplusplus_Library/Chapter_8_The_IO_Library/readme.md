# THE INPUT OUTPUT LIBRARY
    The Input Output Library provides a set of classes to perform input and output operations
    HEADERS
        1. iostream - input from and output to standard(console) input and output stream 
        2. fstream - input from and output to named files
        3. sstream - input from and output to in-memory string streams
• istream (input stream) type, which provides input operations       
• ostream (output stream) type, which provides output operations      
• cin, an istream object that reads the standard input      
• cout, an ostream object that writes to the standard output       
• cerr, an ostream object, typically used for program error messages, that writes to the standard error      
• The >> operator, which is used to read input from an istream object      
• The << operator, which is used to write output to an ostream object      
• The getline function (§ 3.2.2, p. 87), which reads a line of input from a given istream into a given string      
• istringstream and ifstream inherits from istream, so can be used anywhere we use cin       
• ostringstream and ofstream inherits from ostream, so can be used anywhere we use cout               

> ifstream and istringstream inherits from istream, so we can use obj of ifstream and istringstream in place of cin    

    cin >> word;    ifstreamobj >> word;     istringstreamobj >> word
    getline(cin, line),     getline(ifstreamobj,line),      getline(istringstreamobj, line);       

> ofstream and ostringstream inherits from ostream, so we can these types in place of cout               

    cout << word;   ostreamobj << word      ostringstreamobj << word

### No Copy or Assign for IO Objects only References      
    ofstream out1, out2;
    out1 = out2                // error : can't assign stream objects
    ofstream print(ofstream )  // error : will be considered as function call, stream objects cannot be copied
    out2 = print(out2)         // error : cannot copy stream objects
### No Const
    reading and writing changes the state of the subject, so no const references

### Condition State
    The state of a io stream(obj) can be accessed by strm::iostate type - machine dependent integral 

### Flushing Buffer
    cout << "hi" << endl;  //  writes hi and a newline, then flushes the buffer
    cout << "hi" << flush; //  writes hi and flushes the buffer
    cout << "hi" << ends;  //  writes hi and a null, flushes the buffer
    cout << unitbuf;       //  all writes will be flushed immedietly
    cout << nounitbuf;     //  returns to normal buffering

### fstream
    along with all the operations that iostream provides, fstream adds these file specific operations

### filemodes
    'in' mode is implicit in ifstream, it cannot be used ofstream
    'out' and 'trunc' mode is implicit in ofstream, so by default ofstream truncates the file opened unless 'app' mode is specified, if file not present a new file is created, 'out' cannot be specified with ifstream    
    
    fstream should be close the file, before bound to other file, if not fstream will set failbit.
    modes are reset every time file is opened.
    file is implicitly closed when fstream obj gets destroyed at the end of the block
    ex :-
        while(1){
            std::ofstream out(fileName);    //  out is created
            out << "some thing"
        }   // out gets destroyed
        every time the loop iterates out is created and destroyed

### sstream - in-memory input output of strings
    istringstream, reads  a string
    ostringstream, writes a string

    stringstream.str() will return a copy of the underlying string and stores a copy of the new string if passed,
    # even after extracting all characters from the stream
    # even if failbit, eofbit, badbit is set true
    # as extraction only moves the pointer, but doesn't modify the string in anyway, so strm will always have the string
    https://stackoverflow.com/questions/43124746/istringstreamstr-does-not-return-current-contents
    https://en.cppreference.com/w/cpp/io/basic_istringstream/str   

    sstream is mainly used to efficiently process numbers converted to and from string