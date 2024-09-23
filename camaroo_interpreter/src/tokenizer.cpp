#include <tokenizer.h>
#include <limits.h>
#include <float.h>

namespace camaroo_core {

    Tokenizer::Tokenizer(const std::string& text)
        :text(text), pos(0), current_char(text[pos]), token_size(0) {}

    void Tokenizer::advance() {
        ++pos;
        ++token_size;
        if (pos >= text.length()) {
            current_char = '\0';
        } else {
            current_char = text[pos];
        }
    }

    std::string Tokenizer::get_number() {
        std::string result;
        while (isdigit(current_char) || current_char == '.') {
            result += current_char;
            advance();
        }

        return result;
    }

    TokenType Tokenizer::check_std_type(const std::string& result) {
        if (result == "num8") {
            return TokenType::num8_type;
        } else if (result == "num16") {
            return TokenType::num16_type;
        } else if (result == "num32") {
            return TokenType::num32_type;
        } else if (result == "num64") {
            return TokenType::num64_type;
        } else if (result == "fnum32") {
            return TokenType::fnum32_type;
        } else if (result == "fnum64") {
            return TokenType::fnum64_type;
        } else if (result == "text") {
            return TokenType::text_type;
        } else if (result == "letter") {
            return TokenType::letter_type;
        } else if (result == "func") {
            return TokenType::func_type;
        } else if (result == "toggle") {
            return TokenType::toggle_type;
        } else if (result == "true" || result == "false") {
            return TokenType::toggle;
        } else if (result == "or") {
            return TokenType::or_operator;
        } else if (result == "and") {
            return TokenType::and_operator;
        } else if (result == "not") {
            return TokenType::not_operator;
        } else if (result == "print") {
            return TokenType::print;
        } else {
            return TokenType::identifier;
        }
    }

    std::optional<Token> Tokenizer::peek_next_token() {
        std::optional<Token> temp_token = next_token();
        pos -= token_size;
        current_char = text[pos];
        return temp_token;
    }

    std::optional<Token> Tokenizer::next_token() {
        token_size = 0;
        while (current_char != '\0') {
            if (isdigit(current_char)) {
                std::string result = get_number();
                if (result.find('.') != std::string::npos)
                    return Token{TokenType::fnum, result};
                return Token{TokenType::num, result};
            }

            if (current_char == '#') {
                advance();
                if(current_char=='#') {
                    while (current_char != '#') {
                        advance();
                    }
                    advance();
                    advance();
                }
            }

            if (current_char == '/') {
                advance();
                if (current_char == '/') {
                    while (current_char != '\n') {
                        advance();
                    }
                }
                else {
                    return(Token{TokenType::division, "/"});
                }
            }

            if (current_char == '\'') {
                std::string result = "\'";
                advance();
                if (current_char == '\\') {
                    result += current_char;
                    advance();
                }
                result += current_char;
                advance();
                result += current_char;
                advance();
                return(Token{TokenType::letter, result});
            }

            if (current_char == '\"') {
                std::string result = "\"";
                advance();
                while (true) {
                    if (current_char == '\0')
                        break;
                    if (current_char == '\"' && result[result.size()-1] != '\\') {
                        result += current_char;
                        advance();
                        break;
                    }
                    result += current_char;
                    advance();
                }
                return(Token{TokenType::text, result});
            }

            if ((current_char >= 'a' && current_char <= 'z') || (current_char >= 'A' && current_char <= 'Z') || (current_char == '_')) {
                std::string result = "";
                result += current_char;
                advance();
                while (isalnum(current_char) && current_char != ' ' && current_char != ';' && current_char != '\n' && current_char != '\0') {
                    result += current_char;
                    advance();
                }
                TokenType token_type = check_std_type(result);
                return(Token{token_type, result});
            }

            if (current_char == '+') {
                advance();
                return(Token{TokenType::add, std::string("+")});
            }
            if (current_char == '-') {
                advance();
                return(Token{TokenType::subtract, std::string("-")});
            }
            if (current_char == '*') {
                advance();
                return(Token{TokenType::multiply, std::string("*")});
            }
            if (current_char == '%') {
                advance();
                return(Token{TokenType::modulo, std::string("%")});
            }
            if (current_char == '(') {
                advance();
                return(Token{TokenType::LParen, std::string("(")});
            }
            if (current_char == ')') {
                advance();
                return(Token{TokenType::RParen, std::string(")")});
            }
            if (current_char == '{') {
                advance();
                return(Token{TokenType::LCurlyBrace, std::string("{")});
            }
            if (current_char == '}') {
                advance();
                return(Token{TokenType::RCurlyBrace, std::string("}")});
            }
            if (current_char == '[') {
                advance();
                return(Token{TokenType::LSquareBracket, std::string("[")});
            }
            if (current_char == ']') {
                advance();
                return(Token{TokenType::RSquareBracket, std::string("]")});
            }
            if (current_char == ';') {
                advance();
                return(Token{TokenType::semicolon, std::string(";")});
            }
            if (current_char == '=') {
                advance();
                if(current_char == '='){
                    advance();
                    return (Token{TokenType::equal_operator, std::string("==")});
                }
                return(Token{TokenType::equal, std::string("=")});
            }
            if (current_char != ' ' && current_char != '\n' && current_char != '\0') {
                std::string result = "";
                result+= current_char;
                advance();
                return Token{TokenType::unknown, std::string(result)};
            }
            advance();
        }
        return std::nullopt;
    }
}
