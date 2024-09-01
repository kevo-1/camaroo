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
        LParen, Rparen,
        semicolon,
        multiple_comments, single_comment,
        equal_conditional, and_conditional, or_conditional, not_conditional
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
            Token return_size_num(const std::string& result);
            Token return_size_fnum(const std::string& result);
            std::string get_text();
        private:
            std::string text;
            size_t pos;
            char current_char;
    };
}
