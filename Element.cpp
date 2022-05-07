#pragma once
#include "Elements.h"

////////////////////////////////////////////////////////////////////////////////
///////////////////////////// ELEMENT'S METHODS ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Determine the layout ( position, height ..etc. ) of the element
KDPoint	Element::layout(KDPoint startingPosition){
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
	if (m_tag.isInline() && m_posY == currentPos.y()) {
		m_width = currentPos.x() - m_posX;
	}

	return currentPos;
}

// Obsolete function for the width
int		Element::minimalWidth() {
	int w = 0;
	for (int i = 0; i < nb_childs; i++) {
		w += m_childs[i]->minimalWidth();
	}
	return w;
}

// Print debuggig informartion of this element and all his children in the console
void	Element::print(int nbIndent, int nbSpaces) {
	printMe(nbIndent, nbSpaces);
	for (int i = 0; i < nb_childs; i++) {
		m_childs[i]->print(nbIndent + 1, nbSpaces);
	}
}

// Print the debugging informations about this element in the console
void	Element::printMe(int nbIndent, int nbSpaces) {
	for (int i = 0; i < nbIndent; i++) {
		cout << "\t";
	}
	for (int i = 0; i < nbSpaces; i++) {
		cout << " ";
	}
	cout << m_tag << nb_childs << "\tx :" << m_posX << "\ty :" << m_posY << "\tmin_width :" << minimalWidth() << "\twidth :" << m_width << "\theight :" << m_height << endl;
}

// Convertit un charactère de chiffre hexadecimal en nombre 
int		Element::hex_to_int(char c) {
	if ('0' <= c && c <= '9')
		return int(c) - int('0');
	if ('A' <= c && c <= 'F')
		return 10 + int(c) - int('A');
	if ('a' <= c && c <= 'f')
		return 10 + int(c) - int('a');
	return -1;
}

// Draws this element on the screen
void	Element::showMe( Screen& s,KDPoint startingPosition) {
	KDColor background_color = m_style.background_color();
	s.fillRect(m_posX + startingPosition.x(), m_posY + startingPosition.y(), m_width, m_height, background_color);
}

// Draws this element and all his children on the screen
void	Element::show( Screen& s, KDPoint startingPosition) {
	showMe(s, startingPosition);
	for (int i = 0; i < nb_childs; i++) {
		m_childs[i]->show(s, startingPosition);
	}
}

// Add an attribute to this element ( like style, onclick ..etc. )
void	Element::addAttribute(char* name, size_t len_n, char* value, size_t len_v) {
	if (len_n == 5) { //color
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

// Add a child to the element
bool	Element::appendChild(Element* child) {
	if (nb_childs >= 10 - 1) {
		return false;
	}
	child->m_parent = this;
	m_childs[nb_childs++] = child;
	return true;
}

// The height of the last line of child elements 
int		Element::height_per_unit() { 
	return (nb_childs > 0 ? m_childs[nb_childs - 1]->height_per_unit() : 0); 
}


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// TEXT'S METHODS /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Cherche le dernier espace avant une certaine position , et retourne sa position
// et retourne -1 si aucun n'est trouvé
int		Text::lastSpaceBefore(int pos) {
	for(int i = pos; i >= 0; i--)
	{
		if (isspace(m_text[i])) {
			return i;
		}
	}
	return -1;
}

// Cherche le premier espace après une certaine position et retourne sa position
// et retourne la position de la fin du texte si aucun n'est trouvé avant
int		Text::firstSpaceAfter(int pos) {
	for (size_t i = pos; i < strlen(m_text); i++)
	{
		if (isspace(m_text[i])) {
			return (int) i;
		}
	}
	return (int) strlen(m_text) - 1;
}

// Sets a new value for the content text, replacing multiple 
// spaces, new lines, tabulation by a sipmple space
void	Text::setText(char* c, size_t len) {
	if (m_text != nullptr) {
		delete m_text;
	}
	m_text = new char[len + 1];
	for (size_t i = 0; i < len; i++) {
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

// Draws the text on the screen
void	Text::showMe(Screen& s, KDPoint startingPosition ){

	// Just to have the values in local variables
	int parentX = m_parent->m_posX;
	int parentY = m_parent->m_posY;
	int parentW = m_parent->m_width;
	size_t text_len = strlen(m_text);

	int firstLineW = parentW - (m_posX - parentX); // = width - relative_x ( left_offset )
	int max_nb_char_line = firstLineW / Sgw;

	// If it fits in the first line we print it and we are done
	if ((int)text_len <= max_nb_char_line) {
		s.drawString(m_text, m_posX, m_posY, KDColorBlack);
		return;
	}

	int pos = 0;
	int currentY = m_posY;
	int splitting_space = lastSpaceBefore(max_nb_char_line);

	// Draws the first line
	if (splitting_space == -1) { // Go to a new line if text is too long to fit
		splitting_space = firstSpaceAfter(max_nb_char_line);
		currentY += Sgh;
		m_posX = parentX;
	} 
	s.drawString(m_text, m_posX + parentX, m_posY + currentY, KDColorBlack, splitting_space);
	currentY += Sgh;

	pos += splitting_space;
	max_nb_char_line = parentW / Sgh;
	while ((int)text_len > max_nb_char_line + pos) {
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
	//s.drawString(m_text + pos + 1, parentX, m_posY + currentY, KDColorBlack, text_len - ( pos + 1 ) );
}

// Determine the position, height, width..etc. of the text
KDPoint Text::layout(KDPoint startingPosition) {
	// The position of the text is the position at wich it starts
	m_posX = startingPosition.x();
	m_posY = startingPosition.y();

	// Just to have the values in local variables
	int parentX = m_parent->m_posX;
	int parentW = m_parent->m_width;
	size_t text_len = strlen(m_text);

	int firstLineW = parentW -  ( startingPosition.x() - parentX ); // = width - relative_x ( left_offset )
	int max_nb_char_first_line = firstLineW / Sgw;
	
	// If it fits into the first line we are done
	if ((int)text_len <= max_nb_char_first_line) {
		m_height = Sgh;
		m_width = (int)text_len * Sgw;
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
		
	while (pos < (int)text_len) {
		nb_line++;
		// If there is space to fit everything else it's done
		if ((int)text_len <= nb_chars_per_line + pos) {
			m_height = nb_line * Sgh;
			return KDPoint(
				parentX + ((int)text_len - pos) * Sgw, // = origin + number_of_letters_left*letter_width 
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

// Obsolete function for the width
int		Text::minimalWidth() { 
	return (int) strlen(m_text) * Sgw; 
}

// The height of one line of this text
int		Text::height_per_unit() { 
	return Sgh; 
}

