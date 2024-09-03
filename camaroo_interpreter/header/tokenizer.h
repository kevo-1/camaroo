#include<iostream>
namespace camaroo_core 
{
    enum class TokenType {
        unknown = 0,
        num8, num16, num32, num64,
        fnum32, fnum64,
        letter, text,
        toggle,
        func,
        add, subtract, multiply, division, equal,
        LParen, RParen,
        semicolon,
        equal_conditional, and_conditional, or_conditional, not_conditional,
        //variable names:
        num8_type,num16_type,num32_type,num64_type,
        fnum32_type,fnum64_type,
        text_type,letter_type,
        toggle_type,
        func_type,
    };
    
    struct Token
    {
        TokenType Token;
        std::string value;
    };

    class Tokenizer{
        Tokenizer(const std::string& text);
        void advance();
        Token next_token();
        private:
            std::string get_number();
            Token return_num_token(const std::string& result);
            Token return_fnum_token(const std::string& result);
            TokenType check_std_type(const std::string& result);
        private:
            std::string text;
            size_t pos;
            char current_char;
    };
}
