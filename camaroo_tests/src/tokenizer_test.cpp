#include <tokenizer.h>
#include <gtest/gtest.h>
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
	std::string source = get_test_file("camaroo_tests/res/fnum_test.cmr");
    camaroo_core::Tokenizer tokentest(source);

    std::optional<camaroo_core::Token> token = tokentest.next_token();
    EXPECT_EQ(token.has_value(), true);
    EXPECT_EQ(token.value(), camaroo_core::Token(camaroo_core::TokenType::fnum, "5.6"));

    token = tokentest.next_token();
    EXPECT_EQ(token.has_value(), true);
    EXPECT_EQ(token.value(), camaroo_core::Token(camaroo_core::TokenType::fnum, "5684.6546"));

    token = tokentest.next_token();
    EXPECT_EQ(token.has_value(), true);
    EXPECT_EQ(token.value(), camaroo_core::Token(camaroo_core::TokenType::num, "5"));
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
