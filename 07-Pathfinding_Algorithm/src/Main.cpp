#include <iostream>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

const int COLS = 5;
const int ROWS = 6;
const int TS = 60;

sf::RectangleShape rectangle(sf::Vector2f(TS - 1, TS - 1));

class Cell
{
public:
	int x, y; // position
	int f, g, h;
public:
	Cell(int i, int j) : x(j), y(i)
	{
		f = g = h = 0;
	}

	void show(sf::RenderWindow & app, sf::Color color)
	{
		rectangle.setPosition(x*TS, y*TS);
		rectangle.setFillColor(color);
		app.draw(rectangle);
	}

	bool operator==(const Cell & temp)
	{
		return x == temp.x && y == temp.y;
	}

	~Cell()
	{
		std::cout << "destroyed" << "\n";
	}
};

void removeFromVector(std::vector<Cell *> & vector, Cell * element)
{
	for (int i = vector.size() - 1; i >= 0; i--)
		if (element == vector[i])
		{
			vector.erase(vector.begin() + i);
			return;
		}
}


int main()
{
	//	srand(time(0));
	sf::RenderWindow app(sf::VideoMode(COLS * TS, ROWS * TS), "Pathfinding Algorithm");

	// rectangle
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(1);

	// initialize with positions
	std::array<std::array<Cell *, COLS>, ROWS> grid;
	for (int i = 0; i < grid.size(); i++)
		for (int j = 0; j < grid[i].size(); j++)
			grid[i][j] = new Cell(i, j);

	/// start and end used in algorithm
	Cell * start = grid[0][0];
	Cell * end = grid[ROWS - 1][COLS - 1];

	/// The set of nodes already evaluated
	std::vector<Cell *> closedSet;

	/// The set of currently discovered nodes that are not evaluated yet.
	/// Initially, only the start node is known.
	std::vector<Cell *> openSet{start};

	while (app.isOpen())
	{
		// window open
		sf::Event e;
		while (app.pollEvent(e))
			if (e.type == sf::Event::Closed)
				app.close();


		/// algorithm no solution
		if (openSet.size() == 0) continue;

		/// the node in openSet having the lowest fScore[] value
		Cell * current = openSet[0];
		for (int i = 0; i < openSet.size(); i++)
			if (openSet[i]->f < current->f)
				current = openSet[i];

		/// check if we are done
		if (current == end)
			std::cout << "DONE" << std::endl;

		//removeFromVector(openSet, current);
		closedSet.push_back(current);

		//////////draw//////////
		app.clear();
		// draw all grid
		for (int i = 0; i < grid.size(); i++)
			for (int j = 0; j < grid[i].size(); j++)
				grid[i][j]->show(app, sf::Color::White);

		// draw openset and closet
		for (Cell * c : closedSet) c->show(app, sf::Color::Red);
		for (Cell * c : openSet) c->show(app, sf::Color::Green);

		app.display();
	}

	return 0;
}