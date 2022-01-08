#pragma once
#include"KDColor.h"
#include <iostream>
#include "SDL_API.h"
#include "Balise.h"
using namespace std;

constexpr int Sgw = 7, Sgh = 14;//, Lgw = 10, Lgh = 18;

class Element {
public:
	enum class Position {
	relative,
	absolute,
	fixed
	};
	Element(Balise tag,int width = 340, int height = 20)
		:m_tag(tag), m_height(height), m_width(width), m_color(KDColorBlue),m_parent(nullptr), m_position(Position::relative) {
		m_color = KDColorBlue;
		if (m_tag.isDisplayable()) {
			m_color = m_tag.defaultColor();
		}
	}
	virtual void printMe(int nbIndent = 0, int nbSpaces = 0) {
		for (int i = 0; i < nbIndent; i++) {
			cout << "\t";
		}
		for (int i = 0; i < nbSpaces; i++) {
			cout << " ";
		}
		cout << m_tag << nb_childs << "  x :" << m_posX << " y :" << m_posY <<" min_width :" << minimalWidth() << " width :" << m_width << " height :" << m_height << endl;
	}
	virtual void print(int nbIndent = 0, int nbSpaces = 0) {
		printMe(nbIndent, nbSpaces);
		for (int i = 0; i < nb_childs; i++) {
			m_childs[i]->print(nbIndent + 1, nbSpaces);
		}
	}
	
	virtual void showMe( Screen& s, int x, int y);
	virtual int minimalWidth() {
		int w = 0;
		for (int i = 0; i < nb_childs; i++) {
			w += m_childs[i]->minimalWidth();
		}
		return w;
	}
	virtual void show( Screen& s, int x, int y);
	int hex_to_int(char c);
	void addAttribute(char* name, int len_n, char* value, int len_v);
	virtual bool appendChild(Element* child);
	~Element() {
		for (int i = 0; i < nb_childs; i++) {
			delete m_childs[i];
		}
		nb_childs = 0;
	}
	virtual void layout(int& x, int& y);
	void layout() {
		int x = 0;
		int y = 0;
		layout(x, y);
	}
//	private:
	virtual int height_per_unit() { return m_height; }

	public:
	Balise m_tag;
	int m_posX = 0;
	int m_posY = 0;
	int m_width;
	int m_height;
	KDColor m_bg_color = KDColorPurple;
	KDColor m_color;
//	int padding[4] = { 0, 0, 0, 0 };
//	int margin[4] = { 16, 0, 16, 0 };
	Position m_position;
	Element* m_childs[10];
	int nb_childs;
	Element* m_parent;
};
class Text : public Element {
public:
	Text(const char* el, int len) : Element(Balise::Balises::Text) {
		m_text = new char[len + 1];
		for (int i = 0; i < len; i++) {
			m_text[i] = el[i];
		}
		m_text[len] = 0;
	}
	Text(const char* el) :Text(el, strlen(el)) {}
	Text() : Text(nullptr, 0) {}

	virtual int minimalWidth() override{ return strlen(m_text) * Sgw; }
	void setText(char* c, int len);
	virtual void showMe(Screen& s, int x, int y) override;
	virtual void layout(int& x, int& y) override;
	int lastSpaceBefore(int pos);
	int firstSpaceAfter(int pos);

	int height_per_unit() override { return Sgh; }
private :
	char* m_text = nullptr;
};