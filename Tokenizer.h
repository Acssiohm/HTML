#pragma once
#include <iostream>
#include "Token.h"
#include "Elements.h"
using namespace std;

class Tokenizer {
public:

	Tokenizer(char* text) :m_text(text), m_pos(0), is_inside_tag(false) {}
	Token popToken();
	Token popAttribute();
	Token popText();
	Token popEndTag();
	Token popString();
	Token popComment();
	Token popTag();

private:
	bool is_inside_tag;
	size_t m_pos;
	char* m_text;
};

