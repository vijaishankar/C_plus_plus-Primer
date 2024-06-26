//  using subscript count alphabets, numbers, alphanum, punctuations, whitespaces

#include <iostream>
#include <string>

int main(){
    std::cout << "Enter the sentence :\n";
    std::string sentence;
    getline(std::cin, sentence);

    size_t alpha_count{};
    size_t num_count{};
    size_t alpha_num_count{};
    size_t punct_count{};
    size_t white_space_count{};
    for( std::string::size_type i = 0; i < sentence.size(); ++i){
        int ch = sentence[i];
        if( isalpha(ch) )
            ++alpha_count;
        if( isdigit(ch))
            ++num_count;
        if( isalnum(ch) )
            ++alpha_num_count;
        if( ispunct(ch) )
            ++punct_count;
        if( isspace(ch) )
            ++white_space_count;
    }

    std::cout << sentence << "[no of characters = " << sentence.size() << "]" << std::endl;
    std::cout << "alphabets = " << alpha_count << "\n"
              << "numbers = " << num_count << "\n"
              << "alphanumbers = "<< alpha_num_count << "\n"
              << "punctuations = " << punct_count << "\n"
              << "white spaces = " << white_space_count << std::endl;

    return 0;
}