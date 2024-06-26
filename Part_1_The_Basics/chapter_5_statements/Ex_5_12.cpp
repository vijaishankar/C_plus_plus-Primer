/*  Exercise 5.12: Modify our vowel-counting program so that it counts the number of occurrences of the following 
    two-character sequences: ff, fl, and fi */

    #include <iostream>
int main(){
    std::cout << "Enter a sentence : ";
    char prevch = 0,ch;
    size_t aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0, others = 0, newlnCnt = 0, spCnt = 0, tabCnt = 0;
    size_t ffCnt = 0, flCnt = 0, fiCnt = 0;
    std::string line;
    bool match = false;
    while( getline(std::cin, line) ){
        ++newlnCnt;
        auto beg = line.begin();
        while( beg != line.end()){            
            ch = *beg++;
            ch = tolower(ch);
            if( ch == 'a'){
                ++aCnt;
            }else if(ch == 'e'){
                ++eCnt;
            }else if(ch == 'i'){
                ++iCnt;
            }else if(ch == 'o'){
                ++oCnt;
            }else if(ch == 'u'){
                ++uCnt;
            }else if(ch == ' '){
                ++spCnt;
            }else if(ch == '\t'){
                ++tabCnt;
            }else{
                ++others;
            }
            if(prevch == 'f'){
                if( ch == 'f'){
                    ++ffCnt;
                    match = true;
                }else if( ch == 'l'){
                    ++flCnt;
                    match = true;
                }else if(ch == 'i'){
                    ++fiCnt;
                    match = true;
                }else{
                    match = false;
                }
            }
            if(match){
                match = false;
                prevch = 0;
            }else{
                prevch = ch;
            }
        }    
    }

    std::cout << "\nothers = "<< others << std::endl;
    std::cout << "a : " << aCnt << std::endl;
    std::cout << "e : " << eCnt << std::endl;
    std::cout << "i : " << iCnt << std::endl;
    std::cout << "o : " << oCnt << std::endl;
    std::cout << "u : " << uCnt << std::endl;
    std::cout << "spaces : " << spCnt << std::endl;
    std::cout << "tabs : " << tabCnt << std::endl;
    std::cout << "new line : " << newlnCnt << std::endl;
    std::cout << "ff count : " << ffCnt << std::endl;
    std::cout << "fl count : " << flCnt << std::endl;
    std::cout << "fi count : " << fiCnt << std::endl;

    return 0;
}