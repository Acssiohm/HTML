#include "Parser.h"
#include "Balise.h"

Element* Parser::parse() {
	Element* el = new Element(Balise("body"));
	if (m_body) { delete m_body; }
	m_body = el;
	while (!currentToken.isBaliseOf(Balise("body"))
		&& !currentToken.is(Token::Type::EOS)) {
		currentToken = m_tokenizer.popToken();
	}
	if (currentToken.is(Token::Type::EOS)) {
		return m_body;
	}
	
	parseBalise(m_body);
	parseInsideBalise(m_body);
	return m_body;
}

void Parser::parseInsideBalise(Element* el) {
	//Line* line = new Line();
	while (!currentToken.isEndBaliseOf( el->m_tag) && currentToken.type() != Token::Type::EOS ) {
		if (currentToken.type() == Token::Type::Text) {
			Text* el2;
			el2 = new Text();//Element(Balise::Balises::Text);
			el2->setText(currentToken.text(), currentToken.length());
			//el2->m_text = currentToken.text();
			//el2->m_textlen = currentToken.length();
		//	line->appendChild(el2);
			el->appendChild(el2);
		}
		else if (currentToken.type() == Token::Type::Balise) {
			Element* el2;
			el2 = new Element(Balise(currentToken.text(), currentToken.length()));
		//	if (el2->m_tag.isInline()){
		//		line->appendChild(el2);
		//	}
		//	else {
				
		//		if (line->nb_childs > 0) {
		//			el->appendChild(line);
		//			line = new Line();
		//		}
				el->appendChild(el2);
		//	}
			parseBalise(el2);
			currentToken = m_tokenizer.popToken();
			if (!el2->m_tag.isOrpheline()) {
				parseInsideBalise(el2);
			}
		}
		currentToken = m_tokenizer.popToken();
	}
	//if (line->nb_childs > 0) {
	//	el->appendChild(line);
	//}
}
void Parser::parseBalise(Element* el) {
	currentToken = m_tokenizer.popToken();
	char* attr = nullptr;
	int len_attr = 0;
	bool has_eq = true;
	while (currentToken.type() != Token::Type::BaliseEnd) {
		if (currentToken.type() == Token::Type::Attribute) {
			attr = currentToken.text();
			len_attr = currentToken.length();
			has_eq = false;
		}
		else if (attr != nullptr && currentToken.type() == Token::Type::Equal && !has_eq) {
			has_eq = true;
		}
		else if (attr != nullptr && currentToken.type() == Token::Type::String && has_eq) {
			el->addAttribute(attr, len_attr, currentToken.text(), currentToken.length());
			has_eq = false;
		}
		else {
			attr = nullptr;
			has_eq = false;
		}
		currentToken = m_tokenizer.popToken();
	}
}