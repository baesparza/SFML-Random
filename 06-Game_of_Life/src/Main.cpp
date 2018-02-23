#include <SFML/Graphics.hpp>
#include <time.h>

// options
const int TS = 10;
const int COL = 90, ROW = 90;

struct Square
{
	bool live;
	Square()
	{
		live = rand() % 2 - 1;
	}
} grid[ROW][COL];

int main()
{
	srand(time(0));

	sf::RenderWindow app(sf::VideoMode(TS * COL, TS * ROW), "Game of life");

	// rectangle
	sf::RectangleShape rectangle(sf::Vector2f(TS, TS));
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(2);
	while (app.isOpen())
	{
		sf::Event e;
		while (app.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				app.close();
		}

		/////draw/////
		app.clear(sf::Color::White);

		// draw all rects
		for (int i = 0; i < ROW; i++)
			for (int j = 0; j < COL; j++)
			{
				rectangle.setPosition(j * TS, i * TS);
				rectangle.setFillColor((grid[i][j].live) ? sf::Color::Black : sf::Color::White); // live -> brack, else white
				app.draw(rectangle);
			}

		app.display();
	}

	return 0;
}