#pragma once
#include"KDColor.h"
#include <iostream>
#include "SDL_API.h"
#include "Balise.h"
using namespace std;


constexpr int Sgw = 7, Sgh = 14, Lgw = 10, Lgh = 18;
/*
class Style {

	void setLeft(int left) { rect[0] = left; }
	void setTop(int top) { rect[1] = top; }
	void setWidth(int width) { rect[2] = width; }
	void setHeight(int height) { rect[3] = height; }

	int Left() { return rect[0] ; }
	int Top() { return rect[1] ; }
	int Width() { return rect[2] ; }
	int Height() { return rect[3] ; }

	void setMarginLeft(int left) { margin[0] = left; }
	void setMarginTop(int top) { margin[1] = top; }
	void setMarginWidth(int width) { margin[2] = width; }
	void setMarginHeight(int height) { margin[3] = height; }

	int marginLeft() { return margin[0]; }
	int marginTop() { return margin[1]; }
	int marginWidth() { return margin[2]; }
	int marginHeight() { return margin[3]; }

	void setPaddingLeft(int left) { padding[0] = left; }
	void setPaddingTop(int top) { padding[1] = top; }
	void setPaddingWidth(int width) { padding[2] = width; }
	void setPaddingHeight(int height) { padding[3] = height; }

	int paddingLeft() { return padding[0]; }
	int paddingTop() { return padding[1]; }
	int paddingWidth() { return padding[2]; }
	int paddingHeight() { return padding[3]; }

	void setBackgroundColor(KDColor c) { bg_color = c; }
	void setColor(KDColor c) { m_color = c; }

	KDColor backgroundColor() { return bg_color; }
	KDColor color() { return m_color; }

	Element::Position position;
	int rect[4];
	int margin[4];
	int padding[4];
	KDColor bg_color;
	KDColor m_color;
};
*/
class Element {
public:
	enum class Position {
	relative,
	absolute,
	fixed
	};
	Element(Balise tag,int width = 500, int height = 500)
		:m_tag(tag), m_height(height), m_width(width), m_color(KDColorBlue),m_parent(nullptr), m_position(Position::relative) {
		m_color = KDColorBlue;
		if (m_tag.isDisplayable()) {
			m_color = m_tag.defaultColor();
		}
	}
	//void showMe( Screen& s, int x, int y);
	//int minimalWidth();
	//int maximalWidth();
	//void layout();
	//void show( Screen& s, int x, int y);
	//int hex_to_int(char c);
	void addAttribute(char* name, int len_n, char* value, int len_v);
	//void setText(char* c, int len);
	//bool appendChild(Element* child);
/*	~Element() {
		for (int i = 0; i < nb_childs; i++) {
			delete m_childs[i];
		}
		nb_childs = 0;
	}*/
//	private:
//	char * m_text = nullptr;
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
//	Element* m_childs[10];
//	int nb_childs;
	Element* m_parent;
};
/*
class Container : public Element {
public:
	Container(Balise tag, int width = 500, int height = 500): Element(tag, width, height){}
	bool appendChild(Element* child);
	virtual int nbChilds() = 0;
	virtual void setNbChilds(int nb_hilds) = 0;
	virtual int maxChilds() = 0;
	virtual Element * childAt(int index) = 0;
	virtual Element * setChildAt(int index, Element * child) = 0;
};

class Block : Container {
public :
	Block(Balise tag) : Container(tag, 0, 0 ) {
		if (tag.isInline()) {
			cerr << "Block element asigned to an inline tag ! \n";
		}
	}
private:
	//int margin[4] = { 16, 0, 16, 0 };
};
class Inline : Container {
	Inline(Balise tag) : Container(tag, 0, 0) {
		if (!tag.isInline()) {
			cerr << "Inline element asigned to a non-inline tag ! \n";
		}
	}
	//int margin[2] = { 0, 0 };
};
class Line : Container  {
	Line (Balise tag): Container(tag){	}
	bool appendChild(Element * child) {
		if (child->m_tag.isBlock()) {
			return false;
		}
		setChildAt(nbChilds(), child);
		setNbChilds(nbChilds() + 1);
		return true;
	}
	virtual int nbChilds() override;
	virtual void setNbChilds(int nb_hilds) override;
	virtual int maxChilds() override;
	virtual Element* childAt(int index) override;
	virtual Element* setChildAt(int index, Element* child) override;

	static constexpr int max_childs = 20;
	Element* m_childs[max_childs];
	int m_nb_childs;
};
class Text : public Element {
	Text(const char* el, int len) : Element(Balise::Balises::Text) {
		m_text = new char[len+1];
		for (int i = 0; i < len; i++) {
			m_text[i] = el[i];
		}
		m_text[len] = 0;
	}
	Text(const char* el):Text(el, strlen(el)){}
	Text() : Text(nullptr, 0) {}

	void setText(char * text, int len ) {
		delete m_text;
		m_text = new char[len + 1];
		for (int i = 0; i < len; i++) {
			if (isspace(text[i])) {
				m_text[i] = ' ';
			}
			else {
				m_text[i] = text[i];
			}
		}
		m_text[len] = 0;
	}
	void setText(char * text) {
		setText(text, strlen(text));
	}
private :
	char* m_text;
};
class Body : public Container {
public:
	Body(int width, int height) :Container(Balise::Balises::body, width, height){}

	virtual int nbChilds() override;
	virtual void setNbChilds(int nb_hilds) override;
	virtual int maxChilds() override;
	virtual Element* childAt(int index) override;
	virtual Element* setChildAt(int index, Element* child) override;

	static constexpr int max_childs = 20;
	Element* m_childs[max_childs];
	int m_nb_childs;
};*/