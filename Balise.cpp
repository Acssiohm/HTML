#include "Balise.h"
#include <iostream>
#include "KDColor.h"

using namespace std;

std::ostream& operator<<(std::ostream& os, const Balise& b)
{
	os << b.text();
	return os;
}
const char* Balise::text() const {
	switch (m_name) {
	case Balise::Balises::html:
		return "[ Balise : html ]";
	case Balise::Balises::head:
		return "[ Balise : head ]";
	case Balise::Balises::body:
		return "[ Balise : body ]";
	case Balise::Balises::link:
		return "[ Balise : link ]";
	case Balise::Balises::meta:
		return "[ Balise : meta ]";
	case Balise::Balises::script:
		return "[ Balise : script ]";
	case Balise::Balises::style:
		return "[ Balise : style ]";
	case Balise::Balises::title:
		return "[ Balise : title ]";
	case Balise::Balises::abbr:
		return "[ Balise : abbr ]";
	case Balise::Balises::blockquote:
		return "[ Balise : blockquote ]";
	case Balise::Balises::cite:
		return "[ Balise : cite ]";
	case Balise::Balises::q:
		return "[ Balise : q ]";
	case Balise::Balises::sup:
		return "[ Balise : sup ]";
	case Balise::Balises::sub:
		return "[ Balise : sub ]";
	case Balise::Balises::strong:
		return "[ Balise : strong ]";
	case Balise::Balises::em:
		return "[ Balise : em ]";
	case Balise::Balises::mark:
		return "[ Balise : mark ]";
	case Balise::Balises::h1:
		return "[ Balise : h1 ]";
	case Balise::Balises::h2:
		return "[ Balise : h2 ]";
	case Balise::Balises::h3:
		return "[ Balise : h3 ]";
	case Balise::Balises::h4:
		return "[ Balise : h4 ]";
	case Balise::Balises::h5:
		return "[ Balise : h5 ]";
	case Balise::Balises::h6:
		return "[ Balise : h6 ]";
	case Balise::Balises::img:
		return "[ Balise : img ]";
	case Balise::Balises::figure:
		return "[ Balise : figure ]";
	case Balise::Balises::figcaption:
		return "[ Balise : figcaption ]";
	case Balise::Balises::audio:
		return "[ Balise : audio ]";
	case Balise::Balises::video:
		return "[ Balise : video ]";
	case Balise::Balises::source:
		return "[ Balise : source ]";
	case Balise::Balises::a:
		return "[ Balise : a ]";
	case Balise::Balises::br:
		return "[ Balise : br ]";
	case Balise::Balises::p:
		return "[ Balise : p ]";
	case Balise::Balises::hr:
		return "[ Balise : hr ]";
	case Balise::Balises::address:
		return "[ Balise : address ]";
	case Balise::Balises::del:
		return "[ Balise : del ]";
	case Balise::Balises::ins:
		return "[ Balise : ins ]";
	case Balise::Balises::dfn:
		return "[ Balise : dfn ]";
	case Balise::Balises::kbd:
		return "[ Balise : kbd ]";
	case Balise::Balises::pre:
		return "[ Balise : pre ]";
	case Balise::Balises::progress:
		return "[ Balise : progress ]";
	case Balise::Balises::ul:
		return "[ Balise : ul ]";
	case Balise::Balises::ol:
		return "[ Balise : ol ]";
	case Balise::Balises::li:
		return "[ Balise : li ]";
	case Balise::Balises::dl:
		return "[ Balise : dl ]";
	case Balise::Balises::dt:
		return "[ Balise : dt ]";
	case Balise::Balises::dd:
		return "[ Balise : dd ]";
	case Balise::Balises::span:
		return "[ Balise : span ]";
	case Balise::Balises::div:
		return "[ Balise : div ]";
	case Balise::Balises::input:
		return "[ Balise : input ]";
	case Balise::Balises::Text:
		return "[ Balise : TEXT ]";
	default:
		return "[ UNKNOWN BALISE ]";
	}
}

bool operator==(const Balise& b1, const Balise& b2) {
	return b1.m_name == b2.m_name;
}
bool Balise::isOrpheline() {
	return (
		//Balises::area == m_name|| 
		//Balises::base == m_name|| 
		Balises::br == m_name ||
		//Balises::col == m_name|| 
		//Balises::embed == m_name||
		Balises::hr == m_name||
		Balises::img == m_name||
		Balises::input == m_name||
		//Balises::keygen == m_name|| 
		Balises::link == m_name||
		Balises::meta == m_name||
		//Balises::param == m_name||
		Balises::source == m_name//|| 
		//Balises::track == m_name||
		//Balises::wbr == m_name
		);
}
Balise::Balises Balise::str_to_balises(const char* str, size_t len) {
	switch (len) {
	case 0: return Balises::unknown;
	case 1:
		if (str[0] == 'q')return Balises::q;
		if (str[0] == 'a')return Balises::a;
		if (str[0] == 'p')return Balises::p;
		return Balises::unknown;
	case 2:
		if (str[0] == 'e' && str[1] == 'm')return Balises::em;
		if (str[0] == 'h' && str[1] == '1')return Balises::h1;
		if (str[0] == 'h' && str[1] == '2')return Balises::h2;
		if (str[0] == 'h' && str[1] == '3')return Balises::h3;
		if (str[0] == 'h' && str[1] == '4')return Balises::h4;
		if (str[0] == 'h' && str[1] == '5')return Balises::h5;
		if (str[0] == 'h' && str[1] == '6')return Balises::h6;
		if (str[0] == 'b' && str[1] == 'r')return Balises::br;
		if (str[0] == 'h' && str[1] == 'r')return Balises::hr;
		if (str[0] == 'u' && str[1] == 'l')return Balises::ul;
		if (str[0] == 'o' && str[1] == 'l')return Balises::ol;
		if (str[0] == 'l' && str[1] == 'i')return Balises::li;
		if (str[0] == 'd' && str[1] == 'l')return Balises::dl;
		if (str[0] == 'd' && str[1] == 't')return Balises::dt;
		if (str[0] == 'd' && str[1] == 'd')return Balises::dd;
		return Balises::unknown;
	case 3:
		if (str[0] == 's' && str[1] == 'u' && str[2] == 'p')return Balises::sup;
		if (str[0] == 's' && str[1] == 'u' && str[2] == 'b')return Balises::sub;
		if (str[0] == 'i' && str[1] == 'm' && str[2] == 'g')return Balises::img;
		if (str[0] == 'd' && str[1] == 'e' && str[2] == 'l')return Balises::del;
		if (str[0] == 'i' && str[1] == 'n' && str[2] == 's')return Balises::ins;
		if (str[0] == 'd' && str[1] == 'f' && str[2] == 'n')return Balises::dfn;
		if (str[0] == 'k' && str[1] == 'b' && str[2] == 'd')return Balises::kbd;
		if (str[0] == 'p' && str[1] == 'r' && str[2] == 'e')return Balises::pre;
		if (str[0] == 'd' && str[1] == 'i' && str[2] == 'v')return Balises::div;
		return Balises::unknown;
	case 4:
		if (str[0] == 'h' && str[1] == 't' && str[2] == 'm' && str[3] == 'l')return Balises::html;
		if (str[0] == 'h' && str[1] == 'e' && str[2] == 'a' && str[3] == 'd')return Balises::head;
		if (str[0] == 'b' && str[1] == 'o' && str[2] == 'd' && str[3] == 'y')return Balises::body;
		if (str[0] == 'l' && str[1] == 'i' && str[2] == 'n' && str[3] == 'k')return Balises::link;
		if (str[0] == 'm' && str[1] == 'e' && str[2] == 't' && str[3] == 'a')return Balises::meta;
		if (str[0] == 'a' && str[1] == 'b' && str[2] == 'b' && str[3] == 'r')return Balises::abbr;
		if (str[0] == 'c' && str[1] == 'i' && str[2] == 't' && str[3] == 'e')return Balises::cite;
		if (str[0] == 'm' && str[1] == 'a' && str[2] == 'r' && str[3] == 'k')return Balises::mark;
		if (str[0] == 's' && str[1] == 'p' && str[2] == 'a' && str[3] == 'n')return Balises::span;
		return Balises::unknown;
	case 5:
		if (str[0] == 's' && str[1] == 't' && str[2] == 'y' && str[3] == 'l' && str[4] == 'e')return Balises::style;
		if (str[0] == 't' && str[1] == 'i' && str[2] == 't' && str[3] == 'l' && str[4] == 'e')return Balises::title;
		if (str[0] == 'a' && str[1] == 'u' && str[2] == 'd' && str[3] == 'i' && str[4] == 'o')return Balises::audio;
		if (str[0] == 'v' && str[1] == 'i' && str[2] == 'd' && str[3] == 'e' && str[4] == 'o')return Balises::video;
		if (str[0] == 'i' && str[1] == 'n' && str[2] == 'p' && str[3] == 'u' && str[4] == 't')return Balises::input;
		return Balises::unknown;
	case 6:
		if (str[0] == 's' && str[1] == 'c' && str[2] == 'r' && str[3] == 'i' && str[4] == 'p' && str[5] == 't')return Balises::script;
		if (str[0] == 's' && str[1] == 't' && str[2] == 'r' && str[3] == 'o' && str[4] == 'n' && str[5] == 'g')return Balises::strong;
		if (str[0] == 'f' && str[1] == 'i' && str[2] == 'g' && str[3] == 'u' && str[4] == 'r' && str[5] == 'e')return Balises::figure;
		if (str[0] == 's' && str[1] == 'o' && str[2] == 'u' && str[3] == 'r' && str[4] == 'c' && str[5] == 'e')return Balises::source;
		return Balises::unknown;
	case 7:
		if (str[0] == 'a' && str[1] == 'd' && str[2] == 'd' && str[3] == 'r' && str[4] == 'e' && str[5] == 's' && str[6] == 's')return Balises::address;
		return Balises::unknown;
	case 8:
		if (str[0] == 'p' && str[1] == 'r' && str[2] == 'o' && str[3] == 'g' && str[4] == 'r' && str[5] == 'e' && str[6] == 's' && str[7] == 's')return Balises::progress;
		return Balises::unknown;
	case 10:
		if (str[0] == 'b' && str[1] == 'l' && str[2] == 'o' && str[3] == 'c' && str[4] == 'k' && str[5] == 'q' && str[6] == 'u' && str[7] == 'o' && str[8] == 't' && str[9] == 'e')return Balises::blockquote;
		if (str[0] == 'f' && str[1] == 'i' && str[2] == 'g' && str[3] == 'c' && str[4] == 'a' && str[5] == 'p' && str[6] == 't' && str[7] == 'i' && str[8] == 'o' && str[9] == 'n')return Balises::figcaption;
		return Balises::unknown;
	default: return Balises::unknown;
	}

}
KDColor Balise::defaultColor() {
	return (m_name == Balises::a ? KDColorBlue : KDColorBlack);
}
bool Balise::isUndisplayable() {
	return (m_name == Balises::html || m_name == Balises::link || m_name == Balises::meta || m_name == Balises::script ||
		m_name == Balises::style || m_name == Balises::title || m_name == Balises::audio || m_name == Balises::video ||
		m_name == Balises::head);
}
bool Balise::isDisplayable() {
	return !isUndisplayable();
}
bool Balise::isInline() {
	return (isDisplayable() && (Balises::a == m_name ||
		Balises::abbr == m_name ||
		//Balises::acronym == m_name ||
		Balises::audio == m_name ||
		/*	Balises::m_name  == m_name ||
			Balises::bdi == m_name ||
			Balises::bdo == m_name ||
			Balises::big == m_name ||*/
		Balises::br == m_name ||
		//Balises::button == m_name ||
		//Balises::canvas == m_name ||
		Balises::cite == m_name ||
		//Balises::code == m_name ||
		//Balises::data == m_name ||
		//Balises::datalist == m_name ||
		Balises::del == m_name ||
		Balises::dfn == m_name ||
		Balises::em == m_name ||
		//Balises::embed == m_name ||
		//Balises::i == m_name ||
		//Balises::iframe == m_name ||
		Balises::img == m_name ||
		Balises::input == m_name ||
		Balises::ins == m_name ||
		Balises::kbd == m_name ||
		//Balises::label == m_name ||
		//Balises::map == m_name ||
		Balises::mark == m_name ||
		//Balises::meter == m_name ||
		//Balises::noscript == m_name ||
		//Balises::object == m_name ||
		//Balises::output == m_name ||
		//Balises::picture == m_name ||
		Balises::progress == m_name ||
		Balises::q == m_name ||
		//Balises::ruby == m_name ||
		//Balises::s == m_name ||
		//Balises::samp == m_name ||
		Balises::script == m_name ||
		//Balises::select == m_name ||
		//Balises::slot == m_name ||
		//Balises::small == m_name ||
		Balises::span == m_name ||	//66 route de tulipes
		Balises::strong == m_name ||
		Balises::sub == m_name ||
		Balises::sup == m_name ||
		//Balises::svg == m_name ||
		//Balises::template == m_name ||
		//Balises::u == m_name ||
		//Balises::tt == m_name ||
		//Balises::var == m_name ||
		Balises::video == m_name ||
		Balises::Text == m_name
		//Balises::wbr 
		));
}
bool Balise::isBlock() {
	return !isInline() && isDisplayable();
}
