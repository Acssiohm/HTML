#pragma once
#include "Tokenizer.h"
#include "Elements.h"

class Parser {
public:
	Parser(char* text) :m_tokenizer(text) {
		currentToken = m_tokenizer.popToken();
		//	nextToken = m_tokenizer.popToken();
	}

	Element* parse();
	void parseInsideBalise(Element* el);
	void parseBalise(Element* el);
	~Parser() {
		delete m_body;
	}
	Element* m_body;
	Token currentToken;
	//	Token nextToken;
	Tokenizer m_tokenizer;
};
