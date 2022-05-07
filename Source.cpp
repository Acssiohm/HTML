//#include <iostream>
#include "Elements.h"
//#include "Tokenizer.h"
#include "Parser.h"
#include <SDL.h>
#include "kandinsky.h"


using namespace std;
int main(int arg, char** argv) {
	
	const char * c = R"(
	<html>
		<body style = "background-color: #F00 ; margin : 0; padding:0;width:320px;font-size: 13; ">
			<p style = "background-color: #F0F ;margin:0; padding:0;">
				Some text
				<span style = "background-color: #0F0FFF ;margin:0; padding:0;"> inside </span>
				or abcdefgh ijklmnop qrstuvw xyz1234567890ABCDEFGH IJKLMNOP QRTUVWYZ
			</p>
			<p style="background-color: #aaa;margin:0; padding:0;"> nested</p>
		</body>
	</html>
	)";
	Parser prs((char * )c);
	

	Element* body = prs.parse();
	body->m_width = 320;//WIN_WIDTH;
	body->m_height = 240;// WIN_HEIGHT;
	Screen screen;
	KDPoint origin(100, 10);
	body->layout();
	body->print();
	body->show(screen);
	//screen.strokeRect(-1, -1, 320+2, 240+2, KDColorOrange);  
	screen.update();



	SDL_bool run = SDL_TRUE;
	while (run) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT :
					run = SDL_FALSE;
					break;
				case SDL_KEYUP:
					if (event.key.keysym.sym == SDLK_SPACE) {
						body->m_width ++;
						body->m_height ++ ;
						body->layout();
						screen.fillRect(0, 0, 1000, 1000, KDColorBlack);
						body->show(screen);
						screen.update();

					}
					if (event.key.keysym.sym == SDLK_UP) {
						body->m_width += 10;
						body->m_height += 10;
						body->layout();
						screen.fillRect(0, 0, 1000, 1000, KDColorBlack);
						body->show(screen);
						screen.update();

					}
					if (event.key.keysym.sym == SDLK_DOWN) {
						body->m_width -= 10;
						body->m_height -= 10;
						body->layout();
						screen.fillRect(0, 0, 1000, 1000, KDColorBlack);
						body->show(screen);
						screen.update();   
					}
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

