#pragma once
#include "Elements.h"
#include"KDColor.h"
#include <iostream>
#include "SDL_API.h"
#include "Style.h"
using namespace std;


KDPoint Element::layout(KDPoint startingPosition){
	m_posX = startingPosition.x();
	m_posY = startingPosition.y();
	
	if(m_parent){
		m_width = m_parent->m_width;
	}
	
	KDPoint currentPos = startingPosition;

	for (int i = 0; i < nb_childs; i++) {

		// Inline elements are placed successively
		if (m_childs[i]->m_tag.isInline()) {
			currentPos = m_childs[i]->layout(currentPos);
		}
		// Meanwhile block elements has to be put on a new line
		else {
			// verify if it's already on a new line
			if (currentPos.x() > m_posX && i > 0) {
				currentPos.m_y += m_childs[i - 1]->height_per_unit();
				currentPos.m_x = m_posX;
			}

			// Layout child
			currentPos = m_childs[i]->layout(currentPos);

			// put a new line after if it's not already at the beginning
			if (currentPos.x() > m_posX && i < nb_childs-1) {
				currentPos.m_y += m_childs[i]->height_per_unit();
				currentPos.m_x = m_posX;
			}
		}
	}

	if (m_parent) { // body has fixed dimensions
		m_height = currentPos.m_y - m_posY;
		if (nb_childs > 0) {
			m_height += m_childs[nb_childs - 1]->height_per_unit();
		}
	}
	// Inline elements width is just from start to the end of his content 
	if (m_tag.isInline() && m_posY != currentPos.y()) {
		m_width = currentPos.x() - m_posX;
	}

	return currentPos;
}
int Text::lastSpaceBefore(int pos) {
	for(int i = pos; i >= 0; i--)
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
KDPoint Text::layout(KDPoint startingPosition) {
	// The position of the text is the position at wich it starts
	m_posX = startingPosition.x();
	m_posY = startingPosition.y();

	// Just to have the values in local variables
	int parentX = m_parent->m_posX;
	int parentW = m_parent->m_width;
	int text_len = strlen(m_text);

	int firstLineW = parentW -  ( startingPosition.x() - parentX ); // = width - relative_x ( left_offset )
	int max_nb_char_first_line = firstLineW / Sgw;
	
	// If it fits into the first line we are done
	if (text_len <= max_nb_char_first_line) {
		m_height = Sgh;
		m_width = text_len * Sgw;
		return KDPoint(startingPosition.x() + m_width, startingPosition.y() );
	}
	
	// Multiple line text take all the parent's width
	m_width = parentW;

	// Starting at first character , first line
	int nb_line = 0;
	int pos = 0;

	// Searching for the next space that splits the text into lines 
	int splitting_space = lastSpaceBefore(max_nb_char_first_line);
	nb_line++;
	if (splitting_space == -1) { 
		splitting_space = firstSpaceAfter(max_nb_char_first_line);
		nb_line++; // if text is too big, it takes a whole new line
	}
	
	pos += splitting_space;
	int nb_chars_per_line = parentW / Sgw;
		
	while (pos < text_len) {
		nb_line++;
		// If there is space to fit everything else it's done
		if (text_len <= nb_chars_per_line + pos) {
			m_height = nb_line * Sgh;
			return KDPoint(
				parentX + (text_len - pos) * Sgw, // = origin + number_of_letters_left*letter_width 
				startingPosition.y() + (nb_line - 1 ) * Sgh );
		}

		// Position of the beginning of the next line :
		splitting_space = lastSpaceBefore(pos + nb_chars_per_line);
		if (splitting_space < pos) {
			splitting_space = firstSpaceAfter(pos + nb_chars_per_line);
			nb_line++;
		}

		// We can remove the characters before the space
		pos = splitting_space;
	}
	// Total height, is the height of a letter times the number of lines
	m_height = nb_line * Sgh;
	
	return KDPoint(parentX + parentW, startingPosition.y() + (nb_line - 1) * Sgh);
}

int Element::hex_to_int(char c) {
	if ('0' <= c && c <= '9')
		return int(c) - int('0');
	if ('A' <= c && c <= 'F')
		return 10 + int(c) - int('A');
	if ('a' <= c && c <= 'f')
		return 10 + int(c) - int('a');
}


void Text::showMe(Screen& s, KDPoint startingPosition ){
	//s.fillRect(x, /*m_posY +*/ y + Sgh, strlen(m_text) * Sgw, 1, m_color);

	// Just to have the values in local variables
	int parentX = m_parent->m_posX;
	int parentW = m_parent->m_width;
	int text_len = strlen(m_text);

	int firstLineW = parentW - (startingPosition.x() - parentX); // = width - relative_x ( left_offset )
	int max_nb_char_line = firstLineW / Sgw;
	int pos = 0;

	// If it fits in the first line we print it and we are done
	if (text_len <= max_nb_char_line) {
		s.drawString(m_text, m_posX + startingPosition.x(), m_posY + startingPosition.y(), KDColorBlack);
		return;
	}

	int currentY = startingPosition.y();
	int splitting_space = lastSpaceBefore(max_nb_char_line);

	// Draws the first line
	if (splitting_space == -1) { // Go to a new line if text is too long to fit
		splitting_space = firstSpaceAfter(max_nb_char_line);
		currentY += Sgh;
	} 
	s.drawString(m_text, m_posX + parentX, m_posY + currentY, KDColorBlack, splitting_space);
	currentY += Sgh;
	
	pos += splitting_space;
	max_nb_char_line = parentW / Sgh;
	while (text_len > max_nb_char_line + pos) {
		splitting_space = lastSpaceBefore(pos + max_nb_char_line);
		
		if (splitting_space == -1) { // Goes on a new line if necessary in order to draw the next line
			splitting_space = firstSpaceAfter(pos + max_nb_char_line);
			currentY += Sgh;
		}
		// Draws the next line
		s.drawString(m_text + pos + 1, parentX, m_posY + currentY, KDColorBlack, splitting_space - 1);
		currentY += Sgh;
		
		// Update the number of letters left to draw
		pos += splitting_space;
	}
	//s.drawString(m_text, m_posX + x, m_posY + y, KDColorBlack);


}

void Element::showMe( Screen& s,KDPoint startingPosition) {
	if (m_tag.isBlock()) {
		s.fillRect(m_posX + startingPosition.x(), m_posY + startingPosition.y(), 320, m_height, m_color);
	}
	else {
		s.fillRect(m_posX + startingPosition.x(), m_posY + startingPosition.y(), minimalWidth(), m_height, m_color);
	}
	//s.fillRect(m_posX + x, m_posY + y + 20, minimalWidth(), 2, m_color);
}
void Element::show( Screen& s, KDPoint startingPosition) {
	showMe(s, startingPosition);
	for (int i = 0; i < nb_childs; i++) {
		m_childs[i]->show(s, startingPosition);
	}
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
		if (name[0] == 's' && name[1] == 't' && name[2] == 'y' && name[3] == 'l' && name[4] == 'e') {
			Style s(value, len_v);
			m_style = s;
			string bg_col = m_style.getValueOf("background-color");
			if (bg_col.size() == 4 && bg_col[0] == '#') {
				int r = hex_to_int(bg_col[1]);
				int g = hex_to_int(bg_col[2]);
				int b = hex_to_int(bg_col[3]);
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