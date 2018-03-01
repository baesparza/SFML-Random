#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

// options
const int COLS = 40;
const int ROWS = 40;
const int TS = 15;

sf::CircleShape circle(TS * 0.4);

class Cell
{
public:
	int i, j; // position
	int fScore, gScore, heuristic;
	std::vector<Cell *> neighbors;
	Cell * prev;
public:
	Cell(int i, int j) : j(j), i(i)
	{
		fScore = gScore = heuristic = 0;
		prev = nullptr;
	}

	bool operator==(const Cell & temp)
	{
		return j == temp.j && i == temp.i;
	}

	void calculateNeighbors(std::array<std::array<Cell *, COLS>, ROWS> & grid)
	{
		if (i + 1 < ROWS) // down
			neighbors.push_back(grid[i + 1][j]);
		if (i - 1 >= 0)	// top
			neighbors.push_back(grid[i - 1][j]);
		if (j + 1 < COLS) // right
			neighbors.push_back(grid[i][j + 1]);
		if (j - 1 >= 0)	// left
			neighbors.push_back(grid[i][j - 1]);
		if (i + 1 < ROWS && j + 1 < COLS)
			if (grid[i + 1][j] || grid[i][j + 1])
				neighbors.push_back(grid[i + 1][j + 1]);
		if (i - 1 >= 0 && j - 1 >= 0)
			if (grid[i - 1][j] || grid[i][j - 1])
				neighbors.push_back(grid[i - 1][j - 1]);
		if (i + 1 < ROWS && j - 1 >= 0)
			if (grid[i + 1][j] || grid[i][j - 1])
				neighbors.push_back(grid[i + 1][j - 1]);
		if (i - 1 >= ROWS && j + 1 < COLS)
			if (grid[i - 1][j] || grid[i][j + 1])
				neighbors.push_back(grid[i - 1][j + 1]);

		// remove nullptr`s
		for (int i = neighbors.size() - 1; i >= 0; i--)
			if (!neighbors[i])
				neighbors.erase(neighbors.begin() + i);
	}

	~Cell() { }
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
	return std::sqrt(std::pow(e2->j - e1->j, 2) + std::pow(e2->i - e1->i, 2));
}


int main()
{
	srand(time(0));
	sf::RenderWindow app(sf::VideoMode(COLS * TS, ROWS * TS), "Pathfinding Algorithm");

	// circle
	circle.setFillColor(sf::Color::Black);
	circle.setPointCount(100);
	// line
	sf::RectangleShape line(sf::Vector2f(TS, 4));
	line.setFillColor(sf::Color::Cyan);

	// initialize with positions
	std::array<std::array<Cell *, COLS>, ROWS> grid;
	for (int i = 0; i < grid.size(); i++)
		for (int j = 0; j < grid[i].size(); j++)
			grid[i][j] = (rand() % 10 < 3) ? nullptr : new Cell(i, j); // 30 percent of obstacles

	// force start & end to be valid spots
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
		if (current == end)
			continue;

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
				{
					neighbor->gScore = tentative_gScore;






					neighbor->heuristic = heuristic(neighbor, end);
					neighbor->fScore = neighbor->gScore + neighbor->heuristic;
					neighbor->prev = current;
				}
			}
			else
			{
				/// Discover a new node
				openSet.push_back(neighbor);
				neighbor->gScore = tentative_gScore;




				neighbor->heuristic = heuristic(neighbor, end);
				neighbor->fScore = neighbor->gScore + neighbor->heuristic;
				neighbor->prev = current;
			}
		}

		//////////draw//////////
		app.clear(sf::Color::White);
		// draw all grid
		for (int i = 0; i < grid.size(); i++)
			for (int j = 0; j < grid[i].size(); j++)
				if (!grid[i][j])
				{
					circle.setPosition(j * TS, i * TS);
					circle.setFillColor(sf::Color::Black);
					app.draw(circle);
				}


		while (current)
		{
			// line.rotate(45);
			line.setPosition(current->j * TS + TS / 2, current->i * TS + TS / 2);
			current = current->prev;
			app.draw(line);
		}

		app.display();
	}

	return 0;
}