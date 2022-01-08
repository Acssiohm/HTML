#pragma once
#include "Elements.h"
#include"KDColor.h"
#include <iostream>
#include "SDL_API.h"
using namespace std;


void Element::layout(int& x, int& y){
	m_posX = x;
	m_posY = y;
	if(m_parent){
		m_width = m_parent->m_width;
	}
	int currentX = x;
	int currentY = y;
	int lastHeight = 0;
	for (int i = 0; i < nb_childs; i++) {
		if (m_childs[i]->m_tag.isInline()) {
			m_childs[i]->layout(currentX, currentY);
		}
		else {
			if (currentX > m_posX) {
				currentY += m_childs[i - 1]->height_per_unit();
				currentX = m_posX;
			}
			m_childs[i]->layout(currentX, currentY);
			if (currentX > m_posX) {
				currentY += m_childs[i]->height_per_unit();
				currentX = m_posX;
			}
		}
	}
	x = currentX;
	y = currentY;
	if (nb_childs > 0 && m_childs[nb_childs - 1]->m_tag.isInline()) {
		currentX = m_posX;
		currentY += m_childs[nb_childs - 1]->height_per_unit();
	}
	
	if (m_parent) {
		m_height = currentY - m_posY;  
	}
}
int Text::lastSpaceBefore(int pos) {
	for (size_t i = pos; i >= 0; i--)
	{
		if (isspace(m_text[i])) {
			return i;
		}
	}
	return -1;
}
int Text::firstSpaceAfter(int pos) {
	for (size_t i = pos; i < strlen(m_text); i++)
	{
		if (isspace(m_text[i])) {
			return i;
		}
	}
	return strlen(m_text) - 1;
}
void Text::layout(int& x, int& y) {
	
	int parentX = m_parent->m_posX;
	int parentW = m_parent->m_width;
	int firstLineW = parentX + parentW - x;
	int max_nb_char_first_line = firstLineW / Sgw;
	if (strlen(m_text) <= max_nb_char_first_line) {
		m_posX = x;
		m_posY = y;
		m_height = Sgh;
		m_width = strlen(m_text) * Sgw;
		x += m_width;
	}
	else {
		m_posX = parentX;
		m_posY = y;
		m_width = parentW;
		int nb_line = 1;
		int chars_left = strlen(m_text);
		int lsbln = lastSpaceBefore(max_nb_char_first_line);
		if (lsbln == -1) {
			lsbln = firstSpaceAfter(max_nb_char_first_line);
			nb_line++;
		}
		chars_left -= lsbln;
		int nb_chars_per_line = parentW / Sgw;
		x = 0;
		while (chars_left) {
			nb_line++;
			if (chars_left <= nb_chars_per_line) {
				x = chars_left * Sgw;
				chars_left = 0;
			}
			else{
				int pos = strlen(m_text) - chars_left;
				lsbln = lastSpaceBefore(pos + nb_chars_per_line);
				if (lsbln < pos) {
					lsbln = firstSpaceAfter(pos + nb_chars_per_line);
					nb_line++;
				}
				chars_left -= (lsbln - pos);
			}
		}
		m_height = nb_line * Sgh;
		y += m_height;
	}

}

int Element::hex_to_int(char c) {
	if ('0' <= c && c <= '9')
		return int(c) - int('0');
	if ('A' <= c && c <= 'F')
		return 10 + int(c) - int('A');
	if ('a' <= c && c <= 'f')
		return 10 + int(c) - int('a');
}


void Text::showMe(Screen& s, int x, int y){
	//s.fillRect(x, /*m_posY +*/ y + Sgh, strlen(m_text) * Sgw, 1, m_color);
	s.drawString(m_text,m_posX + x, m_posY + y, KDColorBlack);
}

void Element::showMe( Screen& s, int x, int y) {
	if (m_tag.isBlock()) {
		s.fillRect(m_posX + x, m_posY + y, 320, m_height, m_color);
	}
	else {
		s.fillRect(m_posX + x, m_posY + y, minimalWidth(), m_height, m_color);
	}
	//s.fillRect(m_posX + x, m_posY + y + 20, minimalWidth(), 2, m_color);
}
void Element::show( Screen& s, int x, int y) {
	showMe(s, 0, 0);//x, y);
	//int Hn = Sgh;
	//int currentX =  x;
	//int currentY =  y;
	for (int i = 0; i < nb_childs; i++) {
		//m_childs[i]->m_height = Sgh;
		//m_childs[i]->m_width = m_childs[i]->minimalWidth();// m_width / 10;
	
		//if (m_childs[i]->m_position == Position::relative || true) {

		m_childs[i]->show(s, 0, 0);//x, currentY);
		//currentY += m_childs[i]->m_height;


			
		
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
void Text::setText(char* c, int len) {
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