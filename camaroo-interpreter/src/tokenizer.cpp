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
    std::string Tokenizer::get_text(){
        std::string result;
        while((current_char >= 'a' && current_char <= 'z') || (current_char>='A' && current_char<='Z')){
            result+=current_char;
            advance();
        }
    }
    Token Tokenizer::return_size_num(const std::string& result){
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
    Token Tokenizer::return_size_fnum(const std::string& result){
            if(std::stold(result) > FLT_MAX){
                return(Token{TokenType::fnum64, result});
            }else{
                return(Token{TokenType::fnum32, result});
            }
    }
    Token Tokenizer::next_token(){
        while (current_char!= '\0')
        {
            if(isdigit(current_char)){
                std::string result = get_number();
                if(std::stoll(result) == std::stold(result)){
                    return return_size_num(result);
                }
                else{
                    return return_size_fnum(result);
                }
            }
            if((current_char >= 'a' && current_char <= 'z') || (current_char>='A' && current_char<='Z')){
                std::string result = get_text();
                if(result.length()> 1){
                    if(result == "true" ){
                        advance();
                        return(Token{TokenType::toggle, result});
                    }else if(result == "false"){
                        advance();
                        return(Token{TokenType::toggle, result});
                    }else if(result == "and"){
                        advance();
                        return(Token{TokenType::and_conditional, result});
                    }else if(result == "or"){
                        advance();
                        return(Token{TokenType::or_conditional, result});
                    }else if(result == "not"){
                        advance();
                        return(Token{TokenType::not_conditional, result});
                    }else{
                        advance();
                        return(Token{TokenType::text, result});
                    }
                }else{
                    advance();
                    return(Token{TokenType::letter, result});
                }
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
                return(Token{TokenType::Rparen, std::string(")")});
            }
            if(current_char == ';'){
                advance();
                return(Token{TokenType::semicolon, std::string(";")});
            }
            if(current_char == '##'){
                advance();
                return(Token{TokenType::multiple_comments, std::string("##")});
            }
            if(current_char == '//'){
                advance();
                return(Token{TokenType::single_comment, std::string("//")});
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