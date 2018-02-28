#include <iostream>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

// options
const int COLS = 50;
const int ROWS = 60;
const int TS = 10;

sf::RectangleShape rectangle(sf::Vector2f(TS - 1, TS - 1));

class Cell
{
public:
	int x, y; // position
	int f, g, h;
	std::vector<Cell *> neighbors;
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

	void calculateNeighbors(std::array<std::array<Cell *, COLS>, ROWS> & grid)
	{
		int i = y, j = x;
		if (i + 1 < ROWS) if (grid[i + 1][j]) neighbors.push_back(grid[i + 1][j]); // down
		if (i - 1 >= 0)if (grid[i - 1][j]) neighbors.push_back(grid[i - 1][j]); // top
		if (j + 1 < COLS)if (grid[i][j + 1]) neighbors.push_back(grid[i][j + 1]); // right
		if (j - 1 >= 0) if (grid[i][j - 1])neighbors.push_back(grid[i][j - 1]); // left
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

bool checkIfContains(std::vector<Cell *> & vector, Cell * element)
{
	for (Cell * v : vector)
		if (v == element)
			return true;
	return false;
}

int heuristic(Cell * e1, Cell * e2)
{
	return std::sqrt(std::pow(e2->x - e1->x, 2) + std::pow(e2->y - e1->y, 2));
}


int main()
{
	srand(time(0));
	sf::RenderWindow app(sf::VideoMode(COLS * TS, ROWS * TS), "Pathfinding Algorithm");

	// rectangle
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(1);

	// initialize with positions
	std::array<std::array<Cell *, COLS>, ROWS> grid;
	for (int i = 0; i < grid.size(); i++)
		for (int j = 0; j < grid[i].size(); j++)
			grid[i][j] = (rand() % 10 < 5) ? nullptr : new Cell(i, j);

	grid[0][0] = new Cell(0, 0);
	grid[ROWS - 1][COLS - 1] = new Cell(ROWS - 1, COLS - 1);

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

		removeFromVector(openSet, current);
		closedSet.push_back(current);

		current->calculateNeighbors(grid);
		for (Cell * neighbor : current->neighbors)
		{
			/// Ignore the neighbor which is already evaluated.
			if (checkIfContains(closedSet, neighbor))
				continue;

			/// The distance from start to a neighbor
			/// the "dist_between" function may vary as per the solution requirements.
			int tentative_gScore = current->g + 1;
			if (checkIfContains(openSet, neighbor)) // has been evaluated
			{
				if (tentative_gScore < neighbor->g) // found a better score
					neighbor->g = tentative_gScore;
			}
			else
			{
				/// Discover a new node
				openSet.push_back(neighbor);
				neighbor->g = tentative_gScore;
			}


			neighbor->h = heuristic(neighbor, end);
			neighbor->f = neighbor->g + neighbor->h;

		}

		//////////draw//////////
		app.clear();
		// draw all grid
		for (int i = 0; i < grid.size(); i++)
			for (int j = 0; j < grid[i].size(); j++)
				if (grid[i][j])
					grid[i][j]->show(app, sf::Color::White);
				else
				{
					rectangle.setPosition(j * TS, i * TS);
					rectangle.setFillColor(sf::Color::Blue);
					app.draw(rectangle);
				}

		// draw openset and closet
		for (Cell * c : closedSet) c->show(app, sf::Color::Red);
		for (Cell * c : openSet) c->show(app, sf::Color::Green);

		app.display();
	}

	//	std::cin.get();
	return 0;
}