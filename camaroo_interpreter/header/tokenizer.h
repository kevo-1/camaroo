#pragma once
#include <string>
#include <optional>
#include <cinttypes>

namespace camaroo_core {
	enum class TokenType {
		unknown = 0,
		identifier,
		// data values
		num, fnum,
		letter, text,
		toggle,
		// math operators
		add, subtract, multiply, division, equal, modulo,
		//logical operators
		equal_operator, and_operator, or_operator, not_operator,
		// other
		LCurlyBrace, RCurlyBrace,
		LParen, RParen,
		LSquareBracket, RSquareBracket,
		semicolon,
		// data types
		num8_type,num16_type,num32_type,num64_type,
		fnum32_type,fnum64_type,
		text_type,letter_type,
		toggle_type,
		func_type,
	};

	struct Token {
		TokenType type;
		std::string value;
	};

	class Tokenizer {
		public:
			Tokenizer(const std::string& text);
			std::optional<Token> next_token();
			std::optional<Token> peek_next_token();
		private:
			void advance();
			std::string get_number();
			Token return_num_token(const std::string& result);
			Token return_fnum_token(const std::string& result);
			TokenType check_std_type(const std::string& result);
		private:
			std::string text;
			size_t pos;
			char current_char;
			int32_t token_size;
	};
}
