#include <iostream>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

// options
const int COLS = 40;
const int ROWS = 40;
const int TS = 10;

sf::RectangleShape rectangle(sf::Vector2f(TS - 1, TS - 1));

class Cell
{
public:
	int x, y; // position
	int fScore, gScore, heuristic;
	std::vector<Cell *> neighbors;
	Cell * prev;
public:
	Cell(int i, int j) : x(j), y(i)
	{
		fScore = gScore = heuristic = 0;
		prev = nullptr;
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
		if (y + 1 < ROWS) // down
			neighbors.push_back(grid[y + 1][x]);
		if (y - 1 >= 0)	// top
			neighbors.push_back(grid[y - 1][x]);
		if (x + 1 < COLS) // right
			neighbors.push_back(grid[y][x + 1]);
		if (x - 1 >= 0)	// left
			neighbors.push_back(grid[y][x - 1]);
		if (y + 1 < ROWS && x + 1 < COLS)
			if (grid[y + 1][x] || grid[y][x + 1])
				neighbors.push_back(grid[y + 1][x + 1]);
		if (y - 1 >= 0 && x - 1 >= 0)
			if (grid[y - 1][x] || grid[y][x - 1])
				neighbors.push_back(grid[y - 1][x - 1]);
		if (y + 1 < ROWS && x - 1 >= 0)
			if (grid[y + 1][x] || grid[y][x - 1])
				neighbors.push_back(grid[y + 1][x - 1]);
		if (y - 1 >= ROWS && x + 1 < COLS)
			if (grid[y - 1][x] || grid[y][x + 1])
				neighbors.push_back(grid[y - 1][x + 1]);

		// remove nullptr`s
		for (int i = neighbors.size() - 1; i >= 0; i--)
			if (!neighbors[i])
				neighbors.erase(neighbors.begin() + i);
	}

	~Cell()
	{
		std::cout << "destroyed" << "\n";
	}
};

Cell * getLowest(std::vector<Cell *> & set)
{
	Cell * best = set[0];
	for (int i = 0; i < set.size(); i++)
		if (set[i]->fScore < best->fScore)
			best = set[i];
	return best;
}

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

	bool keepSearch = false;

	// initialize with positions
	std::array<std::array<Cell *, COLS>, ROWS> grid;
	for (int i = 0; i < grid.size(); i++)
		for (int j = 0; j < grid[i].size(); j++)
			grid[i][j] = (rand() % 10 < 4) ? nullptr : new Cell(i, j); // 30 percent of obstacles

	if (!grid[0][0]) grid[0][0] = new Cell(0, 0);
	if (!grid[ROWS - 1][COLS - 1]) grid[ROWS - 1][COLS - 1] = new Cell(ROWS - 1, COLS - 1);

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
		Cell * current = getLowest(openSet);

		/// check if we are done
		if (keepSearch)
		{
			//	std::cout << "DONE" << std::endl;
			continue;
		}
		keepSearch = (current == end);
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
			int tentative_gScore = current->gScore + 1;
			if (checkIfContains(openSet, neighbor)) // has been evaluated
			{
				if (tentative_gScore < neighbor->gScore) // found a better score
					neighbor->gScore = tentative_gScore;
			}
			else
			{
				/// Discover a new node
				openSet.push_back(neighbor);
				neighbor->gScore = tentative_gScore;
			}


			neighbor->heuristic = heuristic(neighbor, end);
			neighbor->fScore = neighbor->gScore + neighbor->heuristic;
			neighbor->prev = current;
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
					rectangle.setFillColor(sf::Color::Black);
					app.draw(rectangle);
				}

		// draw openset and closet
		for (Cell * c : closedSet) c->show(app, sf::Color::Red);
		for (Cell * c : openSet) c->show(app, sf::Color::Green);

		Cell * curr = current;
		while (curr)
		{
			curr->show(app, sf::Color::Blue);
			curr = curr->prev;
		}

		app.display();
	}

	//	std::cin.get();
	return 0;
}