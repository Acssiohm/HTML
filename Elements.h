#pragma once
#include "kandinsky.h"
#include <iostream>
#include "SDL_API.h"
#include "Balise.h"
#include "Style.h"

using namespace std;
constexpr int Sgw = 7, Sgh = 14;//, Lgw = 10, Lgh = 18;


class Element {
public:
	enum class Position {
	relative,
	absolute,
	fixed
	};

	Element(Balise tag = Balise::Balises::unknown,int width = 340, int height = 20)
		:m_tag(tag), m_height(height), m_width(width), m_color(KDColorBlue), m_parent(nullptr), m_position(Position::relative), m_style(), nb_childs(0), m_childs() {
		if (m_tag.isDisplayable()) {
			m_color = m_tag.defaultColor();
		}
	}
	~Element() {
		for (int i = 0; i < nb_childs; i++) {
			delete m_childs[i];
		}
		nb_childs = 0;
	}

	virtual void printMe(int nbIndent = 0, int nbSpaces = 0);
	virtual void print(int nbIndent = 0, int nbSpaces = 0);
	virtual void showMe( Screen& s, KDPoint startingPosition);
	virtual int minimalWidth();
	virtual void show( Screen& s, KDPoint startingPosition = KDPointZero);
	int hex_to_int(char c);
	void addAttribute(char* name, size_t len_n, char* value, size_t len_v);
	virtual bool appendChild(Element* child);
	virtual KDPoint layout(KDPoint startingPosition = KDPointZero);
	virtual int height_per_unit();
public:
	Style m_style;
	Balise m_tag;
	int m_posX = 0;
	int m_posY = 0;
	int m_width;
	int m_height;
	KDColor m_bg_color = KDColorPurple;
	KDColor m_color;
	Position m_position;
	Element* m_childs[10];
	int nb_childs;
	Element* m_parent;
};


class Text : public Element {
public:
	Text(const char* el, size_t len) : Element(Balise::Balises::Text) {
		m_text = new char[len + 1];
		for (size_t i = 0; i < len; i++) {
			m_text[i] = el[i];
		}
		m_text[len] = 0;
	}
	Text(const char* el) :Text(el, strlen(el)) {}
	Text() : Text(nullptr, 0) {}

	virtual int minimalWidth() override;
	void setText(char* c, size_t len);
	virtual void showMe(Screen& s,KDPoint startingPosition) override;
	virtual KDPoint layout(KDPoint startingPosition) override;
	int lastSpaceBefore(int pos);
	int firstSpaceAfter(int pos);
	int height_per_unit() override;
private :
	char* m_text = nullptr;
};
