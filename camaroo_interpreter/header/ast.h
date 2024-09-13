#pragma once

#include <tokenizer.h>
#include <string>
#include <memory>

namespace camaroo_core {


	enum class ExprOrder {
		unknown = 0,
		lowest,
		equals,
		less_greater,
		sum_diff,
		product_div,
		prefix, 		// -X or !X
		call, 			// myFunction(X)
	};

	class Node {
	public:
		virtual TokenType token_type() = 0;
		virtual std::string to_string() = 0;
	};

	class StatementNode : public Node {};
	class ExpressionNode : public Node {};

	class IdentifierNode : public ExpressionNode {
	public:
		IdentifierNode(const std::string& value) {
			identifier = { TokenType::identifier, value };
		}
		virtual TokenType token_type() override { return identifier.type; }
		virtual std::string to_string() override { return "ID: " + identifier.value; }
	private:
		Token identifier; // no nodes
	};

	// num32 x = 5;
	// num32 y = 3;
	// x = 5 + y;
	class AssignStmnt : public StatementNode {
	public:
		AssignStmnt(Token type, std::unique_ptr<IdentifierNode> left, std::unique_ptr<ExpressionNode> right)
			:assignType(type), identifier(std::move(left)), expression(std::move(right)) {}
		virtual TokenType token_type() override { return assignType.type; }
		virtual std::string to_string() override { return assignType.value + " " + identifier->to_string() + " = " + expression->to_string(); }
	private:
		Token assignType; // num64, num32, num16, num8, float64, float32, toggle, letter, text, func
		std::unique_ptr<IdentifierNode> identifier; // left node
		std::unique_ptr<ExpressionNode> expression; // right node
	};

	class Num8Expr : public ExpressionNode {
	public:
		Num8Expr(Token token)
			:numToken(token), value(0)
		{
			int8_t v = static_cast<int8_t>(stoll(token.value));
			if (v > INT8_MAX)
				throw std::range_error("Error: Value is bigger than a num8");
			if (v < INT8_MIN)
				throw std::range_error("Error: Value is smaller than a num8");
			value = stoll(token.value);
		}
		virtual TokenType token_type() override { return numToken.type; }
		std::string get_value() { return numToken.value; }
		virtual std::string to_string() override { return numToken.value; }
	private:
		Token numToken; // No nodes
		int8_t value;
	};

	class Num16Expr : public ExpressionNode {
	public:
		Num16Expr(Token token)
			:numToken(token), value(0)
		{
			int16_t v = static_cast<int16_t>(stoll(token.value));
			if (v > INT16_MAX)
				throw std::range_error("Error: Value is bigger than a num16");
			if (v < INT16_MIN)
				throw std::range_error("Error: Value is smaller than a num16");
			value = stoll(token.value);
		}
		virtual TokenType token_type() override { return numToken.type; }
		std::string get_value() { return numToken.value; }
		virtual std::string to_string() override { return numToken.value; }
	private:
		Token numToken; // No nodes
		int16_t value;
	};

	class Num32Expr : public ExpressionNode {
	public:
		Num32Expr(Token token)
			:numToken(token), value(0)
		{
			int32_t v = static_cast<int32_t>(stoll(token.value));
			if (v > INT32_MAX)
				throw std::range_error("Error: Value is bigger than a num32");
			if (v < INT32_MIN)
				throw std::range_error("Error: Value is smaller than a num32");
			value = stoll(token.value);
		}
		virtual TokenType token_type() override { return numToken.type; }
		std::string get_value() { return numToken.value; }
		virtual std::string to_string() override { return numToken.value; }
	private:
		Token numToken; // No nodes
		int32_t value;
	};

	class Num64Expr : public ExpressionNode {
	public:
		Num64Expr(Token token)
			:numToken(token), value(0)
		{
			int64_t v = stoll(token.value);
			if (v > INT64_MAX)
				throw std::range_error("Error: Value is bigger than a num64");
			if (v < INT64_MIN)
				throw std::range_error("Error: Value is smaller than a num64");
			value = stoll(token.value);
		}
		virtual TokenType token_type() override { return numToken.type; }
		std::string get_value() { return numToken.value; }
		virtual std::string to_string() override { return numToken.value; }
	private:
		Token numToken; // No nodes
		int64_t value;
	};




}
