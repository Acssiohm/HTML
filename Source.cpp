//#include <iostream>
#include "Elements.h"
//#include "Tokenizer.h"
#include "Parser.h"
#include <SDL.h>
#include "kandinsky.h"


using namespace std;
int main(int arg, char** argv) {
	
	const char * c = "<!-- <!DOCTYPE html> -->\
						< html >\
							<head>\
								<meta charset = 'utf-8'>\
								<meta name = 'viewport' content = 'width=device-width, initial-scale=1'>\
								<title>Test</ title>\
							</ head>\
							<body color = '#F00'>\
								<p color = '#F0F'>\
									Some text\n\
									<span color = '#00F'>inside </span> or abcdefgh ijklmnop qrstuvw xyz1234567890ABCDEFGH IJKLMNOP QRTUVWYZ\
								</ p>\
								<p color = '#aaa'> nested</ p>\
							</ body>\
						</ html>" + 0;
	Parser prs((char * )c);
	

	Element* body = prs.parse();
	body->m_width = 320;//WIN_WIDTH;
	body->m_height = 240;// WIN_HEIGHT;
	Screen screen;
	//screen.fillRect(0, 0, 300 - 1, 400 - 1, KDColorPurple);
	//screen.strokeRect(0, 0, 300, 400, KDColorWhite)
	body->layout();
	body->print();
	body->show(screen);
	screen.strokeRect(-1, -1, 320+2, 240+2, KDColorOrange);
	//screen.drawString("_", 20, 20, KDColorYellaow, true);
	screen.update();



	SDL_bool run = SDL_TRUE;
	while (run) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT :
					run = SDL_FALSE;
					break;
				default :
					break;

			}
		}

	}
	//screen.delay(5000);
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

