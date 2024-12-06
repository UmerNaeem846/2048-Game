#include "Game2048.h"
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




void Game2048::initwindow()
{
	window.create(VideoMode(450, 450), "2048", Style::Titlebar | Style::Close | Style::Resize);
	window.setFramerateLimit(60);
}

void Game2048::valueingrid()
{
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			gridvalues[i][j] = 0;
		}
	}
	for (int count = 0; count < 2; count++) {
		int x, y;
		do {
			x = rand() % 4;
			y = rand() % 4;
		} while (gridvalues[x][y] != 0); 

		gridvalues[x][y] = (rand() % 2 + 1) * 2; 
	}
}


void Game2048::makinggrid()
{
	float xspacing =110 ;
	float yspacing =110 ;
	float xstart =10 ;
	float ystart =10 ;
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			Grid[i][j].setSize(Vector2f(100, 100));
			Grid[i][j].setFillColor(Color::Black);
			Grid[i][j].setPosition(xstart + j * xspacing, ystart + i * yspacing);

		}
	}
}
void Game2048::moveTiles(int direction)
{
	bool moved = false;
	if (direction == 0)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int i = 1; i < 4; i++)
			{
				if (gridvalues[i][j] != 0)
				{
					int trow = i;
					while (trow > 0 && gridvalues[trow - 1][j] == 0)
					{
						gridvalues[trow - 1][j] = gridvalues[trow][j];
						gridvalues[trow][j] = 0;
						trow--;
						moved = true;
					}
					if (trow > 0 && gridvalues[trow - 1][j] == gridvalues[trow][j]) 
					{
						gridvalues[trow - 1][j] *= 2;
						gridvalues[trow][j] = 0;
						moved = true;
					}
				}
			}
		}
	}
	else if (direction == 1)
	{
		
		for (int j = 0; j < 4; j++) 
		{
			for (int i = 2; i >= 0; i--)
			{
				if (gridvalues[i][j] != 0)
				{
					int trow = i;
					while (trow < 3 && gridvalues[trow + 1][j] == 0) 
					{
						gridvalues[trow + 1][j] = gridvalues[trow][j];
						gridvalues[trow][j] = 0;
						trow++;
						moved = true;
					}
					if (trow < 3 && gridvalues[trow + 1][j] == gridvalues[trow][j])
					{
						gridvalues[trow + 1][j] *= 2;
						gridvalues[trow][j] = 0;
						moved = true;
					}
				}
			}
		}
	}
	if (direction == 2)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				if (gridvalues[i][j] != 0)
				{
					int tcolunm = j;
					while (tcolunm > 0 && gridvalues[i][tcolunm - 1] == 0)
					{
						gridvalues[i][tcolunm - 1] = gridvalues[i][tcolunm];
						gridvalues[i][tcolunm] = 0;
						tcolunm--;
						moved = true;
					}
					if (tcolunm > 0 && gridvalues[i][tcolunm - 1] == gridvalues[i][tcolunm])
					{
						gridvalues[i][tcolunm - 1] *= 2;
						gridvalues[i][tcolunm] = 0;
						moved = true;
					}
				}
			}
		}
	}
	if (direction == 3)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 2; j >= 0; j--) 
			{
				if (gridvalues[i][j] != 0) 
				{
					int tcolunm = j;
					while (tcolunm < 3 && gridvalues[i][tcolunm + 1] == 0) 
					{
						gridvalues[i][tcolunm + 1] = gridvalues[i][tcolunm];
						gridvalues[i][tcolunm] = 0;
						tcolunm++;
						moved = true;
					}
					if (tcolunm < 3 && gridvalues[i][tcolunm + 1] == gridvalues[i][tcolunm]) 
					{
						gridvalues[i][tcolunm + 1] *= 2;
						gridvalues[i][tcolunm] = 0;
						moved = true;
					}
				}
			}
		}
	}
	if (moved) 
	{
		addNewTile();
	}
}
void Game2048::addNewTile()
{
	int emptycells[16][2];
	int empty_c = 0;

	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++)
		{
			if (gridvalues[i][j] == 0)
			{
				emptycells[empty_c][0] = i;
				emptycells[empty_c][1] = j;
				empty_c++;
			}
		}
	}

	if (empty_c > 0) 
	{
		int randomindex = rand() % empty_c;
		int x = emptycells[randomindex][0];
		int y = emptycells[randomindex][1];
		gridvalues[x][y] = (rand() % 2 + 1) * 2;
	}
}

Game2048::Game2048()
{
	initwindow();
	makinggrid();
	valueingrid();
}

bool const Game2048::windowisopen() const
{
	return window.isOpen();
}
bool Game2048::checkGameOver() 
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (gridvalues[i][j] == 0)
			{
				return false; 
			}
			if (j < 3 && gridvalues[i][j] == gridvalues[i][j + 1])
			{
				return false;
			}
			if (i < 3 && gridvalues[i][j] == gridvalues[i + 1][j])
			{
				return false;
			}
		}
	}
	return true;
}
bool Game2048::checkGameWin() 
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (gridvalues[i][j] == 2048) 
			{
				return true; 
			}
		}
	}
	return false;
}
void Game2048::eventpoll()
{
	ofgame.loadFromFile("AGENCYB.TTF");
	while (window.pollEvent(key))
		if (checkGameOver())
		{
			forgameover.setFont(ofgame);
			forgameover.setCharacterSize(35);
			forgameover.setString("Game Over!");
			forgameover.setFillColor(Color::Black);
			forgameover.setPosition(200, 215);
		}
		if (checkGameWin())
		{
			forgamewin.setFont(ofgame);
			forgamewin.setCharacterSize(35);
			forgamewin.setString("You won the game!");
			forgamewin.setFillColor(Color::Black);
			forgameover.setPosition(200, 215);

		}
		switch (key.type)
		{
		case Event::Closed:
			window.close();
		case Event::KeyPressed:
			if (key.key.code == Keyboard::Up)
				moveTiles(0);
			else if (key.key.code == Keyboard::Down)
				moveTiles(1);
			else if (key.key.code == Keyboard::Left)
				moveTiles(2);
			else if (key.key.code == Keyboard::Right)
				moveTiles(3);
			break;
		}

}

void Game2048::update()
{
	eventpoll();
}

void Game2048::renderingtext()
{
	oftiles.loadFromFile("AGENCYB.TTF");
	fortiles.setFont(oftiles);
	fortiles.setCharacterSize(24);
	fortiles.setFillColor(Color::White);
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			if (gridvalues[i][j] != 0)
			{
				fortiles.setString(to_string(gridvalues[i][j]));
				fortiles.setPosition(Grid[i][j].getPosition().x + 35, Grid[i][j].getPosition().y + 35);
				window.draw(fortiles);
			}
		}
	}

}

void Game2048::render()
{
	window.clear(Color::White);
	if (checkGameOver())
	{
		window.draw(forgameover);

	}
	if (checkGameWin())
	{
		window.draw(forgamewin);
	}
	if (!checkGameWin())
	{
		if (!checkGameOver())
		{
			for (int i = 0;i < 4;i++)
			{
				for (int j = 0;j < 4;j++)
				{
					window.draw(Grid[i][j]);
					renderingtext();

				}
			}
		}
	}


	window.display();
}
