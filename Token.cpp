#include "Token.h"
#include "Balise.h"

bool Token::isBaliseOf( Balise b) {
	return (is(Token::Type::Balise) && Balise(text(), length()) == b);
}
bool Token::isEndBaliseOf( Balise b) {
	return (is(Token::Type::EndBalise) && Balise(text(), length()) == b);
}
ostream& operator<<(ostream& os, const Token& t)
{
	os << "Token < " << t.type();
	if (t.length()) {
		os << " : '";
		for (size_t i = 0; i < t.length(); i++) {
			os << t.text()[i];
		}
		os << "' ";
	}
	os << " >";

	return os;
}
ostream& operator<<(ostream& os, const Token::Type& t)
{
	switch (t) {
	case Token::Type::Comment:
		os << "Type : Comment";
		break;
	case Token::Type::Balise:
		os << "Type : Balise";
		break;
	case Token::Type::BaliseEnd:
		os << "Type : BaliseEnd";
		break;
	case Token::Type::EndBalise:
		os << "Type : EndBalise";
		break;
	case Token::Type::Text:
		os << "Type : Text";
		break;
	case Token::Type::Attribute:
		os << "Type : Attribute";
		break;
	case Token::Type::Equal:
		os << "Type : Equal";
		break;
	case Token::Type::String:
		os << "Type : String";
		break;
	case Token::Type::EOS:
		os << "Type : EOS";
		break;
	default:
		os << "Type : Unknown";
	}
	return os;
}
