//#include <iostream>
#include "Elements.h"
//#include "Tokenizer.h"
#include "Parser.h"
#include <SDL.h>


using namespace std;
int main(int arg, char** argv) {
	
	char p[20][30]{ ' ' };
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 30; j++) {
			p[i][j] = ' ';
		}
	}

	const char * c = "<!-- <!DOCTYPE html> -->\
						< html >\
							<head>\
								<meta charset = 'utf-8'>\
								<meta name = 'viewport' content = 'width=device-width, initial-scale=1'>\
								<title>Test</ title>\
							</ head>\
							<body color = '#911'>\
								<p color = '#333'>\
									Some text\
									<span color = '#00A'> inside </ span>\
									or \
									<p> nested</ p>\
								</ p>\
							</ body>\
						</ html>" + 0;
	Parser prs((char * )c);
	

	Element* body = prs.parse();
	body->m_width = WIN_WIDTH;
	body->m_height = WIN_HEIGHT;
	Screen screen;
	screen.fillRect(0, 0, 300 - 1, 400 - 1, KDColorPurple);
	//screen.strokeRect(0, 0, 300, 400, KDColorWhite)
	body->show(p, screen, 0, 0);
	screen.strokeRect(0, 0, 320, 240, KDColorOrange);
	//screen.drawString("_", 20, 20, KDColorYellow, true);
	screen.update();
	screen.delay(5000);
	/*
	Tokenizer tk((char *)c);
	Token k = tk.popToken();
	while (!(k.is(Token::Type::Balise) && k.text()[0] == 'b' 
		&& k.text()[1] == 'o' && k.text()[2] == 'd' && k.text()[3] == 'y') 
		&& !k.is(Token::Type::EOS)) {
		k = tk.popToken();
	}
	while (!k.is(Token::Type::EOS)){
		cout << k << endl;
		k = tk.popToken();
	}cout << k << endl;*/
	return 0;
}



	/*
	Elements Es = Elements();
	Element f(Balises::head);
	f.m_posX = 3;
	f.m_posY = 2;
	f.m_height = 5;
	f.m_width = 5;
	Element g(Balises::head);
	g.m_posX = 3;
	g.m_posY = 2;
	g.m_height = 5;
	g.m_width = 5;
	Es.addElement(&f);
	Es.addElement(&g);
	Es.showAll(p);
	for (int x = 0; x < 20; x++) {
		for (int y = 0; y < 30; y++) {
			cout << p[x][y];
		}
		cout << endl;
	}*/

