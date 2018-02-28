#include <iostream>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

const int COLS = 10;
const int ROWS = 10;
const int TS = 40;

sf::RectangleShape rectangle(sf::Vector2f(TS - 1, TS - 1));

struct Cell
{
	int x, y; // position
	int f, g, h;

	void setPosition(int i, int j)
	{
		x = j;
		y = i;
	}

	void show(sf::RenderWindow & app, sf::Color color)
	{
		rectangle.setPosition(x*TS, y*TS);
		rectangle.setFillColor(color);
		app.draw(rectangle);
	}

};


int main()
{
	srand(time(0));
	sf::RenderWindow app(sf::VideoMode(COLS * TS, ROWS * TS), "Pathfinding Algorithm");
	//	app.setFramerateLimit(60);

	// rectangle
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(1);

	// initialize with positions
	std::array<std::array<Cell, COLS>, ROWS> grid;
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			grid[i][j].setPosition(i, j);

	/// start and end used in algorithm
	Cell start = grid[0][0];
	Cell end = grid[ROWS - 1][COLS - 1];

	/// The set of nodes already evaluated
	std::vector<Cell> closedSet;

	/// The set of currently discovered nodes that are not evaluated yet.
	/// Initially, only the start node is known.
	std::vector<Cell> openSet{start};


	while (app.isOpen())
	{
		// window open
		sf::Event e;
		while (app.pollEvent(e))
			if (e.type == sf::Event::Closed)
				app.close();

		/// algorithm no solution
		if (openSet.size() == 0) continue;

		app.clear();

		/////draw/////
		// draw all grid
		for (int i = 0; i < ROWS; i++)
			for (int j = 0; j < COLS; j++)
				grid[i][j].show(app, sf::Color::White);

		// draw openset and closet
		for (Cell c : openSet) c.show(app, sf::Color::Cyan);
		for (Cell c : closedSet) c.show(app, sf::Color::Magenta);


		app.display();

	}

	return 0;
}