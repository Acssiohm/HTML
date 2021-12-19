#include "Parser.h"
#include "Balise.h"

Element* Parser::parse() {
	Element* el;
	el = new Element(Balise("body"));
	m_body = el;
	while (!currentToken.isBaliseOf(Balise("body"))
		&& !currentToken.is(Token::Type::EOS)) {
		currentToken = m_tokenizer.popToken();
	}
	if (currentToken.is(Token::Type::EOS)) {
		return m_body;
	}
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
			m_body->addAttribute(attr, len_attr, currentToken.text(), currentToken.length());
			has_eq = false;
		}
		else {
			attr = nullptr;
			has_eq = false;
		}
		currentToken = m_tokenizer.popToken();
	}
	while (!currentToken.isEndBaliseOf(Balise("body")) && currentToken.type() != Token::Type::EOS) {

		if (currentToken.type() == Token::Type::Text) {
			Element* el;
			el = new Element(Balise(Balise::Balises::Text));
			el->setText(currentToken.text(), currentToken.length());
			//el->m_text = currentToken.text();
			//el->m_textlen = currentToken.length();
			m_body->appendChild(el);
		}
		else if (currentToken.type() == Token::Type::Balise) {
			Element* el;
			el = new Element(Balise(currentToken.text(), currentToken.length()));
			m_body->appendChild(el);
			parseBalise(el);
			currentToken = m_tokenizer.popToken();
			if (!el->m_tag.isOrpheline()) {
				parseInsideBalise(el);
			}
		}
		currentToken = m_tokenizer.popToken();
		//cout << currentToken << endl;
	}
	return m_body;

}
void Parser::parseInsideBalise(Element* el) {
	while (!currentToken.isEndBaliseOf( el->m_tag)) {
		if (currentToken.type() == Token::Type::Text) {
			Element* el2;
			el2 = new Element(Balise::Balises::Text);
			el2->setText(currentToken.text(), currentToken.length());
			//el2->m_text = currentToken.text();
			//el2->m_textlen = currentToken.length();
			el->appendChild(el2);
		}
		else if (currentToken.type() == Token::Type::Balise) {
			Element* el2;
			el2 = new Element(Balise(currentToken.text(), currentToken.length()));
			el->appendChild(el2);
			parseBalise(el2);
			currentToken = m_tokenizer.popToken();
			if (!el2->m_tag.isOrpheline()) {
				parseInsideBalise(el2);
			}
		}
		currentToken = m_tokenizer.popToken();
	}
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