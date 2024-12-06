#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;
struct Game2048
{

private:
	RenderWindow window; //Making Window For Game with buttons of resize close titlebar etc.
	Event key; //Capturing Event if we press any key in window

	int gridvalues[4][4];

	RectangleShape Grid[4][4];

	Font oftiles;
	Text fortiles;

	Font ofgame;
	Text forgameover;
	Text forgamewin;

	void valueingrid();
	void makinggrid();
	void moveTiles(int direction);
	void addNewTile();
	void initwindow();



public:
	Game2048();

	//Accessor
	bool const windowisopen() const;
	
	void eventpoll();
	bool checkGameOver();
	bool checkGameWin();
	void update();
	void renderingtext();
	void render();



};

