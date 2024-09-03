#include <tokenizer.h>
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <iterator>
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
    camaroo_core::Tokenizer tokentest(get_test_file("../../camaroo_tests/res/fnum_test.cmr"));
    std::optional<camaroo_core::Token> token = tokentest.next_token();
    EXPECT_EQ(token.has_value(), true);
    EXPECT_EQ(token.value(), camaroo_core::Token(camaroo_core::TokenType::fnum32, "5.6"));
    token = tokentest.next_token();
    EXPECT_EQ(token.has_value(), true);
    EXPECT_EQ(token.value(), camaroo_core::Token(camaroo_core::TokenType::fnum32, "568458645986754896.654645654645654"));
    token = tokentest.next_token();
    EXPECT_EQ(token.has_value(), true);
    EXPECT_EQ(token.value(), camaroo_core::Token(camaroo_core::TokenType::fnum32, "-5.6"));
    token = tokentest.next_token();
    EXPECT_EQ(token.has_value(), true);
    EXPECT_EQ(token.value(), camaroo_core::Token(camaroo_core::TokenType::fnum32, "5"));
}

int main() {

	return 0;
}