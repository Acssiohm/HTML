#pragma once
#include "Tokenizer.h"
#include "Elements.h"

class Parser {
public:
	Parser(char* text) :m_tokenizer(text) {
		m_body = new Element(Balise("body"));
		currentToken = m_tokenizer.popToken();
		
	}
	~Parser() {
		delete m_body;
	}

	Element* parse();
	void parseInsideBalise(Element* el);
	void parseBalise(Element* el);

	Element* m_body;
	Token currentToken;
	Tokenizer m_tokenizer;
};
