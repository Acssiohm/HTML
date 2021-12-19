#pragma once
#include <iostream>
#include "Elements.h"

class Token {
public:
	enum class Type {
		Comment,
		Balise,
		BaliseEnd,
		EndBalise,
		Text,
		Attribute,
		Equal,
		String,
		EOS,
		Unknown
	};
	Token(Type type = Type::Unknown) :m_type(type), m_length(0), m_text(nullptr){}
	bool isEnd() { return is(Type::EOS); }
	bool is(Type type) { return type == m_type; }
	void setString(char* text, size_t length) {
		m_text = text;
		m_length = length;
	}
	bool isBaliseOf( Balise b);
	bool isEndBaliseOf( Balise b);
	
	char* text() const { return m_text; }
	size_t length() const { return m_length; }
	Type type() const { return m_type; }
	Type m_type;
	char* m_text;
	size_t m_length;
};

