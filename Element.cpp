#pragma once
#include "Elements.h"
#include"KDColor.h"
#include <iostream>
#include "SDL_API.h"
using namespace std;

int hex_to_int(char c) {
	if ('0' <= c && c <= '9')
		return int(c) - int('0');
	if ('A' <= c && c <= 'F')
		return int(c) - int('A');
	if ('a' <= c && c <= 'f')
		return int(c) - int('a');
}
/*
bool Container::appendChild(Element * child) {
	int nb_childs = nbChilds();
	if ( nb_childs >= maxChilds() - 1 ) {
		return false;
	}
	child->m_parent = this;
	setChildAt(nb_childs, child);
	setNbChilds(nb_childs + 1);
	return true;
}

int Body::nbChilds() { return m_nb_childs; }
void Body::setNbChilds(int nb_childs) { m_nb_childs = nb_childs; }
int Body::maxChilds() { return max_childs; }
Element* Body::childAt(int index) { return m_childs[index]; }
Element* Body::setChildAt(int index, Element* child) { m_childs[index] = child; }
*/






















void Element::showMe( Screen& s, int x, int y) {

	s.fillRect(m_posX + x, m_posY + y, m_width, m_height, m_color);
	s.fillRect(m_posX + x, m_posY + y + 20, minimalWidth(), 2, m_color);
	if (m_tag == Balise::Balises::Text) {
	
		s.fillRect(x, /*m_posY +*/ y + 20, strlen(m_text) * Sgw, 2, KDColorOrange);
		s.drawString(m_text,/*m_posX +*/ x, /*m_posY +*/ y, KDColorOrange);


	}

}

void Element::show( Screen& s, int x, int y) {
	showMe( s, x, y);
	int Hn = Lgh;
	int currentX = /*m_posX + marginX*/ + x;
	int currentY = /*m_posY + marginY*/ + y;
	for (int i = 0; i < nb_childs; i++) {
		m_childs[i]->m_height = Lgh;
		m_childs[i]->m_width = m_childs[i]->minimalWidth();// m_width / 10;
			
		if (m_childs[i]->m_position == Position::relative) {
			if (m_childs[i]->m_tag.isInline()) {
				m_childs[i]->show( s, currentX, currentY);
				currentX += m_childs[i]->m_width;
			}
			else {
				if (i == 0) {
					m_childs[i]->show( s, currentX, currentY);
					currentY += m_childs[i]->m_height;
					currentX = x;
				}
				else {
					currentX = x;
					currentY += m_childs[i-1]->m_height;
					m_childs[i]->show( s, currentX, currentY);
					currentX += m_childs[i]->m_width;
				}


			}
		}
	}
	//cout << "-----";
}


void Element::addAttribute(char* name, int len_n, char* value, int len_v) {
	if (len_n == 5) { //color
		if (name[0] == 'c' && name[1] == 'o' && name[2] == 'l' && name[3] == 'o' && name[4] == 'r') {
			if (len_v == 4 && value[0] == '#') {
				int r = hex_to_int(value[1]);
				int g = hex_to_int(value[2]);
				int b = hex_to_int(value[3]);
				m_color = KDColor::RGB888(r << 4, g << 4, b << 4);
			}
		}
	}
	//cout << name << ":" << value << endl;
}
void Element::setText(char* c, int len) {
	if (m_text != nullptr) {
		delete m_text;
	}
	m_text = new char[len + 1];
	for (int i = 0; i < len; i++) {
		if (isspace(c[i])) {
			m_text[i] = ' ';
		}
		else {
			m_text[i] = c[i];
		}
	}
	m_text[len] = 0;
	//cout << m_text << ":" << len;
}
bool Element::appendChild(Element* child) {
	if (nb_childs >= 10 - 1) {
		return false;
	}
	child->m_parent = this;
	m_childs[nb_childs++] = child;
	return true;
}