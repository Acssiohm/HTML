#include "Tokenizer.h"


Token Tokenizer::popToken() {
	while (isspace(m_text[m_pos])) { m_pos++; }
	if (m_text[m_pos] == 0) {
		return Token(Token::Type::EOS);
	}   
	if (m_text[m_pos] == '<' && m_text[m_pos + 1] == '!' && m_text[m_pos + 2] == '-' && m_text[m_pos + 3] == '-') {
		return popComment();
	}
	char c = m_text[m_pos];
	if (c == '<') {
		if (m_text[m_pos + 1] == '/') {
			return popEndTag();
		}
		is_inside_tag = true;
		return popTag();
	}
	if (is_inside_tag == true) {
		if (c == '>' || (c == '/' && m_text[m_pos + 1] == '>')) {
			if (c == '/') {
				m_pos++;
			}
			is_inside_tag = false;
			m_pos++;
			return Token(Token::Type::BaliseEnd);
		}
		if (c == '=') {
			m_pos++;
			return Token(Token::Type::Equal);
		}
		if (c == '"' || c == '\'') {
			//cout << "\nSTRING :" << c << endl;
			return popString();
		}
		if (isalnum(c)) {
			return popAttribute();
		}
	}
	else {
		return popText();
	}
	cout << "UNKNOWN TOKEN" << endl;
	return Token();
}
Token Tokenizer::popAttribute() {
	char* start = &m_text[m_pos];
	int length = 0;
	while (isalnum(m_text[m_pos]) && m_text[m_pos] != 0) {
		m_pos++;
		length++;
	}
	if (m_text[m_pos] == 0) {
		return Token(Token::Type::EOS);
	}
	Token t(Token::Type::Attribute);
	t.setString(start, length);
	return t;
}
Token Tokenizer::popText() {
	char* start = &m_text[m_pos];
	int length = 0;
	int last_len_bef_space = 0;
	while (m_text[m_pos] != '<' && m_text[m_pos] != 0) {

		length++;
		if (!isspace(m_text[m_pos])) {
			last_len_bef_space = length;
		}
		m_pos++;
	}
	if (m_text[m_pos] == 0) {
		return Token(Token::Type::EOS);
	}
	if (length > last_len_bef_space) {
		last_len_bef_space++;
	}
	Token t(Token::Type::Text);
	t.setString(start, last_len_bef_space);
	return t;
}
Token Tokenizer::popEndTag() {

	m_pos += 2;

	while (isspace(m_text[m_pos])) {
		//length++;
		m_pos++;
	}
	char* start = &m_text[m_pos];
	int length = 0;
	while (m_text[m_pos] != '>') {
		length++;
		m_pos++;
	}
	m_pos++;

	Token t(Token::Type::EndBalise);
	t.setString(start, length);
	return t;
}
Token Tokenizer::popString() {
	char quote = m_text[m_pos];
	char* start = &m_text[m_pos];
	int length = 1;
	m_pos++;
	while (m_text[m_pos] != quote && m_text[m_pos] != 0) {
		m_pos++;
		length++;
	}
	if (m_text[m_pos] == 0) {
		return Token(Token::Type::EOS);
	}
	m_pos++;
	length++;
	Token t(Token::Type::String);
	t.setString(start + 1, length - 2);
	return t;
}
Token Tokenizer::popComment() {
	char* start = &m_text[m_pos];
	m_pos += 4;
	int length = 4;
	while (isspace(m_text[m_pos])) {
		m_pos++;
		length++;
	}
	while (!(m_text[m_pos] == '-' && m_text[m_pos + 1] == '-' && m_text[m_pos + 2] == '>')) {
		m_pos++;
		length++;
	}
	m_pos += 3;
	length += 3;
	Token t(Token::Type::Comment);
	t.setString(start + 4, length - 4 - 3);
	return t;
}
Token Tokenizer::popTag() {

	m_pos++;

	while (isspace(m_text[m_pos])) {
		//length++;
		m_pos++;
	}
	char* start = &m_text[m_pos];
	int length = 0;
	while (isalnum(m_text[m_pos])) {
		length++;
		m_pos++;
	}
	Token t(Token::Type::Balise);
	t.setString(start, length);
	return t;
}