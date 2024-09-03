#include <Tokenizer.h>
#include <iostream>
#include <float.h>
namespace camaroo_core{


    Tokenizer::Tokenizer(const std::string& text): text(text), pos(0){
        current_char = text[pos];
    }
    void Tokenizer::advance(){
        ++pos;
        if(pos >= text.length()){
            current_char = '\0';
        }else{
            current_char = text[pos];
        }
    }

    std::string Tokenizer::get_number(){
        std::string result;
        while(isdigit(current_char)){
            result+= current_char;
            advance();
        }
    }

    Token Tokenizer::return_num_token(const std::string& result){
            if(std::stoll(result) > INT_MAX){
                return(Token{TokenType::num64, result});
            }else if(std::stoi(result) > SHRT_MAX){
                return(Token{TokenType::num32, result});
            }else if(std::stoi(result) > CHAR_MAX){
                return(Token{TokenType::num16, result});
            }else{
                return(Token{TokenType::num8, result});
            }
    }

    Token Tokenizer::return_fnum_token(const std::string& result){
            if(std::stold(result) > FLT_MAX){
                return(Token{TokenType::fnum64, result});
            }else{
                return(Token{TokenType::fnum32, result});
            }
    }

    TokenType Tokenizer::check_std_type(const std::string& result){
            if(result == "num8"){
                return TokenType::num8_type;
            }else if(result == "num16"){
                return TokenType::num16_type;
            }else if(result == "num32"){
                return TokenType::num32_type;
            }else if(result == "num64"){
                return TokenType::num64_type;
            }else if(result == "fnum32"){
                return TokenType::fnum32_type;
            }else if(result == "fnum64"){
                return TokenType::fnum64_type;
            }else if(result == "text"){
                return TokenType::text_type;
            }else if(result == "letter"){
                return TokenType::letter_type;
            }else if(result == "func"){
                return TokenType::func_type;
            }else if(result == "toggle"){
                return TokenType::toggle_type;
            }else{
                return TokenType::unknown;
            }
    }

    Token Tokenizer::next_token(){
        while (current_char!= '\0')
        {
            if(isdigit(current_char)){
                std::string result = get_number();
                if(std::stoll(result) == std::stold(result)){
                    return return_num_token(result);
                }
                else{
                    return return_fnum_token(result);
                }
            }

            if(current_char == '#'){
                advance();
                if(current_char=='#'){
                    while(current_char != '#'){
                        advance();
                    }
                    advance();
                    advance();
                }
            }

            if(current_char == '/'){
                advance();
                if(current_char == '/'){
                    while(current_char != '\n'){
                        advance();
                    }
                }
            }

            if(current_char == '\''){
                std::string result = "\'";
                advance();
                if(current_char == '\\'){
                    result+= current_char;
                    advance();
                }
                result+=current_char;
                advance();
                result+=current_char;
                advance();
                return(Token{TokenType::letter, result});
            }

            if(current_char == '\"'){
                std::string result = "\"";
                advance();
                while (true)
                {
                    if(current_char == '\"' && result[result.size()-1] != '\\'){
                        result+= current_char;
                        advance();
                        break;
                    }
                    result+= current_char;
                    advance();
                }
                return(Token{TokenType::text, result});
            }

            if((current_char >= 'a' && current_char <= 'z') || (current_char >= 'A' && current_char <= 'Z')){
                std::string result = "";
                result += current_char;
                advance();
                while (current_char != ' ')
                {
                    result += current_char;
                    advance();
                }
                TokenType token_type = check_std_type(result);
                return(Token{token_type, result});
            }

            if(current_char == '+'){
                advance();
                return(Token{TokenType::add, std::string("+")});
            }
            if(current_char == '-'){
                advance();
                return(Token{TokenType::subtract, std::string("-")});
            }
            if(current_char == '*'){
                advance();
                return(Token{TokenType::multiply, std::string("*")});
            }
            if(current_char == '/'){
                advance();
                return(Token{TokenType::division, std::string("/")});
            }
            if(current_char == '('){
                advance();
                return(Token{TokenType::LParen, std::string("(")});
            }
            if(current_char == ')'){
                advance();
                return(Token{TokenType::RParen, std::string(")")});
            }
            if(current_char == ';'){
                advance();
                return(Token{TokenType::semicolon, std::string(";")});
            }
            if(current_char == '='){
                advance();
                return(Token{TokenType::equal, std::string("=")});
            }
            if(current_char == '=='){
                advance();
                return(Token{TokenType::equal_conditional, std::string("==")});
            }
        }
    }
}