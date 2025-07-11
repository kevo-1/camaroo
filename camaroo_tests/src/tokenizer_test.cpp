#include <tokenizer.h>
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

std::string get_test_file(const std::string& path) {
    std::ifstream source_file(path);
    std::string source_code;

    source_file.seekg(0, std::ios::end);
    source_code.reserve(source_file.tellg());
    source_file.seekg(0, std::ios::beg);

    source_code.assign(std::istreambuf_iterator<char>(source_file),
                        std::istreambuf_iterator<char>());
    return source_code;
}

TEST (fnum_test, handling_fnum_value) {
    std::string source = get_test_file("camaroo_tests/res/fnum_test.cmr");
    camaroo_core::Tokenizer tokentest(source);

    std::optional<camaroo_core::Token> token = tokentest.next_token();

    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::fnum);
    EXPECT_TRUE(token.value().value == "5.6");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::fnum);
    EXPECT_TRUE(token.value().value == "5684.6546");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num);
    EXPECT_TRUE(token.value().value == "5");
}

TEST (letter_test, handling_letter_value) {
    std::string source = get_test_file("camaroo_tests/res/letter_test.cmr");
    camaroo_core::Tokenizer tokentest(source);

    std::optional<camaroo_core::Token> token = tokentest.next_token();

    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::letter);
    EXPECT_TRUE(token.value().value == "\'\\n\'");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::letter);
    EXPECT_TRUE(token.value().value == "\'l\'");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::letter);
    EXPECT_TRUE(token.value().value == "\'1\'");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::letter);
    EXPECT_TRUE(token.value().value == "\'k\'");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::letter);
    EXPECT_TRUE(token.value().value == "\'K\'");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::letter);
    EXPECT_TRUE(token.value().value == "\'\\\\\'");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::letter);
    EXPECT_TRUE(token.value().value == "\'\\\'\'");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::letter);
    EXPECT_TRUE(token.value().value == "\'\\\"\'");
}

TEST (text_test, handling_text_value) {
    std::string source = get_test_file("camaroo_tests/res/text_test.cmr");
    camaroo_core::Tokenizer tokentest(source);

    std::optional<camaroo_core::Token> token = tokentest.next_token();

    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::text);
    EXPECT_TRUE(token.value().value == "\"hello world\n\"");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::text);
    EXPECT_TRUE(token.value().value == "\"hello ninja\"");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::text);
    EXPECT_TRUE(token.value().value == "\"\"\"\"\"");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::text);
    EXPECT_TRUE(token.value().value == "\"hello2323 \\ \' \"");
}

TEST (toggle_test, handling_toggle_value) {
    std::string source = get_test_file("camaroo_tests/res/toggle_value_test.cmr");
    camaroo_core::Tokenizer tokentest(source);

    std::optional<camaroo_core::Token> token = tokentest.next_token();

    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::toggle);
    EXPECT_TRUE(token.value().value == "true");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::toggle);
    EXPECT_TRUE(token.value().value == "false");
}

TEST (data_type_test, handling_data_types) {
    std::string source = get_test_file("camaroo_tests/res/data_type_test.cmr");
    camaroo_core::Tokenizer tokentest(source);

    std::optional<camaroo_core::Token> token = tokentest.next_token();

    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::toggle_type);
    EXPECT_TRUE(token.value().value == "toggle");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::fnum_type);
    EXPECT_TRUE(token.value().value == "fnum");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num_type);
    EXPECT_TRUE(token.value().value == "num");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num_type);
    EXPECT_TRUE(token.value().value == "num");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::text_type);
    EXPECT_TRUE(token.value().value == "text");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::letter_type);
    EXPECT_TRUE(token.value().value == "letter");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::func_type);
    EXPECT_TRUE(token.value().value == "func");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num_type);
    EXPECT_TRUE(token.value().value == "num");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num_type);
    EXPECT_TRUE(token.value().value == "num");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::fnum_type);
    EXPECT_TRUE(token.value().value == "fnum");
}


TEST (logical_operators_test, handling_logical_operators) {
    std::string source = get_test_file("camaroo_tests/res/logical_operators_test.cmr");
    camaroo_core::Tokenizer tokentest(source);

    std::optional<camaroo_core::Token> token = tokentest.next_token();

    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::and_operator);
    EXPECT_TRUE(token.value().value == "and");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::not_operator);
    EXPECT_TRUE(token.value().value == "not");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::or_operator);
    EXPECT_TRUE(token.value().value == "or");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::equal_operator);
    EXPECT_TRUE(token.value().value == "==");
}

TEST (mathematical_operators_test, handling_mathematical_operators) {
    std::string source = get_test_file("camaroo_tests/res/math_operators_test.cmr");
    camaroo_core::Tokenizer tokentest(source);

    std::optional<camaroo_core::Token> token = tokentest.next_token();

    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::add);
    EXPECT_TRUE(token.value().value == "+");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::subtract);
    EXPECT_TRUE(token.value().value == "-");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::multiply);
    EXPECT_TRUE(token.value().value == "*");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::division);
    EXPECT_TRUE(token.value().value == "/");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::modulo);
    EXPECT_TRUE(token.value().value == "%");
}

TEST (special_characters_test, handling_special_characters) {
    std::string source = get_test_file("camaroo_tests/res/special_character_test.cmr");
    camaroo_core::Tokenizer tokentest(source);

    std::optional<camaroo_core::Token> token = tokentest.next_token();

    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::semicolon);
    EXPECT_TRUE(token.value().value == ";");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::LParen);
    EXPECT_TRUE(token.value().value == "(");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::RParen);
    EXPECT_TRUE(token.value().value == ")");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::LCurlyBrace);
    EXPECT_TRUE(token.value().value == "{");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::RCurlyBrace);
    EXPECT_TRUE(token.value().value == "}");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::LSquareBracket);
    EXPECT_TRUE(token.value().value == "[");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::RSquareBracket);
    EXPECT_TRUE(token.value().value == "]");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::unknown);
    EXPECT_TRUE(token.value().value == "$");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::unknown);
    EXPECT_TRUE(token.value().value == "@");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::unknown);
    EXPECT_TRUE(token.value().value == "~");
}

TEST (Statements_test, handling_statements) {
    std::string source = get_test_file("camaroo_tests/res/statement_test.cmr");
    camaroo_core::Tokenizer tokentest(source);

    std::optional<camaroo_core::Token> token = tokentest.next_token();

    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num_type);
    EXPECT_TRUE(token.value().value == "num");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::identifier);
    EXPECT_TRUE(token.value().value == "x");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::equal);
    EXPECT_TRUE(token.value().value == "=");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num);
    EXPECT_TRUE(token.value().value == "5");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::semicolon);
    EXPECT_TRUE(token.value().value == ";");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::fnum_type);
    EXPECT_TRUE(token.value().value == "fnum");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::identifier);
    EXPECT_TRUE(token.value().value == "y");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::equal);
    EXPECT_TRUE(token.value().value == "=");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num);
    EXPECT_TRUE(token.value().value == "3");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::semicolon);
    EXPECT_TRUE(token.value().value == ";");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::text_type);
    EXPECT_TRUE(token.value().value == "text");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::identifier);
    EXPECT_TRUE(token.value().value == "word");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::equal);
    EXPECT_TRUE(token.value().value == "=");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::text);
    EXPECT_TRUE(token.value().value == "\"Hello world\"");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::semicolon);
    EXPECT_TRUE(token.value().value == ";");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::letter_type);
    EXPECT_TRUE(token.value().value == "letter");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::identifier);
    EXPECT_TRUE(token.value().value == "char");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::equal);
    EXPECT_TRUE(token.value().value == "=");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::letter);
    EXPECT_TRUE(token.value().value == "\'l\'");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::semicolon);
    EXPECT_TRUE(token.value().value == ";");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::toggle_type);
    EXPECT_TRUE(token.value().value == "toggle");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::identifier);
    EXPECT_TRUE(token.value().value == "flag");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::equal);
    EXPECT_TRUE(token.value().value == "=");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::toggle);
    EXPECT_TRUE(token.value().value == "true");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::semicolon);
    EXPECT_TRUE(token.value().value == ";");
}


TEST (peeking_a_token_test, handling_peek_token_function) {
    std::string source = get_test_file("camaroo_tests/res/peeking_token_test.cmr");
    camaroo_core::Tokenizer tokentest(source);

    std::optional<camaroo_core::Token> token = tokentest.peek_next_token();

    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num_type);
    EXPECT_TRUE(token.value().value == "num");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num_type);
    EXPECT_TRUE(token.value().value == "num");

    token = tokentest.peek_next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::identifier);
    EXPECT_TRUE(token.value().value == "x");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::identifier);
    EXPECT_TRUE(token.value().value == "x");

    token = tokentest.peek_next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::equal);
    EXPECT_TRUE(token.value().value == "=");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::equal);
    EXPECT_TRUE(token.value().value == "=");

    token = tokentest.peek_next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num);
    EXPECT_TRUE(token.value().value == "5");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num);
    EXPECT_TRUE(token.value().value == "5");

    token = tokentest.peek_next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::semicolon);
    EXPECT_TRUE(token.value().value == ";");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::semicolon);
    EXPECT_TRUE(token.value().value == ";");

    token = tokentest.peek_next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::fnum_type);
    EXPECT_TRUE(token.value().value == "fnum");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::fnum_type);
    EXPECT_TRUE(token.value().value == "fnum");

    token = tokentest.peek_next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::identifier);
    EXPECT_TRUE(token.value().value == "y");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::identifier);
    EXPECT_TRUE(token.value().value == "y");

    token = tokentest.peek_next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::equal);
    EXPECT_TRUE(token.value().value == "=");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::equal);
    EXPECT_TRUE(token.value().value == "=");

    token = tokentest.peek_next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num);
    EXPECT_TRUE(token.value().value == "4");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num);
    EXPECT_TRUE(token.value().value == "4");

    token = tokentest.peek_next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::semicolon);
    EXPECT_TRUE(token.value().value == ";");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::semicolon);
    EXPECT_TRUE(token.value().value == ";");
}

TEST (identifier_test, handling_identifiers) {
    std::string source = get_test_file("camaroo_tests/res/identifier_test.cmr");
    camaroo_core::Tokenizer tokentest(source);

    std::optional<camaroo_core::Token> token = tokentest.next_token();

    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num_type);
    EXPECT_TRUE(token.value().value == "num");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num);
    EXPECT_TRUE(token.value().value == "4");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::identifier);
    EXPECT_TRUE(token.value().value == "x");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::equal);
    EXPECT_TRUE(token.value().value == "=");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::num);
    EXPECT_TRUE(token.value().value == "4");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::semicolon);
    EXPECT_TRUE(token.value().value == ";");
}

TEST (printing_test, handling_print_statments) {
    std::string source = get_test_file("camaroo_tests/res/printing_test.cmr");
    camaroo_core::Tokenizer tokentest(source);

    std::optional<camaroo_core::Token> token = tokentest.next_token();

    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::print);
    EXPECT_TRUE(token.value().value == "print");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::LParen);
    EXPECT_TRUE(token.value().value == "(");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::text);
    EXPECT_TRUE(token.value().value == "\"Hello world\"");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::RParen);
    EXPECT_TRUE(token.value().value == ")");
    
    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::semicolon);
    EXPECT_TRUE(token.value().value == ";");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::println);
    EXPECT_TRUE(token.value().value == "println");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::LParen);
    EXPECT_TRUE(token.value().value == "(");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::text);
    EXPECT_TRUE(token.value().value == "\"Hello world\"");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::RParen);
    EXPECT_TRUE(token.value().value == ")");
    
    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::semicolon);
    EXPECT_TRUE(token.value().value == ";");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::println);
    EXPECT_TRUE(token.value().value == "println");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::LParen);
    EXPECT_TRUE(token.value().value == "(");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::identifier);
    EXPECT_TRUE(token.value().value == "x");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::RParen);
    EXPECT_TRUE(token.value().value == ")");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::semicolon);
    EXPECT_TRUE(token.value().value == ";");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::print);
    EXPECT_TRUE(token.value().value == "print");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::LParen);
    EXPECT_TRUE(token.value().value == "(");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::identifier);
    EXPECT_TRUE(token.value().value == "x");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::RParen);
    EXPECT_TRUE(token.value().value == ")");

    token = tokentest.next_token();
    EXPECT_TRUE(token.has_value() == true);
    EXPECT_TRUE(token.value().type == camaroo_core::TokenType::semicolon);
    EXPECT_TRUE(token.value().value == ";");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
