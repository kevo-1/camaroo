#include <string>
#include <optional>

namespace camaroo_core {
	enum class TokenType {
		unknown = 0,
		// data values
		num8, num16, num32, num64,
		fnum32, fnum64,
		letter, text,
		toggle,
		// math operators
		add, subtract, multiply, division, equal,
		equal_conditional, and_conditional, or_conditional, not_conditional,
		// other
		LParen, RParen,
		semicolon,
		// data types
		num8_type,num16_type,num32_type,num64_type,
		fnum32_type,fnum64_type,
		text_type,letter_type,
		toggle_type,
		func_type,
	};

	struct Token {
		TokenType Token;
		std::string value;
	};

	class Tokenizer {
		public:
			Tokenizer(const std::string& text);
			void advance();
			std::optional<Token> next_token();
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
